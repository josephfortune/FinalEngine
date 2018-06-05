// Written by Joseph Fortune 11/19/2016

// NOTE this is not a standard 2D matrix, but a 3D representation of a 2D matrix for the
// purpose of non-affine transformations

#include "Matrix2.h"
#include <cmath>

//==================| Constructor |==================

Matrix2::Matrix2( double n11, double n12, double n13, 
				  double n21, double n22, double n23, 
				  double n31, double n32, double n33 )
{
	m11 = n11; m12 = n12; m13 = n13; 
	m21 = n21; m22 = n22; m23 = n23; 
	m31 = n31; m32 = n32; m33 = n33;
}

Matrix2::Matrix2( void ) { };


//==================| Matrix Builders |==================

Matrix2 Matrix2::getTransMatrix( double dx, double dy )
{
	return Matrix2( 1, 0, dx,
					0, 1, dy,
					0, 0, 1 );
}

Matrix2 Matrix2::getRotateMatrix( double angle )
{
	// SLOW!!!! If you can afford the memory footprint, use trig tables instead
	return Matrix2( cos(angle), -sin(angle), 0,
					sin(angle), cos(angle), 0,
					0, 0, 1 ); 
}


//==================| Overloaded Operators |==================

// Matrix addition
Matrix2 Matrix2::operator+( Matrix2 n ) { return Matrix2( m11 + n.m11, m12 + n.m12, m13 + n.m13,
														  m21 + n.m21, m22 + n.m22, m23 + n.m23,
														  m31 + n.m31, m32 + n.m32, m33 + n.m33 ); }
// Matrix subtraction
Matrix2 Matrix2::operator-( Matrix2 n ) { return Matrix2( m11 - n.m11, m12 - n.m12, m13 - n.m13,
														  m21 - n.m21, m22 - n.m22, m23 - n.m23,
														  m31 - n.m31, m32 - n.m32, m33 - n.m33 ); }
// Matrix multiplication
Matrix2 Matrix2::operator*( Matrix2 n ) { return Matrix2( m11*n.m11 + m12*n.m21 + m13*n.m31,
														  m11*n.m12 + m12*n.m22 + m13*n.m32,
														  m11*n.m13 + m12*n.m23 + m13*n.m33,

														  m21*n.m11 + m22*n.m21 + m23*n.m31,
														  m21*n.m12 + m22*n.m22 + m23*n.m32,
														  m21*n.m13 + m22*n.m23 + m23*n.m33,

														  m31*n.m11 + m32*n.m21 + m33*n.m31,
														  m31*n.m12 + m32*n.m22 + m33*n.m32,
														  m31*n.m13 + m32*n.m23 + m33*n.m33 ); }
// Scalar multiplication
Matrix2 Matrix2::operator*( double k ) { return Matrix2(  k*m11, k*m12, k*m13,
														  k*m21, k*m22, k*m23,
														  k*m31, k*m32, k*m33 ); }
// Vector multiplication 
Vector2 Matrix2::operator*( Vector2 v ) 
{ 
	Vector2 newVec	( v.x*m11 + v.y*m12 + m13,
					  v.x*m21 + v.y*m22 + m23 );

	/* becuase of the homogeneous thing, it might me necessary to test if the bottom row,
		multiplied (which does not occur above) is has a non zero answer so we have to divide by the homoGen corodinate? */
	return newVec;	 
}
// Scalar division
Matrix2 Matrix2::operator/( double k ) { return Matrix2(  m11/k, m12/k, m13/k,
														  m21/k, m22/k, m23/k,
														  m31/k, m32/k, m33/k ); }


