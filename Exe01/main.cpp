/**********************************************************************************
 ********************* MTA DATA STRUCTURES COURSE PROJECT 1 ***********************
 *********** TRADITIONAL LONG-MULTIPLICATION AND KARATSUBA ALGORITHM. *************
 ********************************************************************************** /

/*  The program recieves non-negative n integer and 2 n-digits numbers x and y.
    The program multiplies x and y and calculates the result in 3 ways:
    (1) Long multiplication
    (2) Karatsub'a algorithm (Recursive)
    (3) Karatsub'a algorithm (Iterative)								            */

//-------------------------------------------------------------------------------------------//

#include <iostream>
#include <vector> 
#include <string>
#include "Stack.h"
using namespace std;

//--------------------------------------- CONST VALUES --------------------------------------//
const char* SEPARATOR =
"---------------------------------------------------------------------------------";

#define BASE 10 
enum SEC{SEC1_CALC=1, SEC2_CALC, SEC3_CALC, FINAL_RESULT_CALC};

//----------------------------------- FUNCTIONS DECLARATIONS --------------------------------//

void inputError();
void factorReader(vector<int>& theVector, const int& numOfDigits);
void printVector(const vector<int>& resVector, const char* msg);
void longMulAlgorithm(vector<int>& resVector, const vector<int>& x, const vector<int>& y, int n);
void karatsubaRecOut(const vector<int>& x,const vector<int>& y, int n, vector<int>& resVector);
void karatsubaRec(vector<int>& x, vector<int>& y, int n, vector<int>& resVector);
void karatsubaItrOut(const vector<int>& x, const vector<int>& y, int n, vector<int>& resVector);
void karatsubaItr(vector<int>& x, vector<int>& y, int n, vector<int>& resVector);
void shiftLeft(vector<int>& res, int shift);
void sumOfVectors(vector<int>& resultVector, vector<int>& toAdd);
void subVectors(vector<int>& resultVector, vector<int>& toSub);
void mergeVectors(vector<int>& dest, const vector<int>& v1, const vector<int>& v2);

//-------------------------------------------------------------------------------------------//

void inputError()
{
    cout << "wrong input.\n"
    exit(1);
}

//-------------------------------------------------------------------------------------------//

/*  Function reads an integer into a given vector.
    NOTE: the given numOfDigits is a positive integer.theVector would be in length
    of numOfDigits.(= exercise's assumption.)								   */
void factorReader(vector<int>& theVector, const int& numOfDigits)
{
    string str;
    cout << "Please enter " << numOfDigits 
	    << " digits number and then press enter (please include leading-zeros if needed)." << endl;

    getline(cin, str);

    //validation for input size.
    if (str.size() != numOfDigits) 
	   inputError();

    //validation for each digit in factor.
    for (int i = 0; i < numOfDigits; i++)
    {
	   if (str[i] - '0' < 0 || str[i] - '0' > 9)	  
		  inputError();

	   //if here current digit is valid and can place digit in vector.
	   theVector.push_back((int)(str[i] - '0'));
    }
}

//-------------------------------------------------------------------------------------------//

void printVector(vector<int>& resVector, const char* msg)
{
    bool nonZeroAppeard = false;
    int numberBeginHere = 0, maxVectorSize = resVector.size();
    vector<int>::iterator mostLeftDigit = resVector.begin();
    while (mostLeftDigit != resVector.end() && !nonZeroAppeard)
    {
	   if (*mostLeftDigit == 0)
	   {
		  mostLeftDigit++;
		  numberBeginHere++;
	   }
	   else
		  nonZeroAppeard = true;
    }
    
    cout << msg;
    if (!nonZeroAppeard)
	   cout << 0;
    for (int i = numberBeginHere; i < maxVectorSize; i++)
	   cout << resVector[i];
    cout << endl;
}

//--------------------------- LONG MULTIPICATION ALGORITHM FUNCTION -------------------------//


/*  Long multiplication algorithm implementaion.    */
/*  Iv'e made this algorithm efficient. the condition of (temp == 0) is saving time
    and makes T(n)=O(n^2) insted of Theta(n^2).        */
