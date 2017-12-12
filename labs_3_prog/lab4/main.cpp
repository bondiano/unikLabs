#include <iostream>
#include <sqmatrix.h>
#include <sqmatrixdet.h>
#include <namedmatrix.h>
#include <menu.h>

/*Для классов предыдущей лабораторной работы реализовать иерархию, изменяя отдельные методы и добавляя члены-данные (по усмотрению студента и преподавателя). В иерархию должно входить 2 производных класса. Один из методов должен быть виртуальным.

Изменить демонстрационную программу так, чтобы она демонстрировала создание, копирование объектов родственных типов, работу виртуальных функций.
.*/

using namespace std;

int main()
{
    cout << "Enter matrix order for matrix:\n";
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
    cout << "Input name for namedMatrix\n";
    char name[256];
    cin >> name;
    sqMatrix *matrixNamed = new namedMatrix(order, matrix, name);
    cout << "Your matrix:\n";
    matrixNamed->print();
    sqMatrix *matrixDet = new sqMatrixDet(order, matrix);
    cout << "Your matrix:\n";
    matrixDet->print();

    sqMatrixDet bbb(order,matrix);
    bbb.print();
    delete matrixDet;
   // delete matrixNamed;
    return 0;
}
