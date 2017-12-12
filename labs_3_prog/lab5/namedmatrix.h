#ifndef NAMEDMATRIX_H
#define NAMEDMATRIX_H
#include <sqmatrix.h>
#include <cstring>


class namedMatrix : public sqMatrix
{
    char* name;
public:
    namedMatrix();
    namedMatrix(unsigned int order,float **value, char* name);
    namedMatrix(const sqMatrix& matrix);
    ~namedMatrix();

    namedMatrix(sqMatrix& matrix);

    void print() const;
};

#endif // NAMEDMATRIX_H
