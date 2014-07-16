/*******************************************************
 * COMP2012 - 2012/13 Fall
 * Programming Assignment 3
 * File: IntegerPolynomial.cpp
 *
 * MAR Chun Sum (20057384)
 *******************************************************/

#include <iostream>
#include "Polynomial.h"
#include "IntegerPolynomial.h"
using namespace std;


// The default constructor.
IntegerPolynomial::IntegerPolynomial()
{

};

// Constructor for constant polynomial, i.e. converting a integer value to a constant term.
IntegerPolynomial::IntegerPolynomial(int c)
{
	polyList.push_back(Term(c,0));
};

// Constructor for constant node.
IntegerPolynomial::IntegerPolynomial(Term t)
{
	polyList.push_back(t);
};

// Read and create a integer polynomial from a string. Each string will contain only one polynomial.
// (Truncate the coefficient of the input if necessary.)
IntegerPolynomial::IntegerPolynomial(const string polyStr)
{
	str2poly(polyStr);
};

// The convert constructor, which create a polynomial with coefficients in the intArray,
// where intArray[i] contains the integer coefficient of xi e.g. intArray = {3, 2, 0, 4}
// The polynomial list will have the following terms only: 3x^0, 2x^1, 4x^2
IntegerPolynomial::IntegerPolynomial(int* intArray, int size)
{
	for (int i=0;i<size;i++)
	{
		if (intArray[i] != 0)
			polyList.push_back(Term(intArray[i],i));
	}
};

// Copy constructor.
IntegerPolynomial::IntegerPolynomial(const Polynomial& a)
{
	polyList.clear();
	int i = 0, c[a.length()], counter = 0;
	Term node;
	while(!(*this == a))
	{
		node = (a-*this).leadingTerm();
		c[counter] = (a-*this).leadingTerm().getCoef();
		polyList.push_back(node);
		counter++;
	}
	list<Term>::iterator p = polyList.begin();
	while(p != polyList.end() && i<= counter )
	{
		p->setCoef(c[i]);
		p++;
		i++;
	}

};

// The Destructor.
IntegerPolynomial::~IntegerPolynomial()
{
	polyList.clear();
};

// Evaluate a polynomial given a particular integer value of x, returning a integer number.
// For example, the value of the polynomial 9x6 + 2x3 + x + 2 at x=3 is 9(3)6 + 2(3)3 + 3 + 2 = 6620
int IntegerPolynomial::operator()(int x) const
{
	list<Term>::const_iterator p = polyList.begin();
	int sum = 0;
	while(p != polyList.end())
	{
		sum = sum + (p->getCoef() * pow(x , p->getExpon()));
		p++;
	}
	return sum;
};

// Find the quotient (polynomial) of dividing an integer polynomial by another integer polynomial a (divisor).
Polynomial IntegerPolynomial::operator/(const Polynomial& a)
{
	Polynomial q(0),r(0),p(*this),g(a);
	if(a.isZero())
	{
		cout << "Error:Division by 0!";
	}
	else
	{
		if (g.maxDegree() == p.maxDegree() && p.maxDegree() == 0)
			return (int)(p.leadingTerm().getCoef() / g.leadingTerm().getCoef());
		while (! p.isZero())
		{
			if(g.maxDegree() <= p.maxDegree())
			{
				/*
				u.polyList.clear();
				u.polyList.push_back(Term(p.leadingTerm().getCoef() / g.leadingTerm().getCoef(),
						p.leadingTerm().getExpon() - g.leadingTerm().getExpon()));
				*/
				Term node;
				node.setCoef(p.leadingTerm().getCoef() / g.leadingTerm().getCoef());
				node.setExpon(p.leadingTerm().getExpon() - g.leadingTerm().getExpon());
				Polynomial u(node);
				q = q + u;
				p = p - (u * g);
				u.~Polynomial();
			}
			else
			{
				Term node;
				node.setCoef(p.leadingTerm().getCoef());
				node.setExpon(p.leadingTerm().getExpon());
				Polynomial u(node);
				r = r + u;
				p = p - u;
				u.~Polynomial();
			}
		}
	}
	q.sort();
	return q;
};

