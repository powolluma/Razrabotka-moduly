#include <iostream>
using namespace std;

//Рекурсивная функция: выполняется бесконечно, условие завершает действие
int fibonacci(int a) {
    if (a <= 1) {
        return a; //Если n <= 1, то возвращаем значение n
    } 
    return fibonacci(a - 1) + fibonacci(a - 2); //Иначе возвращаем n-1 и n-2, пока n не станет равным 1 и 0
}

int main() {
    setlocale (LC_ALL, "ru");
    int a;
    cout << "Введите число: ";
    cin >> a;
    cout << "Число Фибоначчи: " << fibonacci(a) << endl;
    return 0;
}