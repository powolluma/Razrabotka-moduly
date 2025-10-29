#include <iostream>
using namespace std;

//Рекурсивная функция: выполняется бесконечно, условие завершает действие
int reverse(int a, int reversed = 0) {
    if (a == 0) {
        return reversed; //Если = 0, то возвращаемся к reversed
    }
    return reverse(a / 10, reversed * 10 + a % 10); //Иначе возвращаем значение функции (формула для нахождения перевернутого числа)
}

int main() {
    setlocale (LC_ALL, "ru");

    int a;
    cout << "Введите число: ";
    cin >> a;
    cout << "Перевернутое число: " << reverse(a) << endl;

    return 0;
}




