#include <iostream>
using namespace std;

//Рекурсивная функция: выполняется бесконечно, условие завершает действие
int sum_number(int a, int b){ 
    int result = 0;

    for(int i = 0; i < b; i++){
        result = result + a; //Пока выполняется условие в цикле, выполняется цикл
    }
    return result; //Цикл завершился, и значение result возвращается в функцию
}

int main(){

    int a,b;
    cout << "Введите первое число: ";
    cin >> a;
    cout << "Введите второе число: ";
    cin >> b;

    cout << "Произведение чисел: " << a << " * " << b << " = " << sum_number(a, b);

    return 0;
}
