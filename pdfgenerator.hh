#ifndef PDFGENERATOR_H
#define PDFGENERATOR_H
#include<QtGlobal>

#ifdef Q_OS_WIN32
// standard library includes
#include <QStandardPaths>
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
//static const string scBasePath = "C:\\Users\\mygnu\\Apps\\PDFWriterCMake3_2\\TestMaterials\\images\\";
//static const string scSystemFontsPath = "C:\\Windows\\Fonts\\";
static const QString fontPath = QStandardPaths::standardLocations(QStandardPaths::FontsLocation).at(0) + "/arial.ttf";

class PdfGenerator
{
public:
    PdfGenerator(const QString &File);
    bool start();
    ~PdfGenerator();
    bool createContextFromPdf(const QString &oldPdfFile);
    bool finishAndWrite();

    void setFixingFlange (const QString &text){ putText(text, 490, 410);}
    void setWidthInternal(const QString &text){ putText(text, 490, 390);}

    void putText(const QString &text, int xAxis, int yAxis);

private:
    std::string outFile;
    PDFWriter pdfWriter;
    EStatusCode status;

    PageContentContext* contentContext{nullptr};
    PDFPage* page{nullptr};
    PDFUsedFont* arialTTF{nullptr};

};

#endif // Q_OS_WIN32
#endif // PDFGENERATOR_H
