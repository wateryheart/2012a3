/*******************************************************
 * COMP2012 - 2012/13 Fall
 * Programming Assignment 3
 * File: Polynomial.h
 *
 * MAR Chun Sum (20057384)
 *******************************************************/
#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <list>

using namespace std;

class Term
{
  public:
    Term() { coef = 0; expon = 0; };
    Term(double c, int e) { coef = c; expon = e; };

    double getCoef() const { return (this->coef); };
    void setCoef(double c) { this->coef = c; };
    int getExpon() const { return (this->expon); };
    void setExpon(int e) { this->expon = e; };

  private:
    double coef;
    int expon;

  friend class Polynomial;
};


/* 
   Polynomial class:
   providing operations on polynomial(s)
   e.g. ==, +, -, *, () 
 */ 
class Polynomial
{
   public:
     // Default constructor 
     Polynomial();

     // Constructor to read and create a polynomial from the file of fileName
     Polynomial(const string poly_str);

     // Constructor for constant polynomial
     Polynomial(double c);

     // Constructor for constant node.
     Polynomial(Term t);

     // Copy constructor
     Polynomial(const Polynomial& a);

     // Destructor
     virtual ~Polynomial();

     virtual void str2poly(const string poly_str);

     virtual string toString() const;
 
     // print the polynomial a in decreasing order of exponent
     virtual void print(ostream&) const;

     // check if the polynomial is zero or not
     bool isZero() const;
     
     // returns the number of node in the polynomial
     int length() const;

     // get the leading term
     Term leadingTerm() const;

     // get the maximum degree
     int maxDegree() const;

     // Assignment operator
     Polynomial& operator=(const Polynomial& a); 

     // Evaluate the polynomial a at value of x 
     double operator()(double x) const;

     // sorting the polynomial in descending order of degree(expon)
     void sort();

   protected:
     std::list<Term> polyList;

   // Addition operator
   friend Polynomial operator+(const Polynomial& b, const Polynomial& a);

   // Subtraction operator
   friend Polynomial operator-(const Polynomial& b, const Polynomial& a);

   // Multiplication operator
   friend Polynomial operator*(const Polynomial& b, const Polynomial& a);

   // Equal to operator
   friend bool operator==(const Polynomial& b, const Polynomial& a);
};

// Addition operator
Polynomial operator+(const Polynomial& b, const Polynomial& a);

// Subtraction operator
Polynomial operator-(const Polynomial& b, const Polynomial& a);
   
// Multiplication operator
Polynomial operator*(const Polynomial& b, const Polynomial& a);

// Equal to operator
bool operator==(const Polynomial& b, const Polynomial& a);

// Output operator
ostream & operator<<(ostream& os, Polynomial& a);

// Input operator
istream & operator>>(istream& is, Polynomial& a);

#endif
