#include <iostream>
using namespace std;

//Рекурсивная функция: выполняется бесконечно, условие завершает действие
int sum_number (int a, int b){
    int result = a;

    for (int i = 0; i < b; i++){
        result = result + 1;
    }
    return result;
}

int main(){
    setlocale(LC_ALL, "ru");
    int a, b;
    
    cout << "Введите первое число: ";
    cin >> a;
    cout << "Введите второе число: ";
    cin >> b;

    cout << "Сумма чисел: " << a << " + " << b << " = " << sum_number(a, b);

    return 0;
}





