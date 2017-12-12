#ifndef LIST_H
#define LIST_H
#include <sqmatrix.h>
#include <namedmatrix.h>
#include <sqmatrixdet.h>

class List
{
    class Element{
    public:
          sqMatrix *el;
          Element *next;
          Element *perv;

          Element(sqMatrix &matrix);
          ~Element();
    };

    Element *first;
    Element *last;
    Element *current;


public:
    List();
    void pushBack(sqMatrix &matrix);
    void popForward();
    void next();
    bool isExist(sqMatrix& matrix);
    sqMatrix* getCurrent();
    void printAll();
    ~List();
};

#endif // LIST_H
