class Fecha{
	private: 
		int diasDesde0;
	public: 
		Fecha();
		Fecha(int, int, int);

		friend int operator - (Fecha, Fecha);
		friend bool operator > (Fecha, Fecha);
		friend bool operator == (Fecha, Fecha);
		friend ostream& operator << (ostream&, Fecha);
		void operator = (Fecha);
};
Fecha::Fecha(){
	diasDesde0 = 0;
}
Fecha::Fecha(int dd, int mm, int aaaa){
	diasDesde0 = dd; 
	///Recibo los valores de dia mes y anio y los convierto a dias
	double diasAnio = aaaa*365.25;
	switch(mm){
	case 1: break;
	case 2: diasDesde0 += 31; break;
	case 3: diasDesde0 += 59; break;
	case 4: diasDesde0 += 90; break;
	case 5: diasDesde0 += 120; break;
	case 6: diasDesde0 += 151; break;
	case 7: diasDesde0 += 181; break;
	case 8: diasDesde0 += 212; break;
	case 9: diasDesde0 += 243; break;
	case 10:diasDesde0 += 273; break;
	case 11:diasDesde0 += 304; break;
	case 12:diasDesde0 += 334; break;
	}
	
	diasDesde0 += diasAnio;
	//diasDesde0 = ( (aaaa%4==0 && aaaa%100!=0 || aaaa%100==0 && aaaa%400==0) && mm<2) ? diasDesde0-1:diasDesde0;
	//si el anio de la fecha es bisiesto 
	//habia bandera que decia que diasDesde0 tiene bien los valores
}

int operator - (Fecha f1, Fecha f2){
	return f1.diasDesde0-f2.diasDesde0;
}
bool operator > (Fecha f1, Fecha f2){
	return (f1.diasDesde0>f2.diasDesde0) ? true:false;	
}
bool operator == (Fecha f1, Fecha f2){
	return (f1.diasDesde0==f2.diasDesde0) ? true:false;	
}
ostream&  operator << (ostream& os, Fecha f1){
	string meses[12] = {"enero","febrero","marzo","abril","mayo","junio","julio"
						,"agosto","septiembre","octubre","noviembre","diciembre"};
	int dd, mm, aaaa;
	bool bisiesto = false;
	//habia bandera, los dias siguen bien a la hora de imprimir
	dd = f1.diasDesde0;

	double anio = dd/365.25;
	aaaa = anio;
	if(aaaa%4==0 && aaaa%100!=0|| aaaa%100==0 && aaaa%400==0){
		bisiesto = false; //puse que siempre fuera false para ver si se arreglaba la bug y se arreglo, lo tengo que quitar
	}
	anio-= aaaa;
	anio *= 365.25; 
	dd = anio;
	anio -= dd;

	if(dd<=31){
		mm = 1;	
	}else if(dd<=59 || dd<=60 && bisiesto){
		mm = 2;
		dd-=30;
	}else if(dd<=90 || dd<=91 && bisiesto){
		mm = 3;
		dd = (!bisiesto) ? (dd-58):(dd-59);
	}else if(dd<=120 || dd<=121 && bisiesto){
		mm = 4;
		dd = (!bisiesto) ? (dd-89):(dd-90);
	}else if(dd<=151 || dd<=152 && bisiesto){
		mm = 5;
		dd = (!bisiesto) ? (dd-119):(dd-120);
	}else if(dd<=181 || dd<=182 && bisiesto){
		mm = 6;
		dd = (!bisiesto) ? (dd-150):(dd-151);
	}else if(dd<=212 || dd<=213 && bisiesto){
		mm = 7;
		dd = (!bisiesto) ? (dd-180):(dd-181);
	}else if(dd<=243 || dd<=244 && bisiesto){
		mm = 8;
		dd = (!bisiesto) ? (dd-211):(dd-212);
	}else if(dd<=273 || dd<=274 && bisiesto){
		mm = 9;
		dd = (!bisiesto) ? (dd-242):(dd-243);
	}else if(dd<=304 || dd<=305 && bisiesto){
		mm = 10;
		dd = (!bisiesto) ? (dd-272):(dd-273);
	}else if(dd<=334 || dd<=335 && bisiesto){
		mm = 11;
		dd = (!bisiesto) ? (dd-303):(dd-304);
	}else if(dd<=365 || dd<=366 && bisiesto){
		mm = 12;
		dd = (!bisiesto) ? (dd-333):(dd-334);
	}
//Le quite un dia menos a dias en cada mes, porque me daba un dia mas.
	if(aaaa==0 && mm>1) dd--;
	os<<dd<<" de "<<meses[mm-1]<<" de "<<aaaa<<' ';
	return os; 
}
void Fecha::operator = (Fecha f2){
	diasDesde0 = f2.diasDesde0;
}
