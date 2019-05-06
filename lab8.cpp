#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cmath>

template <class T>
	T fun(T x)
	{
		return cos(x / 2.0);
	}

template <class T>

    T forawardDifference(T h, T a, T b, T x){
    	
        if(h!=0 && x>a && x<b){
            return (fun(x+h) - fun(x))/h;
        }
        return -100;
    }

template <class T>
   
    T backwardDifference(T h, T a, T b, T x){
        if(h!=0 && x>a && x<b){
            return (fun(x)-fun(x-h))/h;
        }
        return -100;
    }
template <class T>    
    T centralDifference(T h, T a, T b, T x){
        if(h!=0 && x>a && x<b){
            return (fun(x+h) - fun(x-h))/(2*h);
        }
        return -100;
    }
    
    //To calculate derivative where x is in first or end node pochodna dla pkt końcowego
    template <class T>
    T firstOrEndNodeDerivativeTwoPoint(T h, T a, T b, T x){
        if(h!=0 && x==a){
            return (fun(a+h)-fun(a))/h;
        }
        else if(h!=0 && x==b){
            return (fun(b)-fun(b-h))/h;
        }
        return -100;
    }
    template <class T>
    T firstOrEndNodeDerivativeThreePoint(T h, T a, T b, T x){
        if(h!=0 && x==a){
            return (-3.0/2.0*fun(a)+2*fun(a+h)-0.5*fun(a+2*h))/h;
        }
        else if(h!=0 && x==b){
            return (0.5*fun(b-2*h)-2*fun(b-h)+3.0/2.0*fun(b))/h;
        }
        return -100;
    }


template <typename T>
T difference(T x){
    return -sin(x/2.0)*1.0/2.0;
}

void plot();
 
int main(){
	double a = 0;
	double b = M_PI;
	double x = M_PI / 2.0;
    const double stepD = 0.000001;
    const double difABD = difference(M_PI/2.0);
    std::vector<double> forwDiffD, backwDiffD, centralDiffD, firstDiffTwoPointD,
                  firstDiffThreePointD, lastDiffTwoPointD, lastDiffThreePointD;
    for(double h = stepD; h<1.4; h+=stepD*100000){
        forwDiffD.push_back(fabs(difABD-forawardDifference<double>(h, a, b, x)));
        backwDiffD.push_back(fabs(difABD-backwardDifference<double>(h, a, b, x)));
        centralDiffD.push_back(fabs(difABD-centralDifference<double>(h, a, b, x)));
    }
    const double difAD = difference(0);
    
    for(double h = stepD; h<1.4; h+=stepD*100000){
        firstDiffTwoPointD.push_back((difAD-firstOrEndNodeDerivativeTwoPoint(h, a, b, a)));
        firstDiffThreePointD.push_back(fabs(difAD-firstOrEndNodeDerivativeThreePoint(h, a, b, a)));
    }
    const double difBD = difference(M_PI);
    for(double h = stepD; h<1.4; h+=stepD*100000){
        lastDiffTwoPointD.push_back(fabs(difBD-firstOrEndNodeDerivativeTwoPoint(h, a, b, b)));
        lastDiffThreePointD.push_back(fabs(difBD-firstOrEndNodeDerivativeThreePoint(h, a, b, b)));
    }
    std::ofstream file1;
    file1.open("dataDouble.dat");
    file1<<"H"<<" "<<"ErrorForw"<<" "<<"ErrorBack"<<" "<<
           "ErrorCent"<<" "<<"ErrorFirstTw"<<" "<<"ErrorFirstTh"<<
           " "<<"ErrorEndTw"<<" "<<"ErrorEndTh"<<std::endl;
    int i = 0;
    for(double h = stepD; h<1.4; h+=stepD*100000){
        file1 << h << " "<<forwDiffD.at(i);
        file1 <<" "<<backwDiffD.at(i);
        file1 <<" "<<centralDiffD.at(i);
        file1 <<" "<<firstDiffTwoPointD.at(i);
        file1 <<" "<<firstDiffThreePointD.at(i);
        file1 <<" "<<lastDiffTwoPointD.at(i);
        file1 <<" "<<lastDiffThreePointD.at(i)<<std::endl;
        i++;
    }
    file1.close();
    std::cout<<difference(0)<<" "<<difference(M_PI)<<" "<<difference(M_PI/2.0)<<std::endl;
    const float step = 0.000001;
    const float DIFAB = difference(M_PI/2.0);
    std::vector<float> forwDiff, backwDiff, centralDiff, firstDiffTwoPoint,
                  firstDiffThreePoint, lastDiffTwoPoint, lastDiffThreePoint;
    
	float a1 = 0;
	float b1 = M_PI;
	float x1 = M_PI / 2.0;              
    
    for(float h = step; h<1.4; h+=step*100000){
        forwDiff.push_back(fabs(DIFAB-forawardDifference(h, a1, b1, x1)));
        backwDiff.push_back(fabs(DIFAB-backwardDifference(h, a1, b1, x1)));
        centralDiff.push_back(fabs(DIFAB-centralDifference(h, a1, b1, x1)));
    }
    const float DIFA = difference(0);
    //diff.changeX(0.0);
    for(float h = step; h<1.4; h+=step*100000){
        firstDiffTwoPoint.push_back((DIFA-firstOrEndNodeDerivativeTwoPoint(h, a1, b1, a1)));
        firstDiffThreePoint.push_back(fabs(DIFA-firstOrEndNodeDerivativeThreePoint(h, a1, b1, a1)));
    }
    const float DIFB = difference(M_PI);
    for(float h = step; h<1.4; h+=step*100000){
        lastDiffTwoPoint.push_back(fabs(DIFB-firstOrEndNodeDerivativeTwoPoint(h, a1, b1, b1)));
        lastDiffThreePoint.push_back(fabs(DIFB-firstOrEndNodeDerivativeThreePoint(h, a1, b1, b1)));
    }
    file1.open("dataFloat.dat");
    file1<<"H"<<" "<<"ErrorForw"<<" "<<"ErrorBack"<<" "<<
           "ErrorCent"<<" "<<"ErrorFirstTw"<<" "<<"ErrorFirstTh"<<
           " "<<"ErrorEndTw"<<" "<<"ErrorEndTh"<<std::endl;
    i = 0;
    for(float h = step; h<1.4; h+=step*100000){
        file1 << h << " "<<forwDiff.at(i);
        file1 <<" "<<backwDiff.at(i);
        file1 <<" "<<centralDiff.at(i);
        file1 <<" "<<firstDiffTwoPoint.at(i);
        file1 <<" "<<firstDiffThreePoint.at(i);
        file1 <<" "<<lastDiffTwoPoint.at(i);
        file1 <<" "<<lastDiffThreePoint.at(i)<<std::endl;
        i++;
    }
    file1.close();
    
    plot();
    
    return 0;
}
 
 
//Do wykresow

