#include "ItemType.h"

//-------------------------------------------------------------------------------------------//
//CONSTRUCTOR
ItemType::ItemType(vector<int> a, vector<int> b, vector<int> c, vector<int> d, vector<int> sec1,
    vector<int>sec2, vector<int>sec3, int n, vector<int> x, vector<int> y, vector<int> res)
    : a(a), b(b), c(c), d(d), sec1(sec1), sec2(sec2), sec3(sec3), n(n), x(x), y(y), res(res) {}

//CONSTRUCTOR
ItemType::ItemType(vector<int> x1, vector<int> y1, int n1, vector<int> res, int line)
    : x(x1), y(y1), n(n1), res(res), line(line)
{
    if (n != 1)
    {
	   if (n1 % 2 != 0)
	   {
		  x.insert(x.begin(), 0);
		  y.insert(y.begin(), 0);
		  this->n = (n1 + 1);
	   }
	   a.insert(a.end(), x.begin(), x.begin() + n / 2);
	   b.insert(b.end(), x.begin() + n / 2, x.end());
	   c.insert(c.end(), y.begin(), y.begin() + n / 2);
	   d.insert(d.end(), y.begin() + n / 2, y.end());
    }
}

//DESTRUCTOR
ItemType::~ItemType() {}

//-------------------------------------------------------------------------------------------//

//GETTERS
vector<int>& ItemType::getFirstNumber()		   { return x; }
vector<int>& ItemType::getSecondNumber()	   { return y; }
vector<int> ItemType::getRes()			   { return res; }
int ItemType::getN()					   { return n; }
int ItemType::getLine()					   { return line; }

//-------------------------------------------------------------------------------------------//

//SETTERS 
void ItemType::setFirstNumber(vector<int>& v1)  { this->x = v1; }
void ItemType::setSecondNumber(vector<int>& v2) { this->y = v2; }
void ItemType::setRes(vector<int> res)		   { this->res = res; }
void ItemType::setNumber(int n)			   { this->n = n; }
void ItemType::setLine(int line)			   { this->line = (line); }

//-------------------------------------------------------------------------------------------//

//OTHER
void ItemType::clearVector(vector<int>& res)	   { res.clear(); }