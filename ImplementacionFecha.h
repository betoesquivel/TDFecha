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
	diasDesde0 = ( (aaaa%4==0 && aaaa%100!=0 || aaaa%100==0 && aaaa%400==0) && mm>2) ? diasDesde0-1:diasDesde0;
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
	int dd, mm, aaaa;
	//habia bandera, los dias siguen bien a la hora de imprimir
	dd = f1.diasDesde0;

	double anio = dd/365.25;
	aaaa = anio;
	anio-= aaaa;
	anio *= 12; 
	mm = anio; 
	anio -= mm;
	switch(mm){
	case 1: anio *= 31; 
		dd = anio;	
		break;    
	case 2: if(aaaa%4==0 && aaaa%100!=0 || aaaa%100==0 && aaaa%400==0){
			anio *= 29;
		}else{
			anio *= 28;
		} 
                dd = anio; 
                break;    
	case 3: anio *= 31;
                dd = anio; 
                break;    
	case 4: anio *= 30;
                dd = anio; 
                break;    
	case 5: anio *= 31;
                dd = anio; 
                break;    
	case 6: anio *= 30;
                dd = anio; 
                break;    
	case 7: anio *= 31;
                dd = anio; 
                break;    
	case 8: anio *= 31;
                dd = anio; 
                break;    
	case 9: anio *= 30;
                dd = anio; 
                break;    
	case 10:anio *= 31;
                dd = anio; 
                break;    
	case 11:anio *= 30;
                dd = anio; 
                break;    
	case 12:anio *= 31;
                dd = anio; 
                break;    
	}
	os<<dd<<"/"<<mm<<"/"<<aaaa<<endl;
	return os; 
}
void Fecha::operator = (Fecha f2){
	diasDesde0 = f2.diasDesde0;
}
