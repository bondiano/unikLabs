#include "namedmatrix.h"

namedMatrix::namedMatrix(): sqMatrix()
{
    this->name = new char[10];
    strcpy(this->name, "Default");
}

namedMatrix::namedMatrix(unsigned int order, float **value, char* name): sqMatrix(order, value)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

namedMatrix::namedMatrix(const sqMatrix &matrix): sqMatrix(matrix)
{
    this->name = new char[7];
    strcpy(this->name, "Copied");
}

namedMatrix::~namedMatrix()
{
    if(name){
        delete name;
    }
}

void namedMatrix::print() const
{
    sqMatrix::print();
    std::cout << "Name: " << name << std::endl;
}
