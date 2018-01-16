#ifndef INDEXFILE_H
#define INDEXFILE_H
#include <fstream>
#include <QString>
#include "fileinterfaсe.h"
using namespace std;

class IndexFile : public FileInterface
{
private:
    struct Index {
      double key = 0;
      streampos fPtr;
    };

    QString filename;
    fstream *indexF;

    unsigned blockSize;
    unsigned currentBlock;
    unsigned count;
public:
    IndexFile();
    IndexFile(QString filename, unsigned size);
    double insertI(Index* item);
    double insertI(Item* item) override;
    void* getI() override;
    void deleteI(double key) override;
    void printAll() override;
    ~IndexFile();
};

#endif // INDEXFILE_H
