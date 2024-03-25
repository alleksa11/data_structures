#include <iostream>

using namespace std;

// Функция для нахождения обратного элемента
int findInverse(int a, int n) {
    int t = 0, newt = 1;
    int r = n, newr = a;

    while (newr != 0) {
        int quotient = r / newr;
        int temp = newt;
        newt = t - quotient * newt;
        t = temp;

        temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }

    if (r > 1)
        return 0; // Обратного элемента не существует
    if (t < 0)
        t += n;
    
    return t;
}

int main() {
    while (true) {
        int a, n;
        cout << "Введите число a: ";
        cin >> a;
        cout << "Введите число n: ";
        cin >> n;

        if (n == 0) {
            cout << "Ошибка: n не может быть равно 0." << endl;
            continue; // Переход на следующую итерацию цикла
        }

        int inverse = findInverse(a, n);
        if (inverse != 0) {
            cout << "Обратный элемент к числу " << a << " по модулю " << n << " равен: " << inverse << endl;
        } else {
            cout << "Обратного элемента к числу " << a << " по модулю " << n << " не существует." << endl;
        }

        char choice;
        cout << "Хотите продолжить (y/n)? ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break; // Выход из цикла
        }
    }

    return 0;
}

