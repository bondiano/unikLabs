#include "sqmatrixdet.h"

sqMatrixDet::sqMatrixDet(): sqMatrix(), det(1)
{

}

sqMatrixDet::sqMatrixDet(unsigned int order, float **value): sqMatrix(order, value), det(sloveDet())
{

}

sqMatrixDet::sqMatrixDet(const sqMatrix &matrix): sqMatrix(matrix), det(sloveDet())
{

}

sqMatrixDet::~sqMatrixDet()
{

}

int sqMatrixDet::sloveDet()
{
    float det = 1;
    unsigned position = 0;
    float **matrix = new float*[order];
    for(unsigned int i = 0; i < order; i++){
        matrix[i] = new float[order];
        for(unsigned int j = 0; j < order; j++){
            matrix[i][j] = value[i][j];
        }
    }
    while(position != order){
        for(unsigned i = position; i < order; i++){
            float beg = matrix[i][position];
            if(beg == 0) continue;
            det*=beg;
            for(unsigned j = position; j < order; j++){
                matrix[i][j] /= beg;
            }
        }

        for(unsigned i = position+1; i < order; i++){
            if(matrix[i][position] == 0) continue;
            for(unsigned j = position; j < order; j++){
                matrix[i][j] -= matrix[position][j];
            }
        }
        ++position;
    }
    for (unsigned int i = 0; i < order; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return det;
}

void sqMatrixDet::print() const
{
    sqMatrix::print();
    std::cout << "Det: " << det << std::endl;
}