void longMulAlgorithm(vector<int>& resVector, const vector<int>& x, const vector<int>& y, int n)
{
    vector<int>::iterator mostRightDigit = resVector.end() - 1;
    for (int i = 1; i <= n; i++)    //running on each digit in y number (the second one).
    {
	   int temp = y[n - i];
	    if (temp == 0)	   //we can skip iteration, result is already 0
		    mostRightDigit--;		 
	    else					 */
	   {
		  int carry = 0, res;
		  mostRightDigit = resVector.end() - i;
		  carry = 0;

		  for (int j = 1; j <= n; j++)      //running on each digit in x number  (the first one).
		  {
			 // NOTE: res can be referred as an integer. Both temp and x[n-j] are digits so result is a maximum 2-digits number
			 res = temp * x[n - j];
			 if (res > 0 || carry > 0)
			 {
				*(mostRightDigit) += (res + carry);     //place digit in correct place
				if ((carry = *mostRightDigit / BASE) > 0)
				    *mostRightDigit %= BASE;        //updating current place to digit if needed
			 }
			 if (mostRightDigit != resVector.begin())
				mostRightDigit--;
		  }
		  if (carry > 0)
			 *(mostRightDigit) += carry;
	   }
    }
}



//-------------------------- KARATSUBA RECURSIVE ALGORITHM FUNCTION -------------------------//

/*  Recursive function implementaion to Karatsuba's algorithm.
    for two n-digits integers x,y =>	  x = a*10^n/2 + b	    ,	  y = c*10^n/2 + d
    x*y = (a*c)*10^n  +  ((a+b)*(c+d)-a*c-b*d)*10^n/2  +  b*d
    NOTE: determine:    sec1 = a*c;
			sec2 = (a+b)*(c+d)-a*c-b*d
			sec3 = b*d										   */
void karatsubaRecOut(const vector<int>& x, const vector<int>& y, int n, vector<int>& resVector)
{
    //keeping the original x,y const value and make copy of them.
    vector<int> nonConstX(x);
    vector<int> nonConstY(y);
    karatsubaRec(nonConstX, nonConstY, n, resVector);
}

void karatsubaRec(vector<int>& x, vector<int>& y, int n, vector<int>& resVector)
{
    //--- Base case: x and y have only one-cell. ---//
    if (n == 1)
    {
	   int num = x[0] * y[0];  //Performing multiply vectors' digits => maximum case: num is a 2-digits number 
	   if (num >= 0)
		  resVector.insert(resVector.end(), { num / BASE, num%BASE });
    }
    else
    {
	   if (n % 2 != 0)      //In case n is an odd number: according to the assumption that x and y are a n-length integers we'll pad those vectors with one leading zero.
	   {
		  x.insert(x.begin(), 0);
		  y.insert(y.begin(), 0);
		  n++;
	   }

	   //------ Parting x,y vectors to halves ------//
	   vector<int> a(x.begin(), x.begin() + n / 2);
	   vector<int> b(x.begin() + n / 2, x.end());
	   vector<int> c(y.begin(), y.begin() + n / 2);
	   vector<int> d(y.begin() + n / 2, y.end());

	   //------ Calculation of formula's 1 section -------//
	   vector<int> sec1;
	   karatsubaRec(a, c, n / 2, sec1);

	   //------ Calculation of formula's 3 section -------//
	   vector<int> sec3;
	   karatsubaRec(b, d, n / 2, sec3);

	   //--- Adjustments for formula's 1 and 3 sections ---// 
	   if (sec1.size() > (x.size()) || (sec3.size() > (y.size())))	   // resize only if n was originaly an odd number. in that case there are 2 leading zeros in sec1 and sec3
	   {
		  sec1.erase(sec1.begin(), sec1.begin() + 2);
		  sec3.erase(sec3.begin(), sec3.begin() + 2);
	   }
	   vector<int> sumSec1Sec3(sec1);
	   sumOfVectors(sumSec1Sec3, sec3);    //sum of sec1+sec3
	   mergeVectors(resVector, sec1, sec3);

	   //------ Calculation of formula's 2 section -------//
	   vector<int> sec2;
	   sumOfVectors(a, b);
	   sumOfVectors(c, d);
	   if (a.size() != c.size())    //padding with zero-leading if the sizes of a and c are different
		  (a.size() > c.size()) ? c.insert(c.begin(), 0) : a.insert(a.begin(), 0);

	   karatsubaRec(a, c, a.size(), sec2);	 //recalculate Karatsuba's formula with (a+b) and (c+d) in sums (a,c)
	   subVectors(sec2, sumSec1Sec3);	//sec2 = sec2 - (sec1 + sec3)   ( = (a+b)*(c*d)-a*c-b*d )
	   shiftLeft(sec2, n / 2);		//multiply sec2 by 10^n/2
	   sumOfVectors(resVector, sec2);
    }
}

