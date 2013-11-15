/* secant_colebrook.h
 * Ryan Jensen
 * 2013-11-15 (created)
 * 2013-11-15 (last modified)
 * 
 * This header file contains the secant_colebrook() function.
 * This function will solve the Colebrook equation for the friction factor f numerically.
*/

// this function numberically solves the Colebrook Equation for the friction factor f.
// the return value is a pointer to two floating point values.
// the first floating point number is the friction factor f
// the second floating point number is an error flag.
#define SECANT_COLEBROOK_SUCCESS 1.0f	// this is a flag that denotes success in finding a zero
#define SECANT_COLEBROOK_FAILURE 0.0f	// this is a flag that denotes a failure to find a zero
float * secant_colebrook(float RenoldsNumber, float diameter, float roughness){
	
	// this is where we store the frictionFactor
	float frictionFactor;
	// this is where we store the success value for the function.
	// by default, it is set to failure.
	float success = SECANT_COLEBROOK_FAILURE;
	
	// define an array of floating point values with two elements.
	// the first element will store the friction factor.
	// the second value will store the success value.
	static float returnValues[2];
	
	
	
	// return the friction factor and the sucess value.
	return returnValues;
}
