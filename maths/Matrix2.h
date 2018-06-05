// Written by Joseph Fortune 11/19/2016

// NOTE this is not a standard 2D matrix, but a 3D representation of a 2D matrix for the
// purpose of non-affine transformations

#ifndef MATRIX2_H
#define MATRIX2_H

#include "Vector2.h"

class Matrix2
{
	public:	
	// Constructor/Destructor
	Matrix2( double n11, double n12, double n13, 
			 double n21, double n22, double n23, 
			 double n31, double n32, double n33 );

	Matrix2(void);

	// Matrix builders
	static Matrix2 getTransMatrix( double dx, double dy );
	static Matrix2 getRotateMatrix( double angle );

	// Operators
	Matrix2 operator+( Matrix2 n );		// Addition
	Matrix2 operator-( Matrix2 n );		// Subtraction
	Matrix2 operator*( Matrix2 n );		// Matrix Multiplication
	Vector2 operator*( Vector2 v );		// Vector Multiplication
	Matrix2 operator*( double k );		// Scalar Multiplication
	Matrix2 operator/( double k );		// Scalar Division

	double m11, m12, m13, m21, m22, m23, m31, m32, m33;
};

#endif