//-------------------------------------------------------------------------------------------//

/*  Iterative function implementaion to Karatsuba's algorithm.
    for two n-digits integers x,y =>	  x = a*10^n/2 + b	    ,	  y = c*10^n/2 + d
    x*y = (a*c)*10^n  +  ((a+b)*(c+d)-a*c-b*d)*10^n/2  +  b*d
    NOTE: determine:    sec1 = a*c
			sec2 = b*d										   
			sec3 = (a+b)*(c+d)-a*c-b*d						   */
void karatsubaItrOut(const vector<int>& x, const vector<int>& y, int n, vector<int>& resVector)
{
    //keeping the original x,y const value and make copy of them..
    vector<int> nonConstX(x);
    vector<int> nonConstY(y);
    karatsubaItr(nonConstX, nonConstY, n, resVector);
}
void karatsubaItr(vector<int>& x, vector<int>& y, int n, vector<int>& resVector)
{
    Stack s;
    ItemType currItem(x, y, n, resVector, 1);
    Node currNode(currItem);
    s.Push(currNode);

    while (!s.IsEmpty())
    {
	   currItem = s.Pop().getItem();
	   int currLine = currItem.getLine();
	   int currN = currItem.getN();
	   vector<int> currResult = currItem.getRes();

	   //--- Base case: x and y have only one cell. ---//
	   if (currN == 1)
	   {
		  vector<int> currX = currItem.getFirstNumber();
		  vector<int> currY = currItem.getSecondNumber();
		  vector<int> res;
		  int num = currX[0] * currY[0];  //Performing multiply vectors' digits => maximum case: num is a 2-digits number 
		  if (num >= 0)
		  {
			  res = { num / BASE, num%BASE };
			  currItem.setRes(res);
		  }
		  //Update line and result in last call
		  ItemType updatingItem(s.Pop().getItem());
		  updatingItem.setRes(res);
		  updatingItem.setLine(updatingItem.getLine() + 1);
		  s.Push(updatingItem);
	   }

	   else
	   {
		  /*  In case n is an odd number: according to assumption that x and y
			 are a n-length integers we'll pad those vectors with one leading zero. */
		  if (currN % 2 != 0)
		  {
			 vector<int> currX = currItem.getFirstNumber();
			 currX.insert(currX.begin(), 0);
			 vector<int> currY = currItem.getSecondNumber();
			 currY.insert(currY.begin(), 0);
			 currItem.setFirstNumber(currX);
			 currItem.setSecondNumber(currY);
			 currItem.setNumber(++currN);
		  }


		  switch (currLine)
		  {
		  case SEC1_CALC:   //calculation of a*c
		  {
			 ItemType nextItem(currItem.a, currItem.c, currN / 2, currItem.sec1, 1);
			 s.Push(currItem);
			 s.Push(nextItem);
			 break;
		  }
		  case SEC2_CALC:   //calculation of b*d
		  {
			 currItem.sec1 = currResult;	   //if here: we already calculate sec1 result (a*c) so place it in correct vector.
			 currItem.clearVector(currResult);
			 currItem.setRes(currResult);
			 //start calculate (b*d) section
			 ItemType nextItem(currItem.b, currItem.d, currN / 2, currItem.sec2, 1);
			 s.Push(currItem);
			 s.Push(nextItem);
			 break;
		  }
		  case SEC3_CALC:   //calculation of (a+b)*(c+d)
		  {
			 currItem.sec2 = currResult;	//if here: we already calculate sec1 and sec2 result (a*c), (b*d) so place it in correct vector.
			 currItem.clearVector(currResult);
			 currItem.setRes(currResult);

			 //resize only if n was originaly an odd number. in that case there are 2 leading zeros in each of sec1 and sec3
			 if (currItem.sec1.size() > (currItem.getFirstNumber().size())
				|| (currItem.sec2.size() > (currItem.getSecondNumber().size())))
			 {
				currItem.sec1.erase(currItem.sec1.begin(), currItem.sec1.begin() + 2);
				currItem.sec2.erase(currItem.sec2.begin(), currItem.sec2.begin() + 2);
			 }

			 vector<int> tmpA(currItem.a);
			 sumOfVectors(tmpA, currItem.b); //(a+b)
			 vector<int> tmpC(currItem.c);
			 sumOfVectors(tmpC, currItem.d); //(c+d)
			 if (tmpA.size() != tmpC.size())	//padding with zero-leading if the sizes of tmpA and tmpC are different
				(tmpA.size() > tmpC.size()) ? tmpC.insert(tmpC.begin(), 0) : tmpA.insert(tmpA.begin(), 0);
			 ItemType nextItem(tmpA, tmpC, tmpA.size(), currItem.sec3, 1);
			 s.Push(currItem);
			 s.Push(nextItem);
			 break;
		  }
		  case FINAL_RESULT_CALC:   //summing sections
		  {
			 currItem.sec3 = currResult; //if here: we already calculate all sections. now we'll make adjustments for final result.
			 currItem.clearVector(currResult);
			 //sec1 and sec2 are not disturbing each other so we can merge them and put in result.
			 currResult.insert(currResult.end(), currItem.sec1.begin(), currItem.sec1.end());
			 currResult.insert(currResult.end(), currItem.sec2.begin(), currItem.sec2.end());
			 currItem.setRes(currResult);
			 vector<int> currSec3(currItem.sec3);
			 subVectors(currSec3, currItem.sec1);
			 subVectors(currSec3, currItem.sec2);	//sec3-sec1-sec2
			 shiftLeft(currSec3, currN / 2);	//multiply sec2 by 10^n/2
			 currItem.sec3 = currSec3;		//save the result of sec3
			 sumOfVectors(currResult, currItem.sec3);

			 /*  	if not all sections in the original vector are calculated, we need to place this
				currResult in correct section and move on to the  next section's calculation.
				else: insert currResult into the original resultVector.					    */
			 if (!s.IsEmpty())
			 {
				ItemType updateTop = s.Pop().getItem();
				updateTop.setRes(currResult);
				updateTop.setLine(updateTop.getLine() + 1);
				s.Push(updateTop);
			 }
			 else
				resVector.insert(resVector.end(), currResult.begin(), currResult.end());

			 break;
		  }
		  default:
			 break;
		  }
	   }
    }
}

