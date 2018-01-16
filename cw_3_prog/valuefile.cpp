#include "valuefile.h"

ValueFile::ValueFile()
{

}

ValueFile::ValueFile(QString filename): filename(filename)
{
    dataF->open(filename.toStdString(), ios::in | ios::out | ios::binary | ios::ate);
}

double ValueFile::insertI(Item *item)
{

}

void *ValueFile::getI()
{

}

void ValueFile::deleteI(double key)
{

}

void ValueFile::printAll()
{

}

ValueFile::~ValueFile()
{

}
