#ifndef SQMATRIXDET_H
#define SQMATRIXDET_H
#include <sqmatrix.h>

class sqMatrixDet : public sqMatrix
{
    int det;
public:
    sqMatrixDet();
    sqMatrixDet(unsigned int order,float **value);
    sqMatrixDet(const sqMatrix& matrix);
    ~sqMatrixDet();

    sqMatrixDet(sqMatrix& matrix);

    int sloveDet();
    void print() const;
};

#endif // SQMATRIXDET_H
