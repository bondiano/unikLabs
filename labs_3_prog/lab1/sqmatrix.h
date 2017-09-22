#ifndef SQMATRIX_H
#define SQMATRIX_H


class sqMatrix
{
unsigned int order;
float **value;

public:
    sqMatrix();
    sqMatrix(unsigned int order,float **value);
    sqMatrix(sqMatrix& matrix);
    ~sqMatrix();
    void transpose();
    void print();
};

#endif // SQMATRIX_H
