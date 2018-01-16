#ifndef VALUEFILE_H
#define VALUEFILE_H
#include <fstream>
#include <QString>

#include "fileinterfaсe.h"
using namespace std;

class ValueFile : public FileInterface
{
     QString filename;
     unsigned count;
     fstream *dataF;
public:
    ValueFile();
    ValueFile(QString filename);
    double insertI(Item* item) override;
    void* getI() override;
    void deleteI(double key) override;
    void printAll() override;

    ~ValueFile();
};

#endif // VALUEFILE_H
