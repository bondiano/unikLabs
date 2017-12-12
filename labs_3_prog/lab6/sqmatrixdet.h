#ifndef SQMATRIXDET_H
#define SQMATRIXDET_H
#include <sqmatrix.h>

class sqMatrixDet : public sqMatrix
{
    int det;
public:
    sqMatrixDet() : sqMatrix(), det(1) { }
    sqMatrixDet(unsigned int order,float **value) : sqMatrix(order, value), det(sloveDet()) { }
    sqMatrixDet(const sqMatrix &matrix): sqMatrix(matrix), det(sloveDet()) { }
    ~sqMatrixDet();

    int sloveDet();
    void print() const;
};

#endif // SQMATRIXDET_H
