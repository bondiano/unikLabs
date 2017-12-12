#include "list.h"

void List::pushBack(sqMatrix &matrix)
{
   Element *el = new Element(matrix);
   if(!first) {
       first = el;
       last = el;
       current = el;
       return;
   }

   last->next = el;
   el->perv = last;
   last = el;
}

void List::popForward()
{
    if(!first) {
        return;
    }

    if(current == first) {
        current = current->next;
    }

    first = first->next;
    delete first->perv;
    first->perv = nullptr;
}

void List::next()
{
    if(current == last) {
        current = first;
        return;
    }
    current = current->next;
}

bool List::isExist(sqMatrix& matrix)
{
    Element* tempEl = first;
    while (tempEl != nullptr) {
        if(*(tempEl->el) == matrix){
            return true;
        }
        tempEl = tempEl->next;
    }
    return false;
}

sqMatrix *List::getCurrent()
{
    return current->el;
}

void List::printAll()
{
    Element* tempEl = current;
    while (tempEl != nullptr) {
        tempEl->el->print();
        tempEl = tempEl->next;
    }
    tempEl = first;
    while (tempEl != current) {
        tempEl->el->print();
        tempEl = tempEl->next;
    }
}

List::~List()
{
    Element* tempEl = first;
    while (tempEl != nullptr) {
        Element *temp = tempEl;
        tempEl = tempEl->next;
        delete temp;
    }
}

List::Element::Element(sqMatrix &matrix): next(nullptr), perv(nullptr)
{
    sqMatrix* tempMatrix = nullptr;

    if(typeid(matrix) == typeid(sqMatrix)) {
        tempMatrix = new sqMatrix(matrix);
    }

    if(typeid(matrix) == typeid(sqMatrixDet)) {
        tempMatrix = new sqMatrixDet(matrix);
    }

    if(typeid(matrix) == typeid(namedMatrix)) {
        tempMatrix = new namedMatrix(matrix);
    }

    el = tempMatrix;
}

List::Element::~Element()
{
    if(el){
        delete el;
    }
}
