#include <iostream>
#include <Windows.h>

using namespace std;
void printm(int order, float **matrix){
    cout << endl;
    for(int i = 0; i< order; i++){
        for(int j = 0; j< order; j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
}

int main()
{
    cout << "Matrix order:\n";
    int order = 0;
    cin >> order;
    float **matrix = new float*[order];
    cout << "Input rows el:\n";
    for(int i = 0; i < order; i++){
        matrix[i] = new float[order];
        for(int j = 0; j < order; j++){
            cin >> matrix[i][j];
        }
    }
    SYSTEMTIME sysTime1, sysTime2;
    GetLocalTime(&sysTime1);
    cout << "Det solution:\n";
    float det = 1;
    int position = 0;
    while(position != order){
        //printm(order,matrix);
        for(int i = position; i < order; i++){
            float beg = matrix[i][position];
            if(beg == 0) continue;
            det*=beg;
            for(int j = position; j < order; j++){
                matrix[i][j] /= beg;
            }
        }

        for(int i = position+1; i < order; i++){
            if(matrix[i][position] == 0) continue;
            for(int j = position; j < order; j++){
                matrix[i][j] -= matrix[position][j];
            }
        }
        ++position;
    }
    GetLocalTime(&sysTime2);
    cout << "det: " << det << endl;
    cout << "Calculation time(ms): " << ((sysTime2.wMinute - sysTime1.wMinute) * 60 + sysTime2.wSecond - sysTime1.wSecond) * 1000
            + sysTime2.wMilliseconds - sysTime1.wMilliseconds << endl;

    return 0;
}
