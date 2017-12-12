#include "namedmatrix.h"

namedMatrix::namedMatrix(): sqMatrix(), name("Default")
{
}

namedMatrix::namedMatrix(unsigned int order, float **value, char* name): sqMatrix(order, value)
{
    this->name = new char[256];
    strcpy(this->name, name);
}

namedMatrix::namedMatrix(const sqMatrix &matrix): sqMatrix(matrix), name("Copied")
{
}

namedMatrix::~namedMatrix()
{
    if(!strcmp(name, "Default") && !strcmp(name, "Copied")){
        delete name;
    }
}

void namedMatrix::print() const
{
    sqMatrix::print();
    std::cout << "Name: " << name << std::endl;
}
