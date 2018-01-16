#include "indexfile.h"

IndexFile::IndexFile(): filename("index.bin"), blockSize(10)
{

}

IndexFile::IndexFile(QString filename, unsigned size): filename(filename), blockSize(size)
{
    indexF->open(filename.toStdString(), ios::in | ios::out | ios::binary | ios::ate);
}


double IndexFile::insertI(Index *item)
{
    return 0;
}

double IndexFile::insertI(Item *item)
{

}

void* IndexFile::getI()
{

}

void IndexFile::deleteI(double key)
{
    return;
}

void IndexFile::printAll()
{
    return;
}

IndexFile::~IndexFile()
{

}