//-------------------------------------------------------------------------------------------//

/*  Function shifting left the vector given shift. (equals to multiply result in BASE in power of shift).	  */
void shiftLeft(vector<int>& res, int shift)
{
    unsigned int sizeOfRes = res.size();
    res.insert(res.end(), shift, 0);
    while (sizeOfRes < res.size() && *res.begin() == 0)
	   res.erase(res.begin());
}

//-------------------------------------------------------------------------------------------//

/*  Function performing subtraction of two vectors. resultVector would contain the difference.
    NOTE: according to Karartsuba's algorithm, we can ensure that toSub represents smaller number than resultVector.   */
void subVectors(vector<int>& resultVector, vector<int>& toSub)
{
    int i;
    toSub.insert(toSub.begin(), resultVector.size() - toSub.size(), 0);
    vector<int>::iterator currPos = resultVector.end();
    for (i = 0; i < (int)toSub.size(); i++)
    {
	   currPos--;
	   *currPos -= (toSub[toSub.size() - i - 1]);
	   if (*currPos < 0)
	   {
		  *currPos += BASE;
		  if (currPos != resultVector.begin()) //if its not the last digit
			 (*(currPos - 1))--;
	   }
    }
}

//-------------------------------------------------------------------------------------------//

/*  Function performing addition of two vectors.
    resultVector would contain the sum and its size is changing according to toAdd-vector size.	  */
