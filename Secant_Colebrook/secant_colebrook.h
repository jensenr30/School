/* secant_colebrook.h
 * Ryan Jensen
 * 2013-11-15 (created)
 * 2013-11-18 (last modified)
 * This header file contains the secant_colebrook() function.
 * This function will solve the Colebrook equation for the friction factor f
 * numerically.
*/

//used for the nice math functions like log10() and sqrtf()
#include <math.h>

// this is a flag that denotes success in finding a zero
#define SECANT_COLEBROOK_SUCCESS 1.0f
// this is a flag that denotes a failure to find a zero
#define SECANT_COLEBROOK_FAILURE 0.0f

/// this function solves the Colebrook equation for the friction factor, f.
/// the return value is a pointer to two floating point values.
/// the first floating point number is the friction factor f
/// the second floating point number is an error flag.
float * secant_colebrook(float Re, float D, float epsilon){
	
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
	
	// this is the f_tol for relative error in our value.
	float f_tol = 0.01;
	//this stores the relative error at the current iteration
	float relErr;
	// this keeps track of how many times the function has gone through the loop.
	int iter;
	//this is the maximum number of times that you can go through the while() loop.
	int maxItt = 200;
	
	// define an array of floating point values with two elements.
	// the first element will store the friction factor.
	// the second value will store the success value.
	static float returnValues[2];
	
	///-------------------------------------------------------------------------
	///		EVALUATE THE ROOT OF THE COLEBROOK EQUATION
	///-------------------------------------------------------------------------
	
	//initial guesses for the friction factor
	ffact[0] = 0.1;
	ffact[1] = 0.01;
	//initial value to make sure we can enter the loop
	ffact[2] = 10;
	// start iter at 0
	iter = 0;
	// make sure the relative error is greater than f_tol to enter the loop
	relErr = 100*f_tol;
	
	while(relErr > f_tol && iter < maxItt && ffact[2] >= 0.0){
		
		// evaluate the Colebrook equation at point 0
		y[0]= (1/sqrtf(ffact[0]));
		y[0]+= 2*log10((epsilon/(3.7f * D))+(2.51f/(Re*sqrtf(ffact[0]))));
		// evaluate the Colebrook equation at point 1
		y[1]= (1/sqrtf(ffact[1]));
		y[1]+= 2*log10((epsilon/(3.7f * D))+(2.51f/(Re*sqrtf(ffact[1]))));
		
		// if the slope is 0 or infinite, break and return a failure flag.
		if(ffact[1] == ffact[0] || y[1] == y[0])break;
		
		// calculate the slope
		slope = (y[1]-y[0])/(ffact[1]-ffact[0]);
		
		// calculate where the next x value will be located
		ffact[2] = ffact[0] - y[0]/slope;
		
		
		//store the second guess in the first guess's spot
		ffact[0] = ffact[1];
		// store new ffact value in the second's guess spot
		ffact[1] = ffact[2];
		//increment the iteration counter.
		iter++;
		
		//calculate relative error
		relErr = (ffact[1]-ffact[0])/ffact[1];
		// take absolute value of relative error calculation
		if(relErr < 0) relErr *= -1.0f;
		
	}
	
	///-------------------------------------------------------------------------
	///		DETERMINE RETURN VALUES AND EXIT FUNCTION
	///-------------------------------------------------------------------------
	
	// the program has failed if any of the following are true:
	// 		- the relative error is still larger than the f_tol
	//		- the loop went through too many iter
	//		- the slope of the line if infinite or zero
	//		- the ffact value that will be returned is negative
	if(relErr>f_tol || iter>=maxItt || y[0]==y[1] || ffact[2]<0){
		// return the value of the invalid friction factor (whatever it may be)
		returnValues[0] = ffact[2];
		// set success flag to FAILURE
		returnValues[1] = SECANT_COLEBROOK_FAILURE;
		return returnValues;
	}
	// you must have succeeded if nothing went wrong.
	else{
		// return the value of the correctly calculated friction factor
		returnValues[0] = ffact[2];
		// set success flag to SUCCESS
		returnValues[1] = SECANT_COLEBROOK_SUCCESS;
		return returnValues;
	}
	// the function should never get to this point.
	// but if it does, return a failure flag.
	returnValues[0] = 0.0f;
	returnValues[1] = SECANT_COLEBROOK_FAILURE;
	return returnValues;
}
