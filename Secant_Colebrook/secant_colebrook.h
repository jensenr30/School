/* secant_colebrook.h
 * Ryan Jensen
 * 2013-11-15 (created)
 * 2013-11-15 (last modified)
 * 
 * This header file contains the secant_colebrook() function.
 * This function will solve the Colebrook equation for the friction factor f numerically.
*/

//used for the nice math functions like log10()
#include <math.h>


// don't debug the function unless instructed to.
#ifndef SECANT_DEBUG
#define SECANT_DEBUG 0
#endif


// this function numberically solves the Colebrook Equation for the friction factor f.
// the return value is a pointer to two floating point values.
// the first floating point number is the friction factor f
// the second floating point number is an error flag.
#define SECANT_COLEBROOK_SUCCESS 1.0f	// this is a flag that denotes success in finding a zero
#define SECANT_COLEBROOK_FAILURE 0.0f	// this is a flag that denotes a failure to find a zero
float * secant_colebrook(float ReynoldsNumber, float diameter, float roughness){
	
	///-------------------------------------------------------------------------
	///		SET UP VARIABLES
	///-------------------------------------------------------------------------
	// this is where we store the frictionFactor.
	// ffact[0] is the first guess.
	// ffact[1] is the second guess.
	// ffact[2] is the next guess.
	static float ffact[3];
	
	// this stores the difference between one side and the other side of the
	// colebrook equation. Lets call it y.
	// y[0] is for the first guess.
	// y[1] is for the second guess.
	// y[2] is for the next guess.
	float y[3];
	
	// this stores the slope of the line between.
	float slope;
	
	// this is the tolerance for relative error in our value.
	float tolerance = 0.01;
	//this stores the relative error at the current itteration
	float relativeError;
	
	// this keeps track of how many times the program has gone through the while() loop.
	int itterations;
	//this is the maximum number of times that you can go through the while() loop.
	int maxItterations = 200;
	
	// define an array of floating point values with two elements.
	// the first element will store the friction factor.
	// the second value will store the success value.
	static float returnValues[2];
	
	
	///-------------------------------------------------------------------------
	///		EVALUATE THE ROOT OF THE COLEBROOK EQUATION
	///-------------------------------------------------------------------------
	
	//initial guesses for the friction factor
	ffact[0] = 0.8;
	ffact[1] = 0.4;
	//initial value to make sure we can enter the loop
	ffact[2] = 10;
	// start itterations at 0
	itterations = 0;
	// make sure the relative error is greater than tolerance to start
	relativeError = 100*tolerance;
	
	while(relativeError > tolerance && itterations < maxItterations || ffact[2] >= 0.0){
		
		
		y[0] = (1/sqrtf(ffact[0]))  +  2*log10( (roughness/(3.7f * diameter)) + (2.51f/(ReynoldsNumber*sqrtf(ffact[0]))) );
		y[1] = (1/sqrtf(ffact[1]))  +  2*log10( (roughness/(3.7f * diameter)) + (2.51f/(ReynoldsNumber*sqrtf(ffact[1]))) );
		
		// if the slope is going to be 0 or infinite, break the loop and return a failure condition.
		if(ffact[1] == ffact[0] || y[1] == y[0])break;
		
		// calculate the slope
		slope = (y[1]-y[0])/(ffact[1]-ffact[0]);
		
		ffact[2] = ffact[0] - y[0]/slope;
		
		
		//store the second guess in the first guess's spot
		ffact[0] = ffact[1];
		// store new ffact value in the second's guess spot
		ffact[1] = ffact[2];
		//increment the itteration counter.
		itterations++;
		
		//calculate relative error
		relativeError = (y[1]-y[0])/y[1];
		// take absolute value of relative error calculation
		if(relativeError < 0) relativeError *= -1.0f;
		
	}
	// the program has failed if any of the following are true:
	// 		- the relative error is still larger than the tolerance
	//		- the loop went through too many itterations
	//		- the slope of the line if infinite or zero
	if(relativeError > tolerance || itterations >= maxItterations || y[0] == y[1] || ffact[2] < 0){
		// set succes flag to FAILURE
		returnValues[0] = 0.0f;
		returnValues[1] = SECANT_COLEBROOK_FAILURE;
		return returnValues;
	}
	// you must have succeeded if nothing went wrong.
	else{
		// set success flag to SUCCESS
		returnValues[0] = ffact[2];
		returnValues[1] = SECANT_COLEBROOK_SUCCESS;
		return returnValues;
	}
	
	
	
	
	
	
	
	// the function should never get to this point.
	// but if it does, return a failure flag.
	returnValues[0] = 0.0f;
	returnValues[1] = SECANT_COLEBROOK_FAILURE;
	return returnValues;
}




