#include <iostream>
#include <array>

using namespace std;

void showMatrix(array<array<double, 6>,6> arr)
{
    for(array<double,6> i: arr)
	{
        for(double j: i)
            cout << j << " ";
    
	    cout << endl;
    }
}

void thompsonStepOne(array<array<double, 6>,6> &);

void thompsonStepTwo(array<double, 6>&, array<array<double,6>,6>);

void thompsonStepThree(array<array<double,6>,6>, array<double,6>);

int main()
{
    array<array<double, 6>, 6> matrixA;
    for(int i = 0;i<6;i++)
	{
        for(int j = 0; j<6;j++)
		{
            matrixA[i][j] = 0.0;
        }
    }
    
    matrixA.at(0).at(0) = 30; matrixA.at(0).at(1) = 2.0/3.0;
    matrixA.at(1).at(0) = 3.0/4.0; matrixA.at(1).at(1) = 20.0; matrixA.at(1).at(2) =5.0/6.00;
    matrixA.at(2).at(1) = 7.0/8.0; matrixA.at(2).at(2) = 10.0; matrixA.at(2).at(3) = 9.0/10.0;
    matrixA.at(3).at(2) = 11.0/12.0; matrixA.at(3).at(3) = 10.0; matrixA.at(3).at(4) =13.0/14.0;
    matrixA.at(4).at(3) = 15.0/16.0; matrixA.at(4).at(4) = 20.0; matrixA.at(4).at(5) = 17.0/18.0;
    matrixA.at(5).at(4) = 19.0/20.0; matrixA.at(5).at(5) = 30.0;
    
    array<double, 6> vectorB;
    vectorB.at(0) = 94.0 / 3.0;
    vectorB.at(1) = 173.0 / 4.0;
    vectorB.at(2) = 581.0 / 20.0;
    vectorB.at(3) = -815.0 / 28.0;
    vectorB.at(4) = -6301.0 / 144.0;
    vectorB.at(5) = -319.0 / 10.0;
    thompsonStepOne(matrixA);
    thompsonStepTwo(vectorB, matrixA);
    thompsonStepThree(matrixA, vectorB);
    return 0;
}


void thompsonStepOne(array<array<double, 6>,6> & matrixA){
    for(int i = 1; i<6;i++)
        matrixA.at(i).at(i) = matrixA[i][i] - matrixA[i][i-1]*(1.0/matrixA.at(i-1).at(i-1))*matrixA[i-1][i];
}

void thompsonStepTwo(std::array<double, 6> & vectorB, array<array<double, 6>, 6> matrixA)
{
    for(int i = 1; i<6; i++)
	{
        vectorB.at(i) = vectorB.at(i) - matrixA.at(i).at(i-1)*(1.0/matrixA.at(i-1).at(i-1))*vectorB.at(i-1);
    }
}

void thompsonStepThree(array<array<double,6>,6> matrixA, array<double,6> vectorB){
   array<double, 6> x;
   x[5] = (1.0 / matrixA.at(5).at(5)) * vectorB.at(5);
   for(int i = 4; i >= 0; i--)
   {
       x[i] = (1.0 / matrixA.at(i).at(i)) * (vectorB.at(i) - matrixA.at(i).at(i+1) * x.at(i+1));
   }
   std::cout<<"ROZWIAZANIE:\n";
   for(int i = 0; i < 6; i++)
   {
       cout<< x[i]<< " ";
   }
   cout << endl;
}
