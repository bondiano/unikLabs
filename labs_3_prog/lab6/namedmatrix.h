#ifndef NAMEDMATRIX_H
#define NAMEDMATRIX_H
#include <sqmatrix.h>
#include <cstring>


class namedMatrix : public sqMatrix
{
    char* name;
public:
    namedMatrix() : sqMatrix(), name("Default") { }
    namedMatrix(const sqMatrix& matrix) : sqMatrix(matrix), name("Copied") { }
    namedMatrix(unsigned int order,float **value, char* name);
    ~namedMatrix();

    void print() const;
};

#endif // NAMEDMATRIX_H
