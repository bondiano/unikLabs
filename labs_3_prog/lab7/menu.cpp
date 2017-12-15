#include "menu.h"
using namespace std;

void saveBin(sqMatrix *matrix){
    try{
        std::ofstream outputBin("matrix.bin", std::ios_base::binary);
        matrix->write(outputBin);
        outputBin.close();
    } catch (const runtime_error exp) {
        cout << exp.what() << endl;
    }
}

void saveTxt(sqMatrix *matrix){
    try{
        ofstream output("matrix.txt");
        output << *matrix << std::endl;
        output.close();
        cout << "Saved!\n";
    } catch (const runtime_error exp) {
        cout << exp.what() << endl;
    }
}

void getNumber(sqMatrix *matrix){
    unsigned row = 0;
    unsigned col = 0;
    cout << "Enter row:\n";
    cin >> row;
    cout << "Enter column:\n";
    cin >> col;

    try {
        cout << matrix->getAt(row - 1, col - 1) << endl;
    } catch (const runtime_error exp) {
        cout << exp.what() << endl;
    }
}

void doSomeOp(sqMatrix *matrix){

    sqMatrix *matrixCopy = new sqMatrix(*matrix);

    try {
        matrix->transpose();
    } catch (const runtime_error exp) {
        cout << exp.what() << endl;
    }

    try {
        cout << "After transpose:\n";
        matrix->print();
    } catch (const runtime_error exp) {
        cout << exp.what() << endl;
    }

    try{
        cout << "Matrix by copy constructor:\n";
        matrixCopy->print();
    } catch (const runtime_error exp) {
        cout << exp.what() << endl;
    }

    try {
        cout << "Matrix by copy constructor + your matrix:\n";
        (*matrix+*matrixCopy).print();
    } catch (const runtime_error exp) {
        cout << exp.what() << endl;
    }

    try {
        cout << "Your matrix - matrix by copy constructor:\n";
        (*matrix-*matrixCopy).print();
    } catch (const runtime_error exp) {
        cout << exp.what() << endl;
    }

    try{
        cout << "Your matrix to int(return order):\n" << (int)*matrix << endl;
    } catch (const runtime_error exp) {
        cout << exp.what() << endl;
    }

    try {
        cout << "Your matrix++:\n";
        (++(*matrix)).print();
    } catch (const runtime_error exp) {
        cout << exp.what() << endl;
    }

    delete matrixCopy;
}

void createNew(){
    try {
        cout << "Enter matrix order:\n";
        int order = 0;
        cin >> order;
        float **matrix = new float*[order];
        cout << "Enter rows el:\n";
        for(int i = 0; i < order; i++) {
            matrix[i] = new float[order];
            for(int j = 0; j < order; j++) {
                cin >> matrix[i][j];
            }
        }

        sqMatrix *sqmatrix = new sqMatrix(order,matrix);
        cout << "Your matrix:\n";
        sqmatrix->print();

        doSomeOp(sqmatrix);

        cout << "Save to file?\n"
                "0) NO!\n"
                "1) Get number\n"
                "2) Save to matrix.txt\n"
                "3) Save to matrix.bin\n";
        ushort choose = 0;
        cin >> choose;
        switch (choose) {
        case 0:
            break;
        case 1:
            getNumber(sqmatrix);
            break;
        case 2:
            saveTxt(sqmatrix);
            break;
        case 3:
            saveBin(sqmatrix);
            break;
        default:
            break;
        }

        delete sqmatrix;
        for (int i = 0; i < order; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    } catch (const runtime_error exp) {
        cout << exp.what() << endl;
    }
}

void loadBin(){
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

void loadTxt(){
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
