#ifndef __ITEMTYPE_H
#define __ITEMTYPE_H
#include <iostream>
#include <vector>
using namespace std;
class ItemType
{
private:
    //parameters
    int n;
    vector<int> x;
    vector<int> y;
    vector<int> res;
    int line;

public:
    //locals
    vector<int> a;
    vector<int> b;
    vector<int> c;
    vector<int> d;
    vector<int> sec1;
    vector<int> sec2;
    vector<int> sec3;

    ItemType(vector<int> a, vector<int> b, vector<int> c, vector<int> d,
	   vector<int> sec1, vector<int>sec2, vector<int>sec3, int n, vector<int> x, vector<int> y, vector<int> res);
    ItemType(vector<int> v1, vector<int> v2, int n, vector<int> res);
    ItemType(vector<int> x, vector<int> y, int n, vector<int> res, int line);
    ~ItemType();
    
    //GETTERS FOR PRIVATE MEMBERS
    vector<int>& getFirstNumber();
    vector<int>& getSecondNumber();
    int getN();
    vector<int> getRes();
    int getLine();

    //SETTERS
    void setFirstNumber(vector<int>& v1);
    void setSecondNumber(vector<int>& v2);
    void setRes(vector<int> res);
    void setNumber(int n);
    void setLine(int line);
    
    //OTHER
    void clearVector(vector<int>& res);
};
#endif // !__ITEMTYPE_H
