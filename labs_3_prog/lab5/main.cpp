#include <iostream>
#include <sqmatrix.h>
#include <sqmatrixdet.h>
#include <namedmatrix.h>
#include <menu.h>
#include <list.h>

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
    List* matrixList = new List();
    sqMatrix sq(order, matrix);
    cout << "Enter matrix order for matrix 2:\n";
    cin >> order;
    cout << "Enter rows el:\n";
    float **namedValue = new float*[order];
    for(int i = 0; i < order; i++){
        namedValue[i] = new float[order];
        for(int j = 0; j < order; j++){
            cin >> namedValue[i][j];
        }
    }
    namedMatrix namedM(order, namedValue, "meow");

    cout << "Enter matrix order for matrix 3:\n";
    cin >> order;
    cout << "Enter rows el:\n";
    float **detValue = new float*[order];
    for(int i = 0; i < order; i++){
        detValue[i] = new float[order];
        for(int j = 0; j < order; j++){
            cin >> detValue[i][j];
        }
    }
    sqMatrixDet detM(order, detValue);

    matrixList->pushBack(sq);
    matrixList->pushBack(namedM);
    matrixList->pushBack(detM);
    matrixList->printAll();
    matrixList->popForward();
    matrixList->printAll();
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
    //delete matrixDet;
    //delete matrixNamed;
    return 0;
}
