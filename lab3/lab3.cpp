#include <iostream>
#include <cmath>

#define NMAX 100
#define TOLF 1e-8
#define TOLX 1e-8
using namespace std;

typedef double (*function)(double);

//funkcje pierwotne
double funA(double x){return ( sin(x / 4.0) * sin(x / 4.0) - x );}
double pochA(double x){return ( (cos(x / 4.0) * sin(x / 4.0) / 2.0) - 1 );}
//pochodne funkcji
double funB(double x){return ( tan(2.0 * x) - x - 1.0 );}
double pochB(double x){return ( 1 / ((cos(2.0 * x)) * (cos(2.0 * x))) * 2.0 - 1.0 );}
//funkcja psi
double funA_pic(double x){return x;}
double funB_pic(double x){return x;}
//pochodna funkcji psi
double pochA_pic(double x){return x;}
double pochB_pic(double x){return x;}


//metoda newtona
double newton(function f, function p, double x)
{
	double x0 = x;
	double x1;
	double estymator = 0;
	for (int i = 0; i < NMAX; i++){
//		ze wzoru
		x1 = x0 - (f(x0) / p(x0));
		estymator = fabs(x0 - x1);
		x0 = x1;

		cout << "Iteracja i =" << i;
		cout << ", x1 = " << x1 << ", est = " << estymator << ", reziduum =" << f(x0) << endl;
//		warunki zakonczenia iteracji
		if (fabs(f(x0)) <= TOLF || estymator <= TOLX) break;
	}
}

//metoda picarda
double picard(function f, function p, function pic, function picP, double x)
{	
	if ( fabs( f(x) ) >= 1 )
	{
		cout << "FI'(x) >= 1. Oznacza to rozbie¿noœæ - metoda Picarda nie przybli¿y pierwiastka";
		return 0;
	}
	
	double est = 0;
	double rez = 0;
	double nx = x;

	cout << "X =" << x << endl;
	//iteracja
	for (int i = 0; i < NMAX; i++)
	{
		cout << "Nr iteracji: " << i;
		nx = pic(nx);
		cout << ", Przybli¿enie = " << nx;

		//zmiana estymatora
		est = fabs(nx - x);
		//przypisanie nowego przyblizenia
		x = nx;

		//zmiana reziduum
		rez = fabs(f(x));

		cout << ", residuum=" << rez << ", estymator bledu=" << est << endl;

//		warunki zakoczenia iteracji
		if ((rez <= TOLF) or (est <= TOLX))
			break;
	}
	return nx;
}

//metoda bisekcji
double bisekcja(function f, double a, double b)
{		
	double xn = 0;
	double est;
	
	for(int i = 0; i < 100; i++)
	{
		if ( f(a) < 0 && f (b) > 0 || f (a) > 0 && f(b) < 0 )
		{
			cout << "Wartosc f(x) na poczatku przedzialu: " << f(a) << " , na koncu: " << f(b) << endl;
			xn = (a + b) / 2.0;
			est = (b - a) / 2.0;
			cout << "a = " << a << "\tb = " << b << "\tSrodek przedzialu = " << xn << "\tReziduum = " << f(xn);
			
			if ( (f(a) < 0 && f(xn) > 0) || (f(xn) < 0 && f(a) > 0))
			{
				b = xn;
			} 
			
			else
			{
				a = xn;
			}
		}
		
		else
		{
			cout << "wartosci funkcji w tych miejscach sa roznego znaku" << endl;

		}
		
	if ((fabs(f(xn)) <= TOLF) or (fabs((b - a) / 2) <= TOLX)) 
		break;
	}
	if (!f(xn)) cout << "x0= " << xn << "(" << f(xn) << ")" << endl;
}

double sieczne(function f, double x0, double x1)
{
	double x2 = 0;
	double est = 0;
	
	cout << "X0 = " << x0 << ", X1 = " << x1 << endl;
	for (int i = 0; i < 100; i++){

		x2 = x1 - f(x1) / ((f(x1) - f(x0)) / (x1 - x0));
		est = fabs(x2 - x1);

		cout << "Numer iteracji: " << i;
		cout << ", X 2=" << x2 << ", est= " << fabs(est) << ", rez=" << fabs(f(x2)) << endl;

		x0 = x1;
		x1 = x2;

		if (fabs(f(x2)) <= TOLF or est <= TOLX) break;
	}

	return x2;
}

int main()
{
	sieczne(funA, -100, 100);
}