void sumOfVectors(vector<int>& resultVector, vector<int>& toAdd)
{
    int carry = 0;
    if (resultVector.size() < toAdd.size()) //resize
	   resultVector.insert(resultVector.begin(), toAdd.size() - resultVector.size(), 0);
    else
	   toAdd.insert(toAdd.begin(), resultVector.size() - toAdd.size(), 0);
        vector<int>::iterator currPos = resultVector.end();
    for (int i = 0; i < (int)toAdd.size(); i++)
    {
	   currPos--;
	   *(currPos) += toAdd[toAdd.size() - i - 1]; //place digit in correct place
	   if ((carry = *currPos / BASE) > 0)
	   {
		  *currPos %= BASE; //updating 2-digit number to a digit
		  if (currPos != resultVector.begin()) //if it isn't the last digit
			 (*(currPos - 1)) += carry;
		  else if (carry > 0)
			 resultVector.insert(resultVector.begin(), carry);
	   }
    }
}

//-------------------------------------------------------------------------------------------//

/*  Function performing merge of 2 vectors into one big vector by input order.
    size of dest vectors is the size of v1 + the size of v2.     */
void mergeVectors(vector<int>& dest, const vector<int>& v1, const vector<int>& v2)
{
    dest.clear();
    dest.insert(dest.end(), v1.begin(), v1.end());
    dest.insert(dest.end(), v2.begin(), v2.end());
}

//----------------------------------------------------------------------------//

int main()
{
    int n;
    string str;
    cout << "Please enter non-negative integer that represents the number of digits in each number and then press enter. \n"
	    << "NOTE: The number can't include leading-zeros." << endl;

    getline(cin, str);
	
    // validation of entered number and checking if there are leading-zeros.
    if (str.size() < 1)       
	   inputError();
    if (str[0] == '0')
    {
	   if (str.size() == 1)
	   {
		  cout << "This is the trivial case. None of the natural numbers has 0 digits. \n";
		  return 0;
	   }
	    inputError();   //The number can't include leading-zeros.
    }

    // validation of entered string's characters. Checking if each char is a digit. 
    for (int i = 0; i < (int)str.size(); i++)
	   if (str[i] - '0' < 0 || str[i] - '0' > 9)
		  inputError();

    //if here - n is valid. transform string to integer.
    n = stoi(str);    
    
    vector<int> x;
    cout << "Entering the first factor:" << endl;
    factorReader(x, n);

    vector<int> y;
    cout << "Entering the second factor:" << endl;
    factorReader(y, n);

    cout << SEPARATOR << "\nThe results of multipication entered numbers:\n" << SEPARATOR << endl;
    
    /*  NOTE:	The printed-output should not contain leading zeros.
    		However, the result-vector of each algorithm can contain zeros.   */

    //-------------------------------------------------------------------------------------------//
    //------------------ PERFORMING LONG MULTIPLICATION ALGORITHM FUNCTION ----------------------//
    //-------------------------------------------------------------------------------------------//

    vector<int> resVectorLongAlgo(2*n);   //vector contains 2n cells initialized by 0.
    longMulAlgorithm(resVectorLongAlgo, x, y, n);
    printVector(resVectorLongAlgo, "Long multiplication: x * y = ");

    //-------------------------------------------------------------------------------------------//
    //----------------------- PERFORMING KARATSUBA ALGORITHM FUNCTIONS --------------------------//
    //-------------------------------------------------------------------------------------------//
    
    ///////////////////////// PERFORMING KARATSUBA RECURSIVE ALGORITHM ////////////////////////////

    vector<int> resVectorKaratsubaRec;
    karatsubaRecOut(x, y, n, resVectorKaratsubaRec);
    printVector(resVectorKaratsubaRec, "Karatsuba (recursive): x * y = ");
    
    ///////////////////////// PERFORMING KARATSUBA ITERATIVE ALGORITHM ////////////////////////////
    
    vector<int> resVectorKaratsubaItr;
    karatsubaItrOut(x, y, n, resVectorKaratsubaItr);
    printVector(resVectorKaratsubaItr, "Karatsuba (iterative): x * y = ");
    
    //-------------------------------------------------------------------------------------------//

    return 0;
}
