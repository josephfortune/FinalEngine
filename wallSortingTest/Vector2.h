// Written by Joseph Fortune 11/16/2014
// 9/25/2015 - Replaced the dot product function with an overloaded operator

#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2

{
	public:
	//Constructor/Destructor	
	Vector2( void );
	Vector2( double x, double y );
	
	// Actions/Operations
	Vector2 normalize( void );
	double dot( Vector2 v );
	Vector2 projectOn( Vector2 v );
	double angle( void );
	Vector2 normal( void );

	// Getters
	double length( void );

	// Static Functions
	static Vector2 rayIntersect( Vector2 location, Vector2 direction, Vector2 targetLoc, Vector2 targetDir );

	// Operators
	Vector2 operator+( Vector2 v );		// Addition
	Vector2 operator-( Vector2 v );		// Subtraction
	Vector2 operator*( double c );		// Scalar multiplication
	double operator*( Vector2 v );		// Dot product
	Vector2 operator/( double c );		// Scalar division	

	double x, y;
	double len; // Vector length
	bool initialized; // has length been set? Stops us from repeating sqroot on same vector
};

// *************************************** Debug ******************************************
#include <iostream>
using namespace std;

void printVec( Vector2 v );

#endif


