class Fecha{
	private: 
		int diasDesde0;
	public: 
		Fecha();
		Fecha(int, int, int);

		int operator - (Fecha fecha);
		friend bool operator > (Fecha, Fecha);
		friend bool operator == (Fecha, Fecha);
		friend ostream& operator << (ostream&, Fecha);
		void operator =(Fecha b);
};
Fecha::Fecha(){
	diasDesde0 = 0;
}
Fecha::Fecha(int dd, int mm, int aaaa){
	//Formula para convertir de calendario gregoriano y a juliano.
	diasDesde0 = 1461 * (aaaa + 4800 + (mm - 14) / 12) / 4 +
		367 * (mm - 2 - (mm - 14) / 12 * 12) / 12 - 
		3 * ((aaaa + 4900 + (mm - 14) / 12) / 100) / 4 + 
		dd - 1753135;	
	//obtenida de usno.navy.mil
}

int Fecha::operator-(Fecha fecha)
{
	if(fecha > *this || fecha == *this)
		throw invalid_argument("El sustraendo debe ser menor al minuendo.");
	return diasDesde0 - fecha.diasDesde0 - 1;//Porque el profesor pidio que fueran los dias entre las fechas.
}
bool operator > (Fecha f1, Fecha f2){
	return (f1.diasDesde0>f2.diasDesde0) ? true:false;	
}
bool operator == (Fecha f1, Fecha f2){
	return (f1.diasDesde0==f2.diasDesde0) ? true:false;	
}
// Output con la formula que encontro Freddy
// Despejo la formula para convertir del calendario gregoriano a julinao para hacer el 
// proceso inverso. Nuevamente, cortesia de la misma fuente. 
ostream& operator<<(ostream& stream, Fecha fecha)
{
	string month[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", 
						"Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
	int x, n, i, j, d, m, y;
	x = fecha.diasDesde0 + 1789629;
	n = 4 * x / 146097;
	x -= (146097 * n + 3) / 4;
	i = (4000 * (x + 1)) / 1461001;
	x -= 1461 * i / 4 - 31;
	j = 80 * x / 2447;
	d = x - 2447 * j / 80;
	x = j / 11;
	m = j + 2 - 12 * x;
	y = 100 * (n - 49) + i + x;
	return stream << setfill('0') << setw(2) <<
	d << " de " <<
	month[m-1] << " de " <<
	setw(4) <<
	y;
}
/*
 * Aunque funciona, llegamos a la conclusion de que el algoritmo que ya implementamos en el constructor de la clase
 * es mas eficiente, o por lo menos se ve mas limpio. Es por esto que lo vamos a utilizar.
//Output de Marcelo. Despues de varios intentos logramos que funcionara. Resulta que le faltaba agregar un dia al mes de febrero.
ostream& operator << (ostream &os, Fecha fe)
{
   int d, m, a,suma=0, l=0;
   double diasr; 
   int arr[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
   string month[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    a = fe.diasDesde0 / 365;
    diasr = fe.diasDesde0 % 365;
    diasr -= ((a/4.0) - (a/100.0) + (a/400.0));
    while (diasr < 0 )
    {
        a--;
        diasr += 365;
    }
    do
    {
        suma += arr[l];
        l++;
    }
    while(suma < diasr);
//en enero y en febrero este algoritmo est'a dando un d'ia menos. 
    m = l;
    d = suma - diasr;
    d = arr[l-1] - d;
	if(m==2 && (a%4==0 && a%100!=0 || a%100==0 && a%400==0) ) d+=1;
    os << setfill('0') << setw(2) << d << "/" << setfill('0') << setw(2) << month[m-1] << "/" << setfill('0') << setw(4) << a;
    return os;
}
*/
void Fecha::operator =(Fecha b){
	diasDesde0 = b.diasDesde0;
}
