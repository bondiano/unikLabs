#include "sqmatrix.h"
#include <iostream>

sqMatrix::sqMatrix()
{
    order = 1;
    value = new float*;
    *value = new float;
    value[0][0] = 1;
}

sqMatrix::sqMatrix(unsigned int order, float **value)
{
    this->order = order;
    this->value = new float*[order];
    for(unsigned int i = 0; i < order; i++){
        this->value[i] = new float[order];
        for(unsigned int j = 0; j < order; j++){
            this->value[i][j] = value[i][j];
        }
    }
}

sqMatrix::sqMatrix(sqMatrix &matrix)
{
    order = matrix.order;
    value = new float*[order];
    for(unsigned int i = 0; i < order; i++){
        value[i] = new float[order];
        for(unsigned int j = 0; j < order; j++){
            value[i][j] = matrix.value[i][j];
        }
    }
}

sqMatrix::~sqMatrix()
{
    for (unsigned int i = 0; i < order; i++) {
        delete[] value[i];
    }
    delete[] value;
}

void sqMatrix::transpose()
{
    float temp = 0;
    for(unsigned int i = 0; i < order; i++){
        for(unsigned int j = i; j < order; j++){
            temp = value[i][j];
            value[i][j] = value[j][i];
            value[j][i] = temp;
        }
    }
}

void sqMatrix::print()
{
    for(unsigned int i = 0; i < order; i++){
        for(unsigned int j = 0; j < order; j++){
            std::cout << value[i][j] << ' ';
        }
        std::cout << '\n';
    }
}