// Find the remainder (polynomial) of dividing an integer polynomial by another integer polynomial a (divisor).
Polynomial IntegerPolynomial::operator%(const Polynomial& a)
{
	Polynomial q(0),r(0),p(*this),g(a),u(0);
	if(a.isZero())
	{
		cout << "Error:Division by 0!";
	}
	else
	{
		if (g.maxDegree() == p.maxDegree() && p.maxDegree() == 0)
			return  ((int)p.leadingTerm().getCoef()) % ((int)g.leadingTerm().getCoef());
		while (! p.isZero())
		{
			if(g.maxDegree() <= p.maxDegree())
			{
				Term node;
				node.setCoef(p.leadingTerm().getCoef() / g.leadingTerm().getCoef());
				node.setExpon(p.leadingTerm().getExpon() - g.leadingTerm().getExpon());
				Polynomial u(node);
				q = q + u;
				p = p - (u * g);
				u.~Polynomial();
			}
			else
			{
				Term node;
				node.setCoef(p.leadingTerm().getCoef());
				node.setExpon(p.leadingTerm().getExpon());
				Polynomial u(node);
				r = r + u;
				p = p - u;
				u.~Polynomial();
			}
		}
	}
	r.sort();
	return r;
};

// Overload the virtual function. Convert a string to overwrite the current Integer polynomial.
// (Truncate the coefficient of the input if necessary.)
void IntegerPolynomial::str2poly(const string poly_str)
{
	polyList.clear();
	int length = poly_str.length();
	int  c = 0, e = 0, ns = 0, s = 0, position = 1;
	bool x;
	//c:coefficient, e:exponent,
	//ns:next sign position, s:sign position,position: node iterator
	//x: have x or not
	for (int i = 0; i < length; i++)
	{
		if ((poly_str[ns] == '+' || poly_str[ns] == '-')&& ns != 0)
		{
			x = false;
			for (int l = s; l < ns; l++)
			{
				if (poly_str[l] == 'x') //with coefficient
				{
					x = true;
					if(position == 1) //first node
					{
						//coefficient
						if (poly_str[0]== '-')
						{
							if (poly_str[1] == 'x') //-x
								c = -1;
							else //-cx
								c = 0 - atoi(&poly_str[1]);
						}
						else
						{
							if (poly_str[0] == 'x') //x
								c = 1;
							else //cx
								c = atoi(&poly_str[0]);
						}

						//exponent
						if (poly_str[ns-1] == 'x')
							e = 1;
						else
							e = atoi(&poly_str[l+2]);
					}
					else //non-first node
					{
						//coefficient
						if (poly_str[s] == '+')
						{
							if (poly_str[s+1] == 'x') //+x
								c = 1;
							else //+cx
								c = atoi(&poly_str[s+1]);
						}
						else if (poly_str[s]== '-')
						{
							if (poly_str[s+1] == 'x') //-x
								c = -1;
							else //-cx
								c = 0 - atoi(&poly_str[s+1]);
						}

						//exponent
						if (poly_str[ns-1] == 'x')
							e = 1;
						else
							e = atoi(&poly_str[l+2]);
					}
				}
			}
			if (x == false) //constant only
			{
				e = 0;

				//coefficient
				if (position == 1)
				{
					if (poly_str[0] == '-')
						c = 0 - atoi(&poly_str[1]);
					else
						c = atoi(&poly_str[0]);
				}
				else
				{
					if (poly_str[s] == '+')
						c = atoi(&poly_str[s+1]);
					else
						c = 0 - atoi(&poly_str[s+1]);
				}
			}
			polyList.push_back(Term(c,e));
			position++;
			s = ns;
			c = 0;
			e = 0;
		}
		ns++;
	}

	//last term
	x = false;
	for (int l = s; l < ns; l++)
	{
		if (poly_str[l] == 'x')  //with coefficient
		{
			x = true;
			if(position == 1) //first and only node
			{
				//coefficient
				if (poly_str[0]== '-')
				{
					if (poly_str[1] == 'x') //-x
						c = -1;
					else //-cx
						c = 0 - atoi(&poly_str[1]);
				}
				else
				{
					if (poly_str[0] == 'x') //x
						c = 1;
					else //cx
						c = atoi(&poly_str[0]);
				}

				//exponent
				if (poly_str[ns-1] == 'x')
					e = 1;
				else
					e = atoi(&poly_str[l+2]);
			}
			else // non-first node
			{
				//coefficient
				if (poly_str[s] == '+')
				{
					if (poly_str[s+1] == 'x') //+x
						c = 1;
					else //+cx
						c = atoi(&poly_str[s+1]);
				}
				else if (poly_str[s]== '-')
				{
					if (poly_str[s+1] == 'x') //-x
						c = -1;
					else //-cx
						c = 0 - atoi(&poly_str[s+1]);
				}
				//exponent
				if (poly_str[ns-1] == 'x')
					e = 1;
				else if (poly_str[ns-1] == c)
					e = 0;
				else
					e = atoi(&poly_str[l+2]);
			}
		}
	}
	if (x == false) //constant only
	{
		e = 0;

		//coefficient
		if (position == 1)
		{
			if (poly_str[0] == '-')
				c = 0 - atoi(&poly_str[1]);
			else
				c = atoi(&poly_str[0]);
		}
		else
		{
			if (poly_str[s] == '+')
				c = atoi(&poly_str[s+1]);
			else
				c = 0 - atoi(&poly_str[s+1]);
		}
	}
	polyList.push_back(Term(c,e));
};

