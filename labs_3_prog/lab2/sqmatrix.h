#ifndef SQMATRIX_H
#define SQMATRIX_H


class sqMatrix
{
unsigned int order;
float **value;

public:
    sqMatrix();
    sqMatrix(unsigned int order,float **value);
    sqMatrix(const sqMatrix& matrix);
    ~sqMatrix();
    void transpose();
    void print();
    unsigned int getOrder();
    float getAt(unsigned int row, unsigned int col);

    sqMatrix operator+(sqMatrix matrix);
    friend sqMatrix operator-(sqMatrix matrix1,  sqMatrix matrix2);
    operator int() const;
    sqMatrix &operator= (sqMatrix matrix);
    //sqMatrix operator++(int);
    //sqMatrix &operator++();
    //sqMatrix operator--(int);
    //sqMatrix &operator--();
};

#endif // SQMATRIX_H
