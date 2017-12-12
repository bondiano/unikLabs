#include <iostream>
#include <sqmatrix.h>
#include <sqmatrixdet.h>
#include <namedmatrix.h>
#include <menu.h>
#include <list.h>
/* Лаб 6.
 * Задание: Добавить в классы и демонстрационную программу обработку исключений при возникновении ошибок:
 * недостатка памяти, выход за пределы диапазона допустимых значений и т.д.
 * Изменить основную программу так, чтобы она демонстрировала обработку исключений.
 */

using namespace std;

int main()
{
    // Call menu functions
    cout << "1) Create new matrix; \n"
            "2) Load from matrix.bin file; \n"
            "3) Load from matrix.txt file; \n";
    ushort choose = 0;
    cin >> choose;
    switch (choose) {
    case 1:
        createNew();
        break;
    case 2:
        loadBin();
        break;
    case 3:
        loadTxt();
        break;
    default:
        break;
    }

    return 0;
}
