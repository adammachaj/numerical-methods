#include <iostream>
#include <cmath>

using namespace std;
const double e = 1e-8;
double residuum = 1e-10;
const int i_max = 100;

using namespace std;

double funkcja1(double x, double y, double z){return x * x + y * y + z * z - 2.0;}
double funkcja2(double x, double y){return x * x + y * y - 1.0;}
double funkcja3(double x, double y){return x * x - y;}

double f1px(double x){
    return 2*x;
}
double f1py(double y){
    return 2*y;
}
double f1pz(double z){
    return 2*z;
}

double f2px(double x){
    return 2*x;
}
double f2py(double y){
    return 2*y;
}
double f2pz(){
    return 0;
}
double f3px(double x){
    return 2*x;
}
double f3py(){
    return -1;
}
double f3pz(){
    return 0;
}

double det(double matrix[3][3])
{
    double d = matrix[0][0]*matrix[1][1]*matrix[2][2] +
               matrix[1][0]*matrix[2][1]*matrix[0][2] +
               matrix[2][0]*matrix[0][1]*matrix[1][2] -
               matrix[0][2]*matrix[1][1]*matrix[2][0] -
               matrix[1][2]*matrix[2][1]*matrix[0][0] -
               matrix[2][2]*matrix[0][1]*matrix[1][0];
}

void showVector(double array[3])
{
	for(int i = 0; i < 3; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

void alg(double x, double y, double z)
{
	double newVectorX [3];
	double oldVectorX [3];
	
	newVectorX [0] = x;	//
	newVectorX [1] = y;
	newVectorX [2] = z;
	
	double valuesVector[3]; //vector wartosci funkcji (x, y, z)
	double jacobian[3][3];
    
    for(int i = 0; i < 100; i++)
	{
        for(int i = 0; i < 3; i++)
		{
            oldVectorX[i] = newVectorX[i];
        }
        
        valuesVector[0] = funkcja1(oldVectorX[0], oldVectorX[1], oldVectorX[2]);	//F(x, y, z)
        valuesVector[1] = funkcja2(oldVectorX[0], oldVectorX[1]);					//F(x, y)
        valuesVector[2] = funkcja3(oldVectorX[0], oldVectorX[1]);					//F(x, y)
        
        //Jacobian
        jacobian[0][0] = f1px(oldVectorX[0]); jacobian[0][1] = f1py(oldVectorX[1]); jacobian[0][2]=f1pz(oldVectorX[2]);
        jacobian[1][0] = f2px(oldVectorX[0]); jacobian[1][1] = f2py(oldVectorX[1]); jacobian[1][2]=f2pz();
        jacobian[2][0] = f3px(oldVectorX[0]); jacobian[2][1] = f3py(); jacobian[2][2]=f3pz();


		//macierze pomocnicze do wyznacznia det
		//wyznacznik z jacobiego
		double array1 [3][3];
        double array2 [3][3];
        double array3 [3][3];
        
        for(int i = 0; i < 3; i++)
        {
        	for(int j = 0; j < 3; j++)
        	{
        		array1[i][j] = jacobian[i][j];
        		array2[i][j] = jacobian[i][j];
        		array3[i][j] = jacobian[i][j];
			}
		}
        
        //zamiana kolumn
        for(int i = 0; i < 3; i++)
		{
            array1[i][0] = valuesVector[i];
            array2[i][1] = valuesVector[i];
            array3[i][2] = valuesVector[i];
        }
        
        double detA = det(jacobian);
        double detAx0 = det(array1);
        double detAx1 = det(array2);
        double detAx2 = det(array3);
        
        newVectorX[0] = oldVectorX[0] - detAx0/detA;
        newVectorX[1] = oldVectorX[1] - detAx1/detA;
        newVectorX[2] = oldVectorX[2] - detAx2/detA;
        
        cout<< endl <<"Iteracja numer " << i <<".->";
        showVector(newVectorX);
        double error[3]; 
		error[0] = fabs(newVectorX[0] - oldVectorX[0]);
        error[1] = fabs(newVectorX[1] - oldVectorX[1]);
        error[2] = fabs(newVectorX[2] - oldVectorX[2]);
        cout << "Wartosci funkcji" << endl;
        showVector(valuesVector);
        cout << "Blad przyblizenia" << endl;
		showVector(error);
        
        if(error[0] < e && error[1] < e && error[2] < e)
		{
            cout<<"Blad.\n";
            cout<<"Przyblizony wynik rownania wynosi: "; showVector(newVectorX);
            return;
        }
        
        if(fabs(funkcja1(newVectorX[0], newVectorX[1], newVectorX[2]))<residuum &&
                fabs(funkcja2(newVectorX[0], newVectorX[1]))<residuum &&
                fabs(funkcja3(newVectorX[0], newVectorX[1]))<residuum){
            std::cout<< endl <<"Residuum.\n";
            std::cout<<"Przyblizony wynik rownania wynosi: "; showVector(newVectorX);
            return;
         }
    }
    std::cout<<"Koniec iteracji.\n";
    std::cout<<"Przyblizony wynik rownania wynosi: "; showVector(newVectorX);
}

int main()
{
	alg(1, 2, 3);
}
