#ifndef _TEMPLATE_FUNCTIONS_
#define _TEMPLATE_FUNCTIONS_

#include "../complexObject/complex.h"

//functions used in hw1_template.cpp

template <class floatType>
floatType fillRange(floatType* Axis, floatType LOW, floatType HI, int DIM){
	floatType delta = (HI-LOW)/float(DIM-1); //note the '-1' is required to fill whole range
	for(int i=0; i<DIM; i++){
		Axis[i] = LOW + floatType(i)*delta;
	}
	return delta;
}


//here we are using a funtion as a parameter
//described here: http://stackoverflow.com/questions/9410/how-do-you-pass-a-function-as-a-parameter-in-c
template <class floatType>
void fillPropagator1D(complex<floatType>* K,,floatType dX, floatType dT,floatType h, floatType m, floatType (*V_Fxn)(floatType),floatType* Xpos, int DIM){
	//some propagator code...
	complex<floatType> A;
	A.a = 0.0f;//real part
	A.b = 1.0f;//complex part UPDATE THIS!!
	for (int i=0; i<DIM; i++) {
		for (int j=0; j<DIM; j++) {
			floatType argument = dT/h*( m/2.0 * pow((xj-xi)/dT,2.0) - (*V_Fxn)( (xj+xi)/2.0 ) ) ;
			//compute complex number exp[i * arg] = cos(arg) + i*sin(arg)
			complex<floatType> Kelement;
			complex<floatType> preFactor = cDiv(dX,A);
			Kelement.a = preFactor.a*cos(argument);//real
			Kelement.b = preFactor.b*sin(argument);//complex part
			
			K[i][j]= Kelement; //dX is added ALREADY see notes...
		}
	}
}

//computes normalized initial wave function
template <class floatType>
void fillGaussianFxn(complex<floatType>* psi,floatType norm, floatType x0, floatType sigma, FLOAT* xAxis, int DIM){
	
	FLOAT sigmaSquared = sigma*sigma; //whatever you want really
	for(int i=0; i<DIM; i++){
		psi[i].a = norm*exp(pow(xAxis[i]-x0,2.0)/sigmaSquared);
		psi[i].b = 0.0;
	}
	
}

FLOAT expectationX(complex<FLOAT>* psi,FLOAT* xAxis,FLOAT dX, int DIM){
	
	//<x> = integrate[conj(psi) x psi]
	FLOAT sum = 0.0f;
	
	for (int i=0; i<DIM; i++) {
		sum += dX*xAxis[i]*(psi[i].a*psi[i].a+psi[i].b*psi[i].b);//x[i]*Conj(psi)*psi = x[i]*cMag(psi)^2
	}
}


#endif