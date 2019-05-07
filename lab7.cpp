#include <iostream>
#include <string>
#include <cmath>
#include <array>
  
using namespace std;

int N=4;

double E = 10e-7;
double R = 10e-5;
double O = 1.0/2.0;

void showMatrix(array<array<double, 4>, 4> arr)
{
	for(int i = 0; i<4;i++)
	{
		for(int j=0; j<4;j++)
		{
			cout<<arr[i][j]<<" ";
		}
		cout<<endl;
	}
}

void showVector(array<double, 4> vector)
{
	for(int i = 0; i < 4; i++)
	{
		cout << vector[i] <<"\t";
	}
	cout<<endl;
}

double maxVector(array<double, 4> vector)
{
	double max = vector[0];
	
	for(int i = 1; i < N; i++)
	{
		if(vector[i] > max)
		{
			max = vector[i];
		}
	}
	return max;
}

bool estymator(array<double, 4> Xo, array<double, 4> Xn)
{
	array<double, 4> h;
	
	for(int i = 0; i < N; i++)
	{
		h[i] = fabs(Xo[i] - Xn[i]);
	}
	cout<<"Estymator bledu: \t";
	
	showVector(h);
	
	if(maxVector(h) < E)
	{
		cout<<"Koniec spowodowany estymatorem bledu, rozw: ";
		showVector(Xn);
		return true;
	}
	return false;
}

bool residuum(array<double, 4> Xn)
{
	array<double, 4>  h;
	h[0] = fabs(100*Xn[0] + Xn[1] - 2*Xn[2] + 3 * Xn[3] - 395);
	h[1] = fabs(4*Xn[0] + 300*Xn[1] - 5*Xn[2] + 6 * Xn[3] - 603);
	h[2] = fabs(7*Xn[0] - 8*Xn[1] - 400*Xn[2] + 9*Xn[3] - 385);
	h[3] = fabs(-10*Xn[0] + 11*Xn[1] - 12*Xn[2] + 200 * Xn[3] + 606);
	cout<<"Estymator residuum: \t";
	showVector(h);
	if(maxVector(h) < R)
	{
		cout<<"Koniec spowodowany residuum, rozw: ";
		showVector(Xn);
		return true;
	}
	return false;
}

void jacobi(array<array<double, 4>, 4> L, array<array<double, 4>, 4> D, array<array<double, 4>, 4> U, array<double, 4> vector, array<double, 4> X)
{
	array<double, 4> c, Xn, Xo;
	double mx;
	array<array<double, 4>, 4> m;
	
	for(int i = 0; i < N; i++)
	{
		Xn[i] = X[i];
	}
	// D^-1
	for(int i = 0; i < N; i++)
	{
		D[i][i] = 1 / D[i][i];
	}
	//C
	for(int i = 0; i < N; i++)
	{
		c[i] = D[i][i] * vector[i];
	}
	//M
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			m[i][j] = D[i][i] * (L[i][j] + U[i][j]); 
		}
	}
	for(int i = 0; i < 100; i++)
	{
		cout<<"Iteracja : "<<i<<endl;
		for(int p=0; p<N; p++){Xo[p] = Xn[p];}
		for(int j=0; j<N; j++)
		{
			mx = 0;
			for(int k=0; k<N; k++)
			{
				if(k != j)
				{
					mx +=m[j][k] * Xo[k];
				}
			}
			Xn[j] = c[j] - mx;
			
		}
		if(estymator(Xo, Xn) || residuum(Xn))
		{
			break;
		}
		
	}
	
	
}
void gauss(array<array<double, 4>, 4> tab, array<double, 4> vector, array<double, 4> X)
{
	array<double, 4> Xn, Xo;
	for(int i=0; i<N; i++)
	{
		Xn[i] = X[i];
	}
	for(int i=0; i<100; i++)
	{
		cout<<"Iteracja : "<<i<<endl;
		for(int p=0; p<N; p++){Xo[p] = Xn[p];}
		for(int j=0; j<N; j++)
		{
			double p[2];
			p[0] = p[1] = 0;
			Xn[j] = 0;
			for(int k=0; k<N; k++)
			{
				if(j !=k)
				{
					if(k < j)
					{
						p[0] += tab[j][k] * Xn[k];
					}
					else{
						p[1] += tab[j][k] * Xo[k];
					}
				}
			}
			Xn[j] = (vector[j] - p[0] - p[1]) / tab[j][j];
		}
		if(estymator(Xo, Xn) || residuum(Xn))
		{
			break;
		}
	}
}
void sor(array<array<double, 4>, 4> tab, array<double, 4> vector, array<double, 4> X)
{
	array<double, 4> Xn, Xo;
	for(int i=0; i<N; i++)
	{
		Xn[i] = X[i];
	}
	for(int i=0; i<100; i++)
	{
		cout<<"Iteracja : "<<i<<endl;
		for(int p=0; p<N; p++){Xo[p] = Xn[p];}
		for(int j=0; j<N; j++)
		{
			double p[2];
			p[0] = p[1] = 0;
			for(int k=0; k<N; k++)
			{
				if(k != j)
				{
					if(k < j)
					{
						p[0] += tab[j][k] * Xn[k];
					}
					else{
						p[1] += tab[j][k] * Xo[k];
					}
				}
			}
			Xn[j] = (1 - O) * Xo[j] - O*(p[0] + p[1] - vector[j]) / tab[j][j];
		}
		if(estymator(Xo, Xn) || residuum(Xn))
		{
			break;
		}
		
	}
}

int main()
{
	array<array<double, 4>, 4> arr;
    arr[0][0] = 100.0;	arr[0][1] = 1.0;		arr[0][2] = -2.0; 	arr[0][3] = 3.0;
    arr[1][0] = 4.0;		arr[1][1] = 300.0;	arr[1][2] = -5.0;		arr[1][3] = 6.0;
	arr[2][0] = 7.0;		arr[2][1] = -8.0; 	arr[2][2] = 400.0;	arr[2][3] = 9.0;
	arr[3][0] = -10.0;	arr[3][1] = 11.0; 	arr[3][2] = -12.0; 	arr[3][3] = 200.0;
				  			        
    array<double, 4> vec;
    vec[0] = 395.0; vec[1] = 603.0; vec[2] = -415.0; vec[3] = -606.0;
    
    array<double, 4> Xo; 
	for(int i = 0; i < 4; i++)
	{
		Xo[i] = 1;
	}
	
	array<array<double, 4>, 4> L, D, U;
    
    for(int i = 0; i < 4; i++)
    {
    	for(int j = 0; j < N; j++)
      	{
      		L[i][j] = 0;
      		U[i][j] = 0;
      		if(i == j)
      		{
      			D[i][j] = arr[i][j];
			}
			
			if(i < j)
      		{
      			U[i][j] = arr[i][j];
			}
			
			if(i > j)
      		{
      			L[i][j] = arr[i][j];
			}
		}
	  }
	  
      cout << "JACOBI" << endl;
      jacobi(L, D, U, vec, Xo);
      cout << endl << "Gauss" << endl;
      gauss(arr, vec, Xo);
      cout << endl << "Sor" << endl;
      sor(arr, vec, Xo);
	  
      return 0;
  }
