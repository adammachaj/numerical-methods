#include <iostream>
#include <cmath>

using namespace std;

void showMatrix(double matrix[4][4])
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << "\n";
	}
}

void showVector(double vector[3])
{
	for(int i = 0; i < 4; i++)
	{
		cout << vector[i] << "\n";
	}
}

void decompositionLU(double matrix[4][4],double vector[4])
{
	const int size = 4;
	double L [4][4];
	double U [4][4];
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			U[i][j] = matrix[i][j];
		}
	}
	
	cout << "Macierz A:\n";
	showMatrix(U);
	
	int N = -1;
	
	for(N += 1; N < size; N++)
	{
        L[N][N] = 1;
        //Pivoting
        if(U[N][N] == 0)
		{
            double max = 0;
            double maxIndex = N;
            for(int i = N; i < size; i++)
			{
                if(max < fabs( U[i][N] ))
				{
                    maxIndex = i;
                    max = U[i][N];
                }
            }
            
            for(int i = N; i < size; i++)
			{
                double tmp = U[N][i];
                U[N][i] = U[maxIndex][i];
                U[maxIndex][i] = tmp;
                tmp = vector[N];
                vector[N] = vector[maxIndex];
                vector[maxIndex] = tmp;
            }
        }
        
        for(int i = N+1; i < size; i++)
		{
        	L[i][N] = U[i][N] / U[N][N];
        	for(int j = N; j < size; j++)
			{
       			U[i][j] = U[i][j] - U[N][j] * L[i][N];
       		}
       	}
	}
	cout<<"U matrix:\n";
    showMatrix(U);
    cout<<"L matrix:\n";
    showMatrix(L);
    cout<<"Vector B:\n";
    showVector(vector);
    //Vector part
    
    std::array<double,4> x, y;
    int x [4];
    int y [4];
    
    for(int i = 0; i<size; i++)
	{
        double sum = 0;
        for(int j = 0; j < i; j++)
		{
            sum+=L[i][j] * y[j];
        }
        y[i] = (vector[i] - sum) / L[i][i];
    }
    
    for(int i = (size-1); i>=0; i--)
	{
        double sum = 0;
        
        for(int j = i+1; j<size; j++)
		{
            sum+=U[i][j]*x[j];
        }
        
        x[i]=(y[i] - sum)/U[i][i];
    }
    
    std::cout<<"Rozwiazanie:\n";
    showVector(x);
}

int main()
{
	double matrixA [4][4];
	matrixA[0][0] = 1; 	matrixA[0][1] = 20; 	matrixA[0][2] = -30; 	matrixA[0][3] = -4; 
	matrixA[1][0] = 4; 	matrixA[1][1] = 20; 	matrixA[1][2] = -6; 	matrixA[1][3] = 50; 
	matrixA[2][0] = 9; 	matrixA[2][1] = -18; 	matrixA[2][2] = 12; 	matrixA[2][3] = -11; 
	matrixA[3][0] = 16; matrixA[3][1] = -15; 	matrixA[3][2] = 14; 	matrixA[3][3] = 130; 
	
	double vectorB [4];
	vectorB[0] = 0; vectorB[1] = 114; vectorB[2] = -5; vectorB[3] = 177;
}
