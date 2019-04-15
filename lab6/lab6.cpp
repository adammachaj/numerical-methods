#include <iostream>
#include <cmath>

using namespace std;

void showMatrix(double matrix[6][6])
{
	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << "\n";
	}
}

void thompsonStepOne(double matrixA[6][6])
{
    for(int i = 1; i<6;i++)
	{
        matrixA[i][i] = matrixA[i][i] - matrixA[i][i-1] * (1.0 / matrixA[i - 1][i - 1] * matrixA[i-1][i]);	
	}	
}

void thompsonStepTwo(double matrixA[6][6], double vectorB[6])
{
	for(int i = 1; i<6; i++){
        vectorB[i] = vectorB[i] - matrixA[i][i - 1] * (1.0 / matrixA[i - 1][i - 1]) * vectorB[i - 1];
    }
}

void thompsonStepThree(double matrixA[6][6], double vectorB[6])
{
	double x [6];
  	x[5] = (1.0 / matrixA[5][5]) * vectorB[5];
  	
  	for(int i = 4; i >= 0; i--)
	{
    	x[i] = (1.0/matrixA[i][i]*(vectorB[i] - matrixA[i][i] * x[i + 1]));
   	}
   	
   	cout<<"ROZWIAZANIE:\n";
   	for(int i = 0; i < 6; i++){
       cout<< x[i] <<" ";
   	}
   	
   	cout << endl;
}

int main()
{
	double matrixA [6][6];
	
	matrixA[0][0] = 30; 		matrixA[0][1] = 2.0 / 3.0; 	matrixA[0][2] = 0; 					matrixA[0][3] = 0;				matrixA[0][4] = 0;			matrixA[0][5] = 0;
	matrixA[1][0] = 3.0 / 4.0; 	matrixA[1][1] = 20.0; 		matrixA[1][2] = 5.0/6.0; 			matrixA[1][3] = 0; 				matrixA[1][4] = 0;			matrixA[1][5] = 0;
	matrixA[2][0] = 0; 			matrixA[2][1] = 7.0/8.0; 	matrixA[2][2] = 10.0; 				matrixA[2][3] = 9.0/10.0;		matrixA[2][4] = 0;			matrixA[2][5] = 0;
	matrixA[3][0] = 0; 			matrixA[3][1] = 0; 			matrixA[3][2] = 11.0/12.0; 			matrixA[3][3] = 10.0; 			matrixA[3][4] = 13.0/14.0;	matrixA[3][5] = 0;
	matrixA[4][0] = 0; 			matrixA[4][1] = 0; 			matrixA[4][2] = 0; 					matrixA[4][3] = 15.0/16.0; 		matrixA[4][4] = 20.0;		matrixA[4][5] = 17.0/18.0;
	matrixA[5][0] = 0; 			matrixA[5][1] = 0; 			matrixA[5][2] = 0; 					matrixA[5][3] = 0; 				matrixA[5][4] = 19.0/20.0;	matrixA[5][5] = 30.0;

	double vectorB [6];
	vectorB[0] = 94.0/3.0;
	vectorB[1] = 173.0/4.0;
	vectorB[2] = 581.0/20.0;
	vectorB[3] = -815.0/28.0;
	vectorB[4] = -6301.0/144.0;
	vectorB[5] = -319.0/10.0;
	
	thompsonStepOne(matrixA);
    thompsonStepTwo(matrixA, vectorB);
    thompsonStepThree(matrixA, vectorB);
}	
