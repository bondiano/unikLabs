#include <iostream>
#include <sqmatrix.h>
/*Для класса из лаб. работы №1 реализовать набор операций для работы с объектами класса: сложение (как метод класса), вычитание (как дружественную функцию), инкремент постфикс-ный и префиксный, преобразование к разным типам (по усмотрению студентов и преподавате-ля).
Изменить демонстpационную пpогpамму, продемострировав все перегруженные опера-ции.*/

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
