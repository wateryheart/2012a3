/*******************************************************
 * COMP2012 - 2012/13 Fall
 * Programming Assignment 3
 * File: Polynomial.h
 *
 * MAR Chun Sum (20057384)
 *******************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <string>
#include <bitset>
#include <list>
#include "Polynomial.h"
using namespace std;

// Default constructor
Polynomial::Polynomial()
{
};

// Constructor to read and create a polynomial from the file of fileName
Polynomial::Polynomial(const string poly_str)
{
	str2poly(poly_str);
};

// Constructor for constant polynomial
Polynomial::Polynomial(double c)
{
	polyList.push_back(Term(c,0));
};

// Constructor for constant node.
Polynomial::Polynomial(Term t)
{
	polyList.push_back(t);
};

// Copy constructor
Polynomial::Polynomial(const Polynomial& a)
{
    polyList.clear();
	list<Term>::const_iterator p = a.polyList.begin();
	while(p!= a.polyList.end())
	{
		polyList.push_back(Term(p->getCoef(),p->getExpon()));
		p++;
	}
};

// Destructor
Polynomial::~Polynomial()
{
	polyList.clear();
};

void Polynomial::str2poly(const string poly_str)
{
	polyList.clear();
	int length = poly_str.length();
	double c = 0;
	int e = 0, ns = 0, s = 0, position = 1;
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
								c = 0 - atof(&poly_str[1]);
						}
						else
						{
							if (poly_str[0] == 'x') //x
								c = 1;
							else //cx
								c = atof(&poly_str[0]);
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
								c = atof(&poly_str[s+1]);
						}
						else if (poly_str[s]== '-')
						{
							if (poly_str[s+1] == 'x') //-x
								c = -1;
							else //-cx
								c = 0 - atof(&poly_str[s+1]);
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
						c = 0 - atof(&poly_str[1]);
					else
						c = atof(&poly_str[0]);
				}
				else
				{
					if (poly_str[s] == '+')
						c = atof(&poly_str[s+1]);
					else
						c = 0 - atof(&poly_str[s+1]);
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
						c = 0 - atof(&poly_str[1]);
				}
				else
				{
					if (poly_str[0] == 'x') //x
						c = 1;
					else //cx
						c = atof(&poly_str[0]);
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
						c = atof(&poly_str[s+1]);
				}
				else if (poly_str[s]== '-')
				{
					if (poly_str[s+1] == 'x') //-x
						c = -1;
					else //-cx
						c = 0 - atof(&poly_str[s+1]);
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
				c = 0 - atof(&poly_str[1]);
			else
				c = atof(&poly_str[0]);
		}
		else
		{
			if (poly_str[s] == '+')
				c = atof(&poly_str[s+1]);
			else
				c = 0 - atof(&poly_str[s+1]);
		}
	}
	polyList.push_back(Term(c,e));
};

string Polynomial::toString() const
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
			if (p->expon == 0)
			{
				if (position == 1) //first element
					poly << p->coef;
				else //non-first element with sign
				{
					if (p->coef >= 0) //positive number should have + sign
							poly << "+" << p->coef;
					else
						poly << p->coef;
				}
			}
			else if (p->expon == 1)
			{
				if (position == 1) //first element
				{
					if (p->coef == 1)
						poly << "x";
					else if(p->coef == -1)
						poly << "-x";
					else
						poly << p->coef << "x";
				}
				else //non-first element with sign
				{
					if (p->coef == 1)
						poly << "+x";
					else if(p->coef == -1)
						poly << "-x";
					else if (p->coef > 0)
						poly << "+" << p->coef << "x";
					else
						poly << p->coef << "x";
				}
			}
			else
			{
				if (position == 1) //first element
				{
					if (p->coef == 1)
						poly << "x^"<< p->expon;
					else if(p->coef == -1)
						poly << "-x^" << p->expon;
					else
						poly << p->coef << "x^" << p->expon;
				}
				else //non-first element with sign
				{
					if (p->coef == 1)
						poly << "+x^" << p->expon;
					else if(p->coef == -1)
						poly << "-x^" << p->expon;
					else if (p->coef > 0)
						poly << "+" << p->coef << "x^" << p->expon;
					else
						poly << p->coef << "x^" << p->expon;
				}
			}
			position++;
			p++;
		}
	}
	return poly.str();
};

// print the polynomial a in decreasing order of exponent
void Polynomial::print(ostream& os) const
{
	list<Term>::const_iterator p = polyList.begin();
	int position = 1;
	if (polyList.size() == 0) //if polynomial is empty
		os << "0";
	else
	{
		while(p!= polyList.end())
		{
			if (p->expon == 0)
			{
				if (position == 1) //first element
					os << setprecision(2)<< fixed << p->coef;
				else //non-first element with sign
				{
					if (p->coef >= 0) //positive number should have + sign
						os << "+" << setprecision(2)<< fixed << p->coef;
					else
						os << setprecision(2)<< fixed << p->coef;
				}
			}
			else if (p->expon == 1)
			{
				if (position == 1) //first element
				{
					if (p->coef == 1)
						os << "x";
					else if(p->coef == -1)
						os << "-x";
					else
						os << setprecision(2)<< fixed << p->coef << "x";
				}
				else //non-first element with sign
				{
					if (p->coef == 1)
						os << "+x";
					else if(p->coef == -1)
						os << "-x";
					else if (p->coef > 0)
						os << "+" << setprecision(2)<< fixed << p->coef << "x";
					else
						os << setprecision(2)<< fixed << p->coef << "x";
				}
			}
			else
			{
				if (position == 1) //first element
				{
					if (p->coef == 1)
						os << "x^" << p->expon;
					else if(p->coef == -1)
						os << "-x^"<< p->expon;
					else
						os << setprecision(2)<< fixed << p->coef << "x^" << p->expon;

				}
				else //non-first element with sign
				{
					if (p->coef == 1)
						os << "+x^" << p->expon;
					else if(p->coef == -1)
						os << "-x^"<< p->expon;
					else if (p->coef > 0)
						os << "+" << setprecision(2)<< fixed << p->coef << "x^" << p->expon;
					else
						os << setprecision(2)<< fixed << p->coef << "x^" << p->expon;
				}
			}
			position++;
			p++;
		}
	}
};

// check if the polynomial is zero or not
bool Polynomial::isZero() const
{
	if (polyList.size() == 0)
		return true;
	list<Term>::const_iterator p = polyList.begin();
	while (p !=polyList.end())
	{
		if (p->getCoef() != 0)
			return false;
		if (p->getExpon() != 0)
			return false;
		p++;
	}
	return true;
};

// returns the number of node in the polynomial
int Polynomial::length() const
{
	list<Term>::const_iterator p = polyList.begin();
	int length = 0;
	while (p !=polyList.end())
	{
		length++;
		p++;
	}
};

// get the leading term
Term Polynomial::leadingTerm() const
{
	void sort();
	list<Term>::const_iterator p = polyList.begin();
	Term lead;
	lead.setCoef(p->getCoef());
	lead.setExpon(p->getExpon());
	return lead;
};

// get the maximum degree
int Polynomial::maxDegree() const
{
	void sort();
	list<Term>::const_iterator p = polyList.begin();
	return p->getExpon();
};

// Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& a)
{
	polyList.clear();
	list<Term>::const_iterator p = a.polyList.begin();
	while(p!= a.polyList.end())
	{
		polyList.push_back(Term(p->getCoef(),p->getExpon()));
		p++;
	}
	return *this;
};

// Evaluate the polynomial a at value of x
double Polynomial::operator()(double x) const
{
	list<Term>::const_iterator p = polyList.begin();
	double sum = 0;
	while(p != polyList.end())
	{
		sum = sum + (p->getCoef() * (int)pow(x , p->getExpon()));
		p++;
	}
	return sum;
};

// sorting the polynomial in descending order of degree(expon)
void Polynomial::sort()
{

	//sort in decreasing order
	list<Term>::iterator m = polyList.begin();
	list<Term>::iterator n;
	double tc;
	int te;
	while (m != polyList.end())
	{
		n=m;
		n++;
		while(n!= polyList.end())
		{
			if (m->getExpon() < n->getExpon())
			{
				tc = m->getCoef();
				te = m->getExpon();
				m->setCoef(n->getCoef());
				m->setExpon(n->getExpon());
				n->setCoef(tc);
				n->setExpon(te);
			}
			n++;
		}
		m++;
	}

	//combine coefficient of same exponent
	list<Term>::iterator ptr;
	Polynomial sol;
	double coef;
	int exp;
	ptr = polyList.begin();
	exp = ptr->getExpon();
	for(int p = exp; p >= 0; p--)
	{
		ptr = polyList.begin();
		coef = 0;
		while(ptr != polyList.end())
		{
			if(ptr->getExpon() == p)
				coef = coef + ptr->getCoef();
			ptr ++;
		}
		if (coef != 0) //only record coefficient of exponent not equal to 0
			sol.polyList.push_back(Term(coef,p));
	}

	list<Term>::iterator ps = sol.polyList.begin();
	polyList.clear();
	while(ps != sol.polyList.end())
	{
		polyList.push_back(Term(ps->getCoef(),ps->getExpon()));
		ps++;
	}
};

// Addition operator
Polynomial operator+(const Polynomial& b, const Polynomial& a)
{
	Polynomial c(b);
	list<Term>::const_iterator pa = a.polyList.begin();
	while (pa != a.polyList.end())
	{
		c.polyList.push_back(Term(pa->getCoef(),pa->getExpon()));
		pa++;
	}
	c.sort();
	return c;
};

// Subtraction operator
Polynomial operator-(const Polynomial& b, const Polynomial& a)
{
	Polynomial c(b);
	list<Term>::const_iterator pa = a.polyList.begin();
	while (pa != a.polyList.end())
	{
		c.polyList.push_back(Term(-pa->getCoef(),pa->getExpon()));
		pa++;
	}
	c.sort();
	return c;
};

// Multiplication operator
Polynomial operator*(const Polynomial& b, const Polynomial& a)
{
	list<Term>::const_iterator pa = a.polyList.begin();
	list<Term>::const_iterator pb = b.polyList.begin();
	Polynomial mul;
	//multiply two polynomial
	if (a.isZero() || b.isZero())
	{
		mul.polyList.push_back(Term(0,0));
	}
	else
	{
		while(pa!= a.polyList.end())
		{
			while(pb!= b.polyList.end())
			{
				mul.polyList.push_back(Term(pa->getCoef() * pb->getCoef(),pa->getExpon() + pb->getExpon()));
				pb++;
			}
			pb = b.polyList.begin();
			pa++;
		}
	}
    mul.sort();
	return mul;
};

// Equal to operator
bool operator==(const Polynomial& b, const Polynomial& a)
{
	list<Term>::const_iterator pa = a.polyList.begin();
	list<Term>::const_iterator pb = b.polyList.begin();
	if (a.polyList.size() != b.polyList.size())
		return false;
	else
	{
		while (pa != a.polyList.end())
		{
			if(pa->getCoef() != pb->getCoef())
				return false;
			if(pa->getExpon() != pb->getExpon())
				return false;
			pa++;
			pb++;
		}
	}
	return true;
};

// Output operator
ostream & operator<<(ostream& os, Polynomial& a)
{
	a.print(os);
	return os;
}

// Input operator
istream & operator>>(istream& is, Polynomial& a)
{
	string str;
	is>>str;
	a.str2poly(str);
	return is;
};
