/*******************************************************
 * COMP2012 - 2012/13 Fall
 * Programming Assignment 3
 * File: main.cpp
 *******************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include "Polynomial.h"
#include "IntegerPolynomial.h"

using namespace std;

template <typename T>
T readPoly(const char* filename)
{
  ifstream fin(filename,  ifstream::in);

  T temp;

  fin >> temp;
  fin.close();

  return (temp);
}

int main(void)
{
   Polynomial a = readPoly<Polynomial>("input1.txt");
   Polynomial b = readPoly<Polynomial>("input2.txt");
   Polynomial d;
   cout << "a=" << a << endl;
   cout << "a_str=" << a.toString() << endl;
   cout << "b=" << b << endl;
   b.sort();
   cout << "sorted b=" << b << endl;

   if (a==b) cout << "a equals to b." << endl;
   else cout << "a does not equal to b." << endl;

   IntegerPolynomial ia = readPoly<IntegerPolynomial>("input1.txt");
   IntegerPolynomial ib = readPoly<IntegerPolynomial>("input2.txt");

   int iarry[5] = {1, 3, 5, 9, 10};
   IntegerPolynomial id(iarry, 5);

   cout << "ia=" << ia <<endl;
   cout << "ib=" << ib <<endl;
   cout << "id=" << id <<endl;

   if (a==ia) cout << "a equals to ia." << endl;
   else cout << "a does not equal to ia." << endl;

   d=b;
   cout << "d=b=" << d << endl; 
   d=ib;
   cout << "d=ib=" << d << endl; 
   id=b;
   cout << "id=b=" << id << endl;
   d=a-b;

   cout << "------ Polynomial Operations -------\n";

   cout << "a-b=" << d << endl;
   d=a+b;
   cout << "a+b=" << d << endl;
   d=a*b;
   cout << "a*b=" << d << endl;

   cout << "------ Integer Polynomial Operations -------\n";
   id = ia+ib;
   cout << "id=ia+ib=" << id << endl;
   id = ia-ib;
   cout << "id=ia-ib=" << id << endl;
   id=ia*ib;
   cout << "ia*ib=" << id << endl;
   ib.str2poly("x");
   id=ia/ib;
   cout << "ia/x=" << id << endl;
   id=ia%ib;
   cout << "ia%x=" << id << endl;

   id=ia+10;
   cout << "ia+10=" << id << endl;
   d=ia/10;
   cout << "ia/10=" << d << endl;
   d=ia%10;
   cout << "ia%10=" << d << endl;

   return (0); 
}
