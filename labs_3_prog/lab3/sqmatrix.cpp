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

sqMatrix::sqMatrix(const sqMatrix &matrix)
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

unsigned int sqMatrix::getOrder()
{
    return order;
}

float sqMatrix::getAt(unsigned int row, unsigned int col)
{
    return value[row][col];
}

sqMatrix sqMatrix::operator+(sqMatrix matrix)
{
    if(order != matrix.getOrder()){
        sqMatrix m;
        return m;
    }

    float ** rValue = new float*[order];
    for(unsigned int i = 0; i < order; i++){
            rValue[i] = new float[order];
        for(unsigned int j = 0; j < order; j++){
            rValue[i][j] = value[i][j] + matrix.getAt(i,j);
        }
    }
    sqMatrix resut(order,rValue);

    return resut;
}

sqMatrix &sqMatrix::operator= (sqMatrix matrix)
{
    if(this == &matrix){
        return *this;
    }

    if(value != nullptr){
        for (unsigned int i = 0; i < order; i++) {
            delete[] value[i];
        }
        delete[] value;
    }

    if(matrix.getOrder() != order){
        order = matrix.getOrder();
        value = new float*[order];
        for(unsigned int i = 0; i < order; i++){
            value[i] = new float[order];
            for(unsigned int j = 0; j < order; j++){
                value[i][j] = matrix.getAt(i,j);
            }
        }
        return *this;
    }

    for(unsigned int i = 0; i < order; i++){
        for(unsigned int j = 0; j < order; j++){
            value[i][j] = matrix.getAt(i,j);
        }
    }

    return *this;

}

sqMatrix sqMatrix::operator++(int)
{
    float ** rValue = new float*[order];
    for(unsigned int i = 0; i < order ; i++){
        rValue[i] = new float[order];
        for(unsigned int j = 0; j < order; j++)
            rValue[i][j] = value[i][j] + 1;
    }
    sqMatrix resut(order,rValue);
    return resut;
}

sqMatrix &sqMatrix::operator++()
{
    for(unsigned int i = 0; i < order ; i++){
        for(unsigned int j = 0; j < order; j++)
             value[i][j] += 1;
    }
    return *this;
}

sqMatrix sqMatrix::operator--(int)
{
    float ** rValue = new float*[order];
    for(unsigned int i = 0; i < order ; i++){
        rValue[i] = new float[order];
        for(unsigned int j = 0; j < order; j++)
            rValue[i][j] = value[i][j] - 1;
    }
    sqMatrix resut(order,rValue);
    return resut;
}

sqMatrix &sqMatrix::operator--()
{
    for(unsigned int i = 0; i < order ; i++){
        for(unsigned int j = 0; j < order; j++)
             value[i][j] -= 1;
    }
    return *this;
}

sqMatrix::operator int() const
{
    return order;
}

sqMatrix operator-(sqMatrix matrix1, sqMatrix matrix2)
{
    if(matrix1.order != matrix2.order){
        sqMatrix m;
        return m;
    }

    float ** rValue = new float*[matrix1.order];
    for(unsigned int i = 0; i < matrix1.order; i++){
            rValue[i] = new float[matrix1.order];
        for(unsigned int j = 0; j < matrix1.order; j++){
            rValue[i][j] = matrix1.value[i][j] - matrix2.value[i][j];
        }
    }
    sqMatrix resut(matrix1.order,rValue);

    return resut;
}
