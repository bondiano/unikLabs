#include <iostream>
#include <sqmatrix.h>
/*Постpоить класс для pаботы с квадратными матрицами. Класс должен включать соответству-ющие поля: порядок, набор коэффициентов (динамическое выделение памяти).
Класс должен обеспечивать пpостейшие функции для pаботы с данными классами: транспони-рование матрицы, вывод матрицы в удобной форме. */

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

    delete defaultMatrix;
    delete sqmatrix;
    delete matrixCopy;

    for (int i = 0; i < order; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}
