#include <stdio.h> // include the standard input/output header file
// include the header file containing the function that solves the colebrook equation for the friction factor f with the secant method.
#include "secant_colebrook.h"

// main program loop
int main(){
	
	// this is used to point to the return values from the secant_colebrook function.
	float *pointerToReturnValues = NULL;
	
	// these are values that will be passed to the secant_colebrook equation.
	float roughness = 0;
	float ReynoldsNumber = 0;
	float diameter = 0;
	
	pointerToReturnValues = secant_colebrook();
	
	// save the 
	float frictionFactor = *pointerToReturnValues;
	float secantSuccess  = *(pointerToReturnValues+1);
	
	
	return 0;
}
