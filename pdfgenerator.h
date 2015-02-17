#ifndef PDFGENERATOR_H
#define PDFGENERATOR_H
#include<QtGlobal>

#ifdef Q_OS_WIN32
// standard library includes
#include <iostream>
#include <string>
using namespace std;

// end standard library includes
// pdfwriter library includes
#include "PDFWriter.h"
#include "PDFPage.h"
#include "PageContentContext.h"
#include "PDFFormXObject.h"
#include "ResourcesDictionary.h"
// end pdfwriter library includes

using namespace PDFHummus;
static const string scBasePath = "C:\\Users\\mygnu\\Apps\\PDFWriterCMake3_2\\TestMaterials\\images\\";
static const string scSystemFontsPath = "C:\\Windows\\Fonts\\";



class PdfGenerator
{
public:
    PdfGenerator();
    ~PdfGenerator();
};

#endif // Q_OS_WIN32
#endif // PDFGENERATOR_H
