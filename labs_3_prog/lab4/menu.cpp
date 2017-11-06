#include "menu.h"

void doSomeOp(sqMatrix *matrix){
    sqMatrix *matrixCopy = new sqMatrix(*matrix);

    matrix->transpose();

    cout << "After transpose:\n";
     matrix->print();
    cout << "Matrix by copy constructor:\n";
    matrixCopy->print();

    cout << "Matrix by copy constructor + your matrix:\n";
    (*matrix+*matrixCopy).print();

    cout << "Your matrix - matrix by copy constructor:\n";
    (*matrix-*matrixCopy).print();

    cout << "Your matrix to int(return order):\n" << (int)*matrix << endl;

    cout << "Your matrix++:\n";
    (++(*matrix)).print();

    delete matrixCopy;
}

void createNew(){
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

    doSomeOp(sqmatrix);

    cout << "Save to file?\n"
            "0) NO!\n"
            "1) Save to matrix.txt\n"
            "2) Save to matrix.bin\n";
    ushort choose = 0;
    cin >> choose;
    switch (choose) {
    case 0:
        break;
    case 1:
        saveTxt(sqmatrix);
        break;
    case 2:
        saveBin(sqmatrix);
        break;
    default:
        break;
    }

    delete defaultMatrix;
    delete sqmatrix;

    for (int i = 0; i < order; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

sqMatrix loadBin(){
    std::ifstream inputBin("matrix.bin", std::ios_base::binary);
    sqMatrix *sqmatrix = new sqMatrix;
    sqmatrix->read(inputBin);
    cout << "Your matrix:\n";
    sqmatrix->print();

    doSomeOp(sqmatrix);

    cout << "Save to file?\n"
            "0) NO!\n"
            "1) Save to matrix.txt\n"
            "2) Save to matrix.bin\n";
    ushort choose = 0;
    cin >> choose;
    switch (choose) {
    case 0:
        break;
    case 1:
        saveTxt(sqmatrix);
        break;
    case 2:
        saveBin(sqmatrix);
        break;
    default:
        break;
    }

    delete sqmatrix;
}

sqMatrix loadTxt(){
    ifstream input("matrix.txt");
    sqMatrix *sqmatrix = new sqMatrix;
    input >> *sqmatrix;
    input.close();

    cout << "Your matrix:\n";
    sqmatrix->print();

    doSomeOp(sqmatrix);

    cout << "Save to file?\n"
            "0) NO!\n"
            "1) Save to matrix.txt\n"
            "2) Save to matrix.bin\n";
    ushort choose = 0;
    cin >> choose;
    switch (choose) {
    case 0:
        break;
    case 1:
        saveTxt(sqmatrix);
        break;
    case 2:
        saveBin(sqmatrix);
        break;
    default:
        break;
    }

    delete sqmatrix;

}

void saveBin(sqMatrix *matrix){
    std::ofstream outputBin("matrix.bin", std::ios_base::binary);
    matrix->write(outputBin);
    outputBin.close();
}

void saveTxt(sqMatrix *matrix){
    ofstream output("matrix.txt");
    output << *matrix << std::endl;
//    output << matrix << std::endl;
    output.close();
    cout << "Saved!\n";
}
