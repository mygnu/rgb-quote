#ifndef PDFGENERATOR_H
#define PDFGENERATOR_H
#include<QtGlobal>

#ifdef Q_OS_WIN32

#include "PDFWriter.h"


class PdfGenerator
{
public:
    PdfGenerator();
    ~PdfGenerator();
};

#endif // Q_OS_WIN32
#endif // PDFGENERATOR_H
