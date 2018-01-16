#ifndef ADT_SPAREINDEX_H
#define ADT_SPAREINDEX_H
#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <fstream>

#include "item.h"
#include "valuefile.h"
#include "indexfile.h"

using namespace std;

class ADT_SpareIndex
{
public:
    ADT_SpareIndex();
    double insertI(Item *item);

    streampos searchI(double key) const;
    void deleteI(double key);
    ~ADT_SpareIndex();
private:

};

#endif // ADT_SPAREINDEX_H