class Gnuplot{
public:
    Gnuplot();
    ~Gnuplot();
    void operator () (const std::string & command);
protected:
    FILE *gnuplotpipe;
};

 
Gnuplot::Gnuplot(){
    gnuplotpipe = popen("C:\ProgramFiles\gnuplot\bingnuplot.exe", "w");
    if(!gnuplotpipe)
        std::cerr<<("Gluplot not found!");
}
Gnuplot::~Gnuplot(){
    fprintf(gnuplotpipe, "exit\n");
    pclose(gnuplotpipe);
}
void Gnuplot::operator() (const std::string &command){
    fprintf(gnuplotpipe, "%s\n", command.c_str());
    fflush(gnuplotpipe);
}
 
 
void plot(){
    Gnuplot plt;
    plt("set term postscript eps color");
    plt("set output \"a.eps\" ");
    plt("set logscale xy");
    plt("plot \'dataDouble.dat' u 1:2 w l lt rgb 'greenyellow' t 'forward', \
              \'dataDouble.dat\' u 1:3 w l lt rgb 'light-pink' t 'backward', \
              \'dataDouble.dat\' u 1:4 w l lt rgb 'black' t 'central', \
              \'dataDouble.dat\' u 1:5 w l lt rgb 'royalblue' t 'firstNTwo', \
              \'dataDouble.dat\' u 1:6 w l lt rgb 'orangered4' t 'firstNThree', \
              \'./dataDouble.dat\' u 1:7 w l lt rgb 'dark-magenta' t 'lastNTwo', \
              \'./dataDouble.dat\' u 1:8 w l lt rgb 'salmon' t 'lastNThree'");
    plt("plot \'./dataFloat.dat\' u 1:2 w l lt rgb 'greenyellow' t 'forward', \
              \'./dataFloat.dat\' u 1:3 w l lt rgb 'light-pink' t 'backward', \
              \'./dataFloat.dat\' u 1:4 w l lt rgb 'black' t 'central', \
              \'./dataFloat.dat\' u 1:5 w l lt rgb 'royalblue' t 'firstNTwo', \
              \'./dataFloat.dat\' u 1:6 w l lt rgb 'orangered4' t 'firstNThree', \
              \'./dataFloat.dat\' u 1:7 w l lt rgb 'dark-magenta' t 'lastNTwo', \
              \'./dataFloat.dat\' u 1:8 w l lt rgb 'salmon' t 'lastNThree'");
}
