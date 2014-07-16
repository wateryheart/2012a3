/*******************************************************
 * COMP2012 - 2012/13 Fall
 * Programming Assignment 3
 * File: IntegerPolynomial.h
 *
 * MAR Chun Sum (20057384)
 *******************************************************/
#ifndef _INTEGERPOLYNOMIAL_H
#define _INTEGERPOLYNOMIAL_H

#include <iostream>
#include "Polynomial.h"

using namespace std;

class IntegerPolynomial : public Polynomial
{
	public:
		// The default constructor.
		IntegerPolynomial();

		// Constructor for constant polynomial, i.e. converting a integer value to a constant term.
		IntegerPolynomial(int c);

		// Constructor for constant node.
		IntegerPolynomial(Term t);

		// Read and create a integer polynomial from a string. Each string will contain only one polynomial.
		// (Truncate the coefficient of the input if necessary.)
		IntegerPolynomial(const string polyStr);

		// The convert constructor, which create a polynomial with coefficients in the intArray,
		// where intArray[i] contains the integer coefficient of xi e.g. intArray = {3, 2, 0, 4}
		// The polynomial list will have the following terms only: 3x^0, 2x^1, 4x^2
		IntegerPolynomial(int* intArray, int size);

		// Copy constructor.
		IntegerPolynomial(const Polynomial& a);

		// The Destructor
		virtual ~IntegerPolynomial();

		// Evaluate a polynomial given a particular integer value of x, returning a integer number.
		// For example, the value of the polynomial 9x6 + 2x3 + x + 2 at x=3 is 9(3)6 + 2(3)3 + 3 + 2 = 6620
		int operator()(int x) const;

		// Find the quotient (polynomial) of dividing an integer polynomial by another integer polynomial a (divisor).
		Polynomial operator/(const Polynomial& a);

		// Find the remainder (polynomial) of dividing an integer polynomial by another integer polynomial a (divisor).
		Polynomial operator%(const Polynomial& a);

		// Overload the virtual function. Convert a string to overwrite the current Integer polynomial.
		// (Truncate the coefficient of the input if necessary.)
		virtual void str2poly(const string poly_str);

		// Overload the virtual function. Convert the polynomial to a string.
		virtual string toString() const;

		// Overload the virtual function. Output the polynomial to the output stream.
		// The polynomial should all be on one line.
		virtual void print(ostream &os) const;

};

#endif /* _INTEGERPOLYNOMIAL_H */
