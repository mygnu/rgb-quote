
#include "pdfgenerator.h"
#include <QDebug>

#ifdef Q_OS_WIN32


PdfGenerator::PdfGenerator(QString outFile)
{

    status = pdfWriter.StartPDF(outFile.toStdString(),ePDFVersion13);
    createContextFromPdf();
    setFixingFlange("22 mm");
    setWidthInternal("12 mm");
    finishAndWrite();
}

PdfGenerator::~PdfGenerator()
{
    delete page;
    delete arialTTF;
    delete contentContext;
}

void PdfGenerator::setFixingFlange(QString text)
{
    contentContext->Tm(8,0,0,10,490,410);
    contentContext->Tj(text.toStdString());
}

void PdfGenerator::setWidthInternal(QString text)
{
    contentContext->Tm(8,0,0,10,490,390);
    contentContext->Tj(text.toStdString());
}

bool PdfGenerator::createContextFromPdf()
{
    // creating XObjects for all pages of XObjectContent.pdf (2 pages)
    EStatusCodeAndObjectIDTypeList result = pdfWriter.CreateFormXObjectsFromPDF(docDir.toStdString() + "CableCover.pdf",
                                                                                PDFPageRange(),ePDFPageBoxMediaBox);
    if(result.first != eSuccess)
    {
        status = eFailure;
        qDebug() << "failed";
    }
    // determine page IDs
    ObjectIDTypeList::iterator it = result.second.begin();
    ObjectIDType firstPageID = *it;

    // create a page using both xobjects
    page = new PDFPage();
    page->SetMediaBox(PDFRectangle(0,0,595,842));
    contentContext = pdfWriter.StartPageContentContext(page);
    // place the first page in the top left corner of the document
    contentContext->q();
    contentContext->cm(1,0,0,1,0,0);
    contentContext->Do(page->GetResourcesDictionary().AddFormXObjectMapping(firstPageID));
    contentContext->Q();

    arialTTF = pdfWriter.GetFontForFile("C:\\Windows\\fonts\\arial.ttf");

    contentContext->k(0,0,0,1); // set color black

    contentContext->BT();
    contentContext->Tf(arialTTF,1);
    return true;
}

bool PdfGenerator::finishAndWrite()
{
    contentContext->ET();
    status = pdfWriter.EndPageContentContext(contentContext);
    if(status != eSuccess)
        return false;
    status = pdfWriter.WritePageAndRelease(page);
    if(status != eSuccess)
        return false;

    status = pdfWriter.EndPDF();
    if(status != eSuccess)
        return false;



    if(eSuccess == status)
    {
        cout<<"Succeeded in creating PDF file\n";
        return true;
    }
    cout<<"Failed in creating PDF file\n";
    return false;
}

#endif // Q_OS_WIN32
