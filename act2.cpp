//Actividad 2: Recursión
//Imanol García
//Bernardo Reyes
#include <iostream>

using namespace std;
//Ejercicio 1:
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

//Ejercicio 2: 
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

//Ejercicio 5:
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

//Ejercicio 6:
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
     cout << "el resultado de la suma es: " << Sum(2,100) << endl;

     cout << "el resultado de la potencia es: " << Power(2,3) << endl;

     cout << "el resultado del primer término de la serie de fibonacci es: " << fibSeries(0) << endl;
     cout << "el resultado del segundo término de la serie de fibonacci es: " << fibSeries(1) << endl;
     cout << "el resultado del tercer término de la serie de fibonacci es: " << fibSeries(2) << endl;
     cout << "el resultado del cuarto término de la serie de fibonacci es: " << fibSeries(3) << endl;
     cout << "el resultado del quinto término de la serie de fibonacci es: " << fibSeries(4) << endl;
     cout << "el resultado del sexto término de la serie de fibonacci es: " << fibSeries(5) << endl;

     cout << "La suma de los digitos es: " << sumDigitNum(123) << endl;
     cout << "La suma de los digitos es: " << sumDigitNum(1027) << endl;
     cout << "La suma de los digitos es: " << sumDigitNum(43) << endl;
 }