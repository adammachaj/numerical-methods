#include <iostream>
#include <cmath>

using namespace std;
const double e = 1e-8;
const int i_max = 100;

using namespace std;

double funkcja1(double x, double y, double z){return x * x + y * y + z * z - 2.0;}
double funkcja2(double x, double y){return x * x + y * y - 1.0;}
double funkcja3(double x, double y){return x * x - y;}

double max(double x, double y, double z)
{
	if(x > y && x > z)
		return x;
	
	else if(y > x && y > z)
		return y;
		
	else 
		return z;
}

void alg(double x, double y, double z)
{
//estymator (sprawdzenie bledu x, reziddum bledu y, wyznacznk - wyznacznik rownania
	double estymator, reziduum, wyznacznik_odwrotny;

	//wartosci piszczegolnych rownan w kroku
	auto *wartosci = new double[3];

	//jakobian przeksztalcenia oznaczony J^-1
	auto **macierz_j = new double *[3];

	for (int i = 0; i < 3; i++){
		macierz_j[i] = new double[3];
	}

	//roznica miedzy dwoma kolejnymi przyblizeniami (poprawka)
	auto *delta = new double[3];

	wartosci[0] = funkcja1(x, y, z);
	wartosci[1] = funkcja2(x, y);
	wartosci[2] = funkcja3(x, y);

	cout << "i" << " " << "x" << "\t\t\t\t\t\t " << "y" << "\t\t\t\t\t\t" << "z" << "\t\t\t\t\t   " << "estymator"
		 << "\t\t\t  " << "reziduum" << endl;

	for (int i = 0; i < i_max; i++){
		//zerujemy macierz delta[]
		fill(delta, delta + 3, 0);
		if (!x || !z){
			cout << "Dzielenie przez zero" << endl;
			break;
		}
		wyznacznik_odwrotny = 1 / ((-4 * x * z) - (8 * x * y * z));

		macierz_j[0][0] = 0;
		macierz_j[0][1] = (-2 * z) * wyznacznik_odwrotny;
		macierz_j[0][2] = (-4 * y * z) * wyznacznik_odwrotny;
		macierz_j[1][0] = 0;
		macierz_j[1][1] = (-4 * x * z) * wyznacznik_odwrotny;
		macierz_j[1][2] = (4 * x * z) * wyznacznik_odwrotny;
		macierz_j[2][0] = (-2 * x - 4 * x * y) * wyznacznik_odwrotny;
		macierz_j[2][1] = (2 * x + 4 * x * y) * wyznacznik_odwrotny;
		macierz_j[2][2] = 0;

		/*
		 * Wyznaczamy deltê poprzez mno¿enie macierzy jakobianu i wartoœci (ze wzoru)
		 * Oznacza to ¿e musimy wykonaæ standardowe mno¿enie macierzy (1) ilosæ kolumn = (2) iloœæ wierszy
		 */
		for (int j = 0; j < 3; j++){
			for (int k = 0; k < 3; k++){
				delta[j] = delta[j] + (macierz_j[j][k] * wartosci[k]);
			}
		}

		//odejmujemy roznice
		x = x - delta[0];
		y = y - delta[1];
		z = z - delta[2];

		//przypisujemy nowe wartosci
		wartosci[0] = funkcja1(x, y, z);
		wartosci[1] = funkcja2(x, y);
		wartosci[2] = funkcja3(x, y);

		//obliczamy estymator i reziduum dla normy inf
		estymator = max(fabs(delta[0]), fabs(delta[1]), fabs(delta[2]));
		reziduum = max(fabs(wartosci[0]), fabs(wartosci[1]), fabs(wartosci[2]));

		cout << i << " " << x << " " << y << " " << z << " " << estymator << " " << reziduum << endl;

		//badamy warunki zakonczenia iteracji
		if (fabs(reziduum) < e) break;
		if (fabs(estymator) < e) break;
	}
}

int main()
{
	cout.setf(ios::scientific);
	cout.precision(16);

	// x ~ +-0.786151, y ~ 0.618034, z = +- 1
	algNewtona(1.0, 2.0, 3.0);
	return 0;
}
