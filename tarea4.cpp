//Ejercicio 4 tarea 1
#include <iostream>


using namespace std;
template <class C>
class Calculator
{
    public:

    C sumar (C num1, C num2) 
    {   
        C result = num1 + num2;
        cout << result << endl;
        return result;

    }
    C restar (C num1, C num2)
    {
        C result = num1 - num2;
        cout << result << endl;
        return result;
    }
    C multiplicar (C num1, C num2)
    {
        C result = num1 * num2;
        cout << result << endl;
        return result;
    }
    C dividir (C num1, C num2)
    {
        C result = num1 / num2;
        cout << result << endl;
        return result;
    }
};

int main()
{
    Calculator <int> num;
    num.sumar(2, 3);
    num.dividir(6,2);
    num.restar(5,3);
    num.multiplicar(6,6);

}