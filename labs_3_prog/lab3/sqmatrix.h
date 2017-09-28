#ifndef SQMATRIX_H
#define SQMATRIX_H
#include <ostream>
#include <istream>

class sqMatrix
{
unsigned int order;
float **value;

public:
    //lab 1
    sqMatrix();
    sqMatrix(unsigned int order,float **value);
    sqMatrix(const sqMatrix& matrix);
    ~sqMatrix();
    void transpose();
    void print();
    unsigned int getOrder();
    float getAt(unsigned int row, unsigned int col);

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
    friend std::iostream& operator<<(std::ostream &os, sqMatrix &matrix);
    friend std::istream& operator>>(std::istream &is, sqMatrix &matrix);
    void read(std::istream &is);
    void write(std::ostream &os);
};

#endif // SQMATRIX_H
