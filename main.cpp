#include <iostream>
#include <windows.h>
#include <math.h>

using namespace std;


double equation(double x){
	return ( sin(x) );
}

double begin;
double end;
double size_x;
double size_y;

int main()
{
	//ustawienia okna
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
    SMALL_RECT sr;
 
    sr.Left = 0;
    sr.Top = 0;
    sr.Right = 100;
    sr.Bottom = 40;
    SetConsoleWindowInfo(handle,true,&sr);
	
	cin >> begin;
	cin >> end;

	int steps = 100;

	cout <<"begin: " << begin << endl;
	cout <<"end: " << end << endl;
	double step = (end - begin) / 100.0;
	cout <<"step: " << step << endl;
	cout <<"steps: " << steps << endl;
	
	int j = 1;
	for(double i = begin; i < steps; i += step)
	{
		cout << j << ". "  << i << endl;
		j++;
	}
	
	
//	int j = 1;
//	for(double i = begin; i < end / 100; i += step)
//	{
//		cout << j << ". " << "x = " << i << ", f(x) = " << equation(i) << endl;
//		j++;
//	}
}
