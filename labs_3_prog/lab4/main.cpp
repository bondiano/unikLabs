#include <iostream>
#include <sqmatrix.h>
#include <menu.h>

/*Для класса из лаб. работы №2 перегрузить операции ввода/вывода, позволяющие осу-ществлять ввод и вывод в удобной фоpме об'ектов классов:
•	вывод в текстовый файл;
•	ввод/вывод из двоичного файла / в двоичный файл.
Изменить демонстpационную пpогpамму. В файл сохранять все созданные объекты. При загрузке в программу создавать объекты с параметрами, записанными в файл.
.*/

using namespace std;

int main()
{
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
