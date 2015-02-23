#ifndef PDFGENERATOR_H
#define PDFGENERATOR_H
#include<QtGlobal>

#ifdef Q_OS_WIN32
// standard library includes
#include <QStandardPaths>
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

static const QString docDir = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0) + "/";


class PdfGenerator
{
public:
    PdfGenerator(QString outFile = docDir + "out.PDF");
    ~PdfGenerator();

    void setFixingFlange(QString text);
    void setWidthInternal(QString text);
    bool finishAndWrite();


private:
    PDFWriter pdfWriter;
    EStatusCode status;

    PageContentContext* contentContext{nullptr};
    PDFPage* page{nullptr};
    PDFUsedFont* arialTTF{nullptr};

    bool createContextFromPdf();
};

#endif // Q_OS_WIN32
#endif // PDFGENERATOR_H