// Overload the virtual function. Convert the polynomial to a string.
string IntegerPolynomial::toString() const
{
	list<Term>::const_iterator p = polyList.begin();
	stringstream poly;
	int position = 1;
	if (polyList.size() == 0) //if polynomial is empty
		poly << "0";
	else
	{
		while(p!= polyList.end())
		{
			if (p->getExpon() == 0)
			{
				if (position == 1) //first element
					poly << p->getCoef();
				else //non-first element with sign
				{
					if (p->getCoef() >= 0) //positive number should have + sign
							poly << "+" << p->getCoef();
					else
						poly << p->getCoef();
				}
			}
			else if (p->getExpon() == 1)
			{
				if (position == 1) //first element
				{
					if (p->getCoef() == 1)
						poly << "x";
					else if(p->getCoef() == -1)
						poly << "-x";
					else
						poly << p->getCoef() << "x";
				}
				else //non-first element with sign
				{
					if (p->getCoef() == 1)
						poly << "+x";
					else if(p->getCoef() == -1)
						poly << "-x";
					else if (p->getCoef() > 0)
						poly << "+" << p->getCoef() << "x";
					else
						poly << p->getCoef() << "x";
				}
			}
			else
			{
				if (position == 1) //first element
				{
					if (p->getCoef() == 1)
						poly << "x^"<< p->getExpon();
					else if(p->getCoef() == -1)
						poly << "-x^" << p->getExpon();
					else
						poly << p->getCoef() << "x^" << p->getExpon();
				}
				else //non-first element with sign
				{
					if (p->getCoef() == 1)
						poly << "+x^" << p->getExpon();
					else if(p->getCoef() == -1)
						poly << "-x^" << p->getExpon();
					else if (p->getCoef() > 0)
						poly << "+" << p->getCoef() << "x^" << p->getExpon();
					else
						poly << p->getCoef() << "x^" << p->getExpon();
				}
			}
			position++;
			p++;
		}
	}
	return poly.str();
};

// Overload the virtual function. Output the polynomial to the output stream.
// The polynomial should all be on one line.
void IntegerPolynomial::print(ostream &os) const
{
	os << toString();
};
