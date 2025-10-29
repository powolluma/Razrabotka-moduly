#include <iostream>
using namespace std;

//Рекурсивная функция: выполняется бесконечно, условие завершает действие
int gcd(int a, int b) {
    if (b == 0) {
        return a; //Если b = 0, то возвращаемся к значению a
    } 
    return gcd (b, a % b); //Иначе возвращаем a % b  и  b
}

int main() {
    setlocale (LC_ALL, "ru");
    int a, b;
    cout << "Введите первое число: ";
    cin >> a;
    cout << "Введите второе число: ";
    cin >> b;
    cout << endl;
    cout << "НОД: " << gcd(a, b) << endl; //Вызываем полученное значение от a и b
    return 0;
}