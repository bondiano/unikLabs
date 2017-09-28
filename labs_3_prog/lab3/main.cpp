#include <iostream>
#include <sqmatrix.h>
/*Для класса из лаб. работы №2 перегрузить операции ввода/вывода, позволяющие осу-ществлять ввод и вывод в удобной фоpме об'ектов классов:
•	вывод в текстовый файл;
•	ввод/вывод из двоичного файла / в двоичный файл.
Изменить демонстpационную пpогpамму. В файл сохранять все созданные объекты. При загрузке в программу создавать объекты с параметрами, записанными в файл.
.*/

using namespace std;

int main()
{
    cout << "Default matrix constructor's matrix:\n";
    sqMatrix *defaultMatrix = new sqMatrix();
    defaultMatrix->print();

    cout << "Enter matrix order:\n";
    int order = 0;
    cin >> order;
    cout << "Enter rows el:\n";
    float **matrix = new float*[order];
    for(int i = 0; i < order; i++){
        matrix[i] = new float[order];
        for(int j = 0; j < order; j++){
            cin >> matrix[i][j];
        }
    }
    sqMatrix *sqmatrix = new sqMatrix(order,matrix);
    cout << "Your matrix:\n";
    sqmatrix->print();

    sqMatrix *matrixCopy = new sqMatrix(*sqmatrix);

    sqmatrix->transpose();

    cout << "After transpose:\n";
     sqmatrix->print();
    cout << "Matrix by copy constructor:\n";
    matrixCopy->print();

    cout << "Matrix by copy constructor + your matrix:\n";
    (*sqmatrix+*matrixCopy).print();

    cout << "Your matrix - matrix by copy constructor:\n";
    (*sqmatrix-*matrixCopy).print();

    cout << "Your matrix to int(return order):\n" << (int)*sqmatrix << endl;

    cout << "Your matrix++:\n";
    (++(*sqmatrix)).print();

    delete defaultMatrix;
    delete sqmatrix;
    delete matrixCopy;

    for (int i = 0; i < order; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}
