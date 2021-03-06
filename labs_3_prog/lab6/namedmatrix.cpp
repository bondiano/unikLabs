#include "namedmatrix.h"

namedMatrix::namedMatrix(unsigned int order, float **value, char* name): sqMatrix(order, value)
{
    if(strlen(name) < 1) {
        throw std::runtime_error("Name must contain at least 1 symbol");
    }

    this->name = new char[256];
    strcpy(this->name, name);
}

namedMatrix::~namedMatrix()
{
    if(!strcmp(name, "Default") && !strcmp(name, "Copied")) {
        delete name;
    }
}

void namedMatrix::print() const
{
    std::cout << "Name: " << name << std::endl;
    sqMatrix::print();
}
