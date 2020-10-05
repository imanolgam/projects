//Recursive exercises
#include <iostream>

using namespace std;
//SUM
int operation;
int Sum (int x, int n)
{
    if (n==0)
    {
        return 0;
    }
    else
    {
        int operation = x+Sum(x, n-1);
        return (operation);
    }
}

int Power (int x, int n)
{
    if (n==0)
    {
        return 1;
    }
    else
    {
        int operation = x*Power(x, n-1);
        return (operation);
    }
}

int fibSeries(int n)
{
    if(n <= 1)
    {
        return 1;
    }
    else
    {
        int operation = fibSeries(n-1) + fibSeries(n-2);
        return operation ;
    }   
};

int sumDigitNum (int num)
{  
    if(num == 0)
    {
        return 0;
    }
    else
    {
        int operation = sumDigitNum(num / 10) + (num % 10);
        return operation;
    }
};

 int main()
 {
     cout << "Result of the sum: " << Sum(2,100) << endl;

     cout << "Result of the power: " << Power(2,3) << endl;

     cout << "Result of the first term of the fibonacci serie is: " << fibSeries(0) << endl;
     cout << "Result of the second term of the fibonacci serie is: " << fibSeries(1) << endl;
     cout << "Result of the third term of the fibonacci serie is: " << fibSeries(2) << endl;
     cout << "Result of the fourth term of the fibonacci serie is " << fibSeries(3) << endl;
     cout << "Result of the fifth term of the fibonacci serie is: " << fibSeries(4) << endl;
     cout << "Result of the sixth term of the fibonacci serie is: " << fibSeries(5) << endl;

     cout << "The sum of the digits is: " << sumDigitNum(123) << endl;
     cout << "The sum of the digits is: " << sumDigitNum(1027) << endl;
     cout << "The sum of the digits is: " << sumDigitNum(43) << endl;
 }
