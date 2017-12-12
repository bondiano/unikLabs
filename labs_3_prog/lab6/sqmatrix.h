#ifndef SQMATRIX_H
#define SQMATRIX_H
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <exception>

class sqMatrix
{
protected:
    unsigned int order;
    float **value;

public:
    //lab 1
    sqMatrix();
    sqMatrix(unsigned int order,float **value);
    sqMatrix(const sqMatrix& matrix);
    ~sqMatrix();
    void transpose();
    unsigned int getOrder() const;
    float getAt(unsigned int row, unsigned int col) const;

    //lab2
    sqMatrix operator+(sqMatrix matrix);
    friend sqMatrix operator-(sqMatrix matrix1,  sqMatrix matrix2);
    operator int() const;
    sqMatrix &operator= (sqMatrix matrix);
    sqMatrix operator++(int);
    sqMatrix &operator++();
    sqMatrix operator--(int);
    sqMatrix &operator--();

    //lab3
    friend std::ostream& operator<<(std::ostream &os, sqMatrix &matrix);
    friend std::istream& operator>>(std::istream &is, sqMatrix &matrix);
    void read(std::istream &is);
    void write(std::ostream &os);

    //lab4
    virtual void print() const;

    //lab5
   bool operator== (sqMatrix& matrix);
   float** getValues();
};

#endif // SQMATRIX_H
