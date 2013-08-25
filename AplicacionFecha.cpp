#include <iostream>
#include <time.h>
#include <fstream>
#include <cstdlib>

using namespace std; 
#include "ImplementacionFecha.h"
bool debug = true;

bool es_numerico(string s){
	bool numerico = true; 
	int i = 0;
	while(i<s.length() && numerico){
		if( s[i]!='0' && s[i]!='1' && s[i]!='2' && s[i]!='3' && s[i]!='4' &&
		     s[i]!='5' && s[i]!='6' && s[i]!='7' &&  s[i]!='8' && s[i]!='9' ) 
				numerico = false; 
		i++;
	}
	return numerico; 
}

bool validar_fecha(int d, int m, int a){
	bool validez = false; 
	validez = (d>0 && m>0 && m<=12 && a>=0) ? true:false;
	if(validez){
			if(m==2){
				if(a%4==0 && a%100!=0 || a%100==0 && a%400==0){
					validez = (d>0 && d<=29) ? true:false;
				}else{
					validez = (d>0 && d<=28) ? true:false;
				}
			}else if(m==1 || m==3 || m==5 || m== 7 || m==8 || m==10 || m==12){
					validez = (d>0 && d<=31) ? true:false; 
			}else{
					validez = (d>0 && d<=30) ? true:false; 
			}
	 }
	return validez; 
}

int main(){
	string nom_archivo;
	ifstream archivo; 	
	string dia, mes, anio; 
	int dd, mm, aaaa;
	Fecha fmayor, fmenor;//inicializo fechas en default
	
	//OBTENER FECHA ACTUAL DEL SISTEMA///
	time_t segundosdesde1970;
	struct tm * tiempo_sistema;
	time(&segundosdesde1970);
	tiempo_sistema = localtime(&segundosdesde1970);
	//Ahora el dia esta en tiempo_sistema->tm_mday, 
	//el mes esta en ->tm_mon+1 
	//y el anio esta en ->tm_year+1900
	Fecha factual(tiempo_sistema->tm_mday, tiempo_sistema->tm_mon+1, tiempo_sistema->tm_year+1900);
	
	//PEDIR EL NOMBRE DEL ARCHIVO//
	cout<<"Introduzca el nombre del archivo de texto (con extension .txt):"<<endl;
	cin>>nom_archivo;

	//LEER EL ARCHIVO OBTENIENDO FECHA MAYOR, FECHA MENOR//
	//e imprimiendo si es del futuro pasado o presente
	//Tambien debo validar cada fecha antes de hacer el objeto.
		
	archivo.open(nom_archivo.c_str());
	string linea;
	bool primera_vuelta = true; 
	while(!archivo.eof()){
		getline(archivo,linea);	
		cout<<linea<<endl;
		if(linea.length()==10){
			if(debug)
				cout<<"DEBUG::Es de longitud 10. B"<<endl;
			dia = linea.substr(0,2);
			mes = linea.substr(3,2);
			anio = linea.substr(6,4);
			if(es_numerico(dia) && es_numerico(mes) && es_numerico(anio)){
				if(debug)
					cout<<"DEBUG::Es es numerico. B"<<endl;
				dd = atoi(dia.c_str());
				mm = atoi(mes.c_str());
				aaaa = atoi(anio.c_str());
				if(validar_fecha(dd, mm, aaaa)){
					if(debug)
						cout<<"DEBUG::Es fecha valida. B "<<dd<<mm<<aaaa<<endl;
					//LA FECHA LEIDA ES VALIDA
					Fecha ftemp(dd, mm, aaaa); 
					if(primera_vuelta){
						fmenor = ftemp;
						fmayor = ftemp;
						primera_vuelta = false;
					}
					
					int diasDeDiferencia;
					cout<<ftemp<<"es una fecha del ";
					if(factual>ftemp){
						cout<<"pasado, ";
						diasDeDiferencia = factual-ftemp;
					}else if(ftemp>factual){
						cout<<"futuro, ";
						diasDeDiferencia = ftemp-factual;
					}else{
						cout<<"presente, ";
						diasDeDiferencia = 0;
					}
					cout<<diasDeDiferencia<<" dias de diferencia."<<endl;	
					fmenor = (fmenor>ftemp) ? ftemp:fmenor;
					fmayor = (ftemp>fmayor) ? ftemp:fmayor;
					
				}else{
					//fecha numerica pero no valida
				}
			}else{
				//no es numerico
			}
		}else{
			//no es de la longitud apropiada
		}
	}
	archivo.close();
	return 0;
}

