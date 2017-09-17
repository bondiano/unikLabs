#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "rows count, elements in rows count:\n";
    int rc = 0, el = 0;
    cin >> rc >> el;
    double **matrix = new double*[rc];
    cout << "enter rows el:\n";
    for(int i = 0; i < rc; i++){
        matrix[i] = new double[el];
        for(int j = 0; j < el; j++){
            cin >> matrix[i][j];
        }
    }

    cout << "your matrix:\n";
    for(int i = 0; i< rc; i++){
        for(int j = 0; j< el; j++){
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
    double det = 1;
    int position = 0;
    while(position != rc){
        for(int i = 0; i < rc; i++){
            det *= matrix[i][i];
            double beg = matrix[i][i];
            for(int j = 0; j < el; j++)
                matrix[i][j] /= beg;
        }


        for(int i = position; i < rc; i++){
            for(int j = position; j < el; j++){
                matrix[i][j] -= matrix[position][j];
            }
        }
        position++;
    }

    cout << "your matrix after operations:\n";
    for(int i = 0; i< rc; i++){
        for(int j = 0; j< el; j++){
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }

    cout << "det: " << det << endl;

    return 0;
}
