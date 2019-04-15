#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void decompositionLU(array<array<double, 4>,4>, array<double, 4>);

void showMatrix(array<array<double, 4>,4> matrix)
{
    for(array<double, 4> vector: matrix)
	{
        for(double number: vector)
		{
            cout<<number<<"\t\t";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

void showVector(array<double, 4> vect)
{
    for(double x : vect)
	{
        cout<<x<<" ";
    }
    cout<<"\n\n";
}

int main(){
    //A
    //1 20 -30 -4
    //4 20 -6 50
    //9 -18 12 -11
    //16 -15 14 130
    array<array<double, 4>,4> matrixA;
    matrixA.at(0).at(0) = 1; matrixA.at(0).at(1) = 20; matrixA.at(0).at(2) = -30; matrixA.at(0).at(3) = -4;
    matrixA.at(1).at(0) = 4; matrixA.at(1).at(1) = 20; matrixA.at(1).at(2) = -6; matrixA.at(1).at(3) = 50;
    matrixA.at(2).at(0) = 9; matrixA.at(2).at(1) = -18; matrixA.at(2).at(2) = 12; matrixA.at(2).at(3) = -11;
    matrixA.at(3).at(0) = 16; matrixA.at(3).at(1) = -15; matrixA.at(3).at(2) = 14; matrixA.at(3).at(3) = 130;
    //B
    //0, 114, -5, 177
    array<double, 4> vectorB;
    vectorB.at(0) = 0; vectorB.at(1) = 114; vectorB.at(2) = -5; vectorB.at(3) = 177;
    decompositionLU(matrixA, vectorB);
    return 0;
}

void decompositionLU(array<array<double, 4>,4> matrix, array<double, 4> vector)
{
    const int size = 4;
    array<array<double, 4>, 4> L, U;
    U = matrix;
    cout<<"Macierz A:\n";
    showMatrix(U);
    int N = -1;
    for(N += 1; N<size; N++)
	{
        L.at(N).at(N) = 1;
        //Pivoting
        if(U.at(N).at(N) == 0)
		{
            double max = 0;
            double maxIndex = N;
            
            for(int i = N; i<size; i++)
			{
                if(max<fabs(U.at(i).at(N)))
				{
                    maxIndex = i;
                    max = U.at(i).at(N);
                }
            }
            
            for(int i = N; i < size; i++)
			{
                double tmp = U.at(N).at(i);
                U.at(N).at(i) = U.at(maxIndex).at(i);
                U.at(maxIndex).at(i) = tmp;
                tmp = vector.at(N);
                vector.at(N) = vector.at(maxIndex);
                vector.at(maxIndex) = tmp;
            }
        }
        //Decomposition
        for(int i = N + 1; i < size; i++)
		{
            L.at(i).at(N) = U.at(i).at(N)/U.at(N).at(N);
            for(int j = N; j < size; j++){
                U.at(i).at(j) = U.at(i).at(j) - U.at(N).at(j) * L.at(i).at(N);
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
    array<double,4> x, y;
    for(int i = 0; i<size; i++)
	{
        double sum = 0;
        for(int j = 0; j<i; j++)
		{
            sum+=L.at(i).at(j)*y.at(j);
        }
        y.at(i) =(vector.at(i) - sum) / L.at(i).at(i);
    }
    for(int i = (size-1); i>=0; i--)
	{
        double sum = 0;
        for(int j = i+1; j<size; j++)
		{
            sum+=U.at(i).at(j) * x.at(j);
        }
        x.at(i)=(y.at(i) - sum)/U.at(i).at(i);
    }
    cout<<"Rozwiazanie:\n";
    showVector(x);
}
