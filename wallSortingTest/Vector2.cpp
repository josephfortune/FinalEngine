// Written by Joseph Fortune 11/16/2014
// 9/25/2015 - Added dot product operator

#include "Vector2.h"
#include <cmath>


//==================| Constructor |==================

Vector2::Vector2( double x, double y ) 
{ 
	Vector2::x = x; Vector2::y = y; 
	initialized = false;
}

Vector2::Vector2( void )
{ 
	x = y = 0; 
	initialized = false;
}

//==================| Actions/Operations |==================

// Normalize
Vector2 Vector2::normalize( void )
{
	double length = sqrt( x*x + y*y );
	return Vector2( x/length, y/length );
}

// Dot product
double Vector2::dot( Vector2 v )
{
	return x * v.x + y * v.y;
}

// Project onto
Vector2 Vector2::projectOn( Vector2 v )
{
	Vector2 perpVec;
	double lengthSquared;

	lengthSquared = v.length() * v.length();
	perpVec = v * ( v.dot(*this) / lengthSquared );
	return perpVec;
}

// Angle
double Vector2::angle( void )
{
	return atan2(y, x);
}

// Normal (A series of vectors laid out in a clockwise direction will give inward facing normals)
Vector2 Vector2::normal( void )
{
	return Vector2(-x, y);
}

//==================| Getters |==================

double Vector2::length( void )
{
	if (!initialized)
	{
		len = sqrt( x*x + y*y );
		initialized = true;
	}


	return len;
}

//==================| Static Functions |==================

// rayIntersect() is the improved line intersection formula from the Graphics Gems book intended
// to replace the y=mx+b style math. It requires 2 rays, each defined by its origin and orientation
Vector2 Vector2::rayIntersect( Vector2 location, Vector2 direction, Vector2 targetLoc, Vector2 targetDir )
{
	Vector2 intersect, perp;
	
	perp = Vector2( -1 * targetDir.y, targetDir.x );
	intersect = direction * ( perp.dot( targetLoc - location ) / perp.dot(direction) )  + location;	

	return intersect;
}

//==================| Overloaded Operators |==================

// Addition
Vector2 Vector2::operator+( Vector2 v ) { return Vector2( x + v.x, y + v.y ); }

// Subtraction
Vector2 Vector2::operator-( Vector2 v ) { return Vector2( x - v.x, y - v.y ); }

// Scalar multiplication
Vector2 Vector2::operator*( double c) {	return Vector2( x * c, y * c ); }

// Dot product
double Vector2::operator*( Vector2 v ) { return x * v.x + y * v.y; }

// Scalar Divison
Vector2 Vector2::operator/( double c ) { return Vector2( x/c, y/c ); }

//==================| Debug |==================

void printVec( Vector2 v )
{
	cout << '[' << v.x << ' ' << v.y << ']' << '\n';
}


