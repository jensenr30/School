#include <stdio.h> // include the standard input/output header file

// include the header file containing the function that solves the colebrook equation for the friction factor f with the secant method.
#include "secant_colebrook.h"

// main program loop
int main(){
	
	// this is used to point to the return values from the secant_colebrook function.
	float *pointerToReturnValues = NULL;
	
	// these are values that will be passed to the secant_colebrook equation.
	float ReynoldsNumber = 13743;	// unitless
	float diameter = 5;				// millimeters
	float roughness = 0.0015;		// millimeters
	
	// numerically evaluate the root of the colebrook equation given the following parameters.
	pointerToReturnValues = secant_colebrook(ReynoldsNumber, diameter, roughness);
	
	// save the return values from the secant_colebrook function
	float frictionFactor = *pointerToReturnValues;
	float secantSuccess  = *(pointerToReturnValues+1);
	
	
	// print out information to the user
	if(secantSuccess == SECANT_COLEBROOK_SUCCESS){
		printf("Friction factor = %f\nSuccess = true.\n",frictionFactor);
	}
	else{
		printf("Success = false.\n");
	}
	
	
	
	
	return 0;	// end program
}
