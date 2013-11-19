/* main.c
 * Ryan Jensen
 * 2013-11-15 (created)
 * 2013-11-18 (last modified)
 * 
 * This program will call the secant_colebrook() function.
 * This program passes parameters to that function.
 * The function will calcuate a friction factor from those parameters.
 * The function will print the results to the user via the terminal.
*/


// include the standard input/output header file
#include <stdio.h> 
// include the header file containing the function that solves the colebrook equation for the friction factor f with the secant method.
#include "secant_colebrook.h"

// main program loop
int main(){
	
	// this is used to point to the return values from the secant_colebrook function.
	float *pointerToReturnValues = NULL;
	
	// these are values that will be passed to the secant_colebrook equation.
	float ReynoldsNumber = 8743;	// unitless
	float diameter = 5;				// millimeters
	float roughness = 0.0015;		// millimeters
	
	// numerically evaluate the root of the colebrook equation given the following parameters.
	pointerToReturnValues = secant_colebrook(ReynoldsNumber, diameter, roughness);
	
	// save the return values from the secant_colebrook function
	float frictionFactor = *pointerToReturnValues;
	float secantSuccess  = *(pointerToReturnValues+1);
	
	// print out information to the user
	printf("Friction factor = %f\n",frictionFactor);
	// print success data
	if(secantSuccess == SECANT_COLEBROOK_SUCCESS){
		printf("Success = true.\n");
	}
	else{
		printf("Success = false.\n");
	}
	
	// end program
	return 0;
}
