
#include "pdfgenerator.h"
#include <QDebug>

#ifdef Q_OS_WIN32

PdfGenerator::PdfGenerator()
{
    string documents = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0).toStdString();

    PDFWriter pdfWriter;
    EStatusCode status;
    do
    {
        status = pdfWriter.StartPDF(documents + "/out.PDF",ePDFVersion13);
        if(status != eSuccess)
            break;
        // creating XObjects for all pages of XObjectContent.pdf (2 pages)
        EStatusCodeAndObjectIDTypeList result = pdfWriter.CreateFormXObjectsFromPDF(documents + "/CableCover.PDF",
                                                                                    PDFPageRange(),ePDFPageBoxMediaBox);
        if(result.first != eSuccess)
        {
            status = eFailure;
            break;
        }
        // determine page IDs
        ObjectIDTypeList::iterator it = result.second.begin();
        ObjectIDType firstPageID = *it;

        // create a page using both xobjects
        PDFPage* page = new PDFPage();
        page->SetMediaBox(PDFRectangle(0,0,595,842));
        PageContentContext* contentContext = pdfWriter.StartPageContentContext(page);

        // place the first page in the top left corner of the document
        contentContext->q();
        contentContext->cm(1,0,0,1,0,0);
        contentContext->Do(page->GetResourcesDictionary().AddFormXObjectMapping(firstPageID));
        contentContext->Q();

        // draw a rectangle around the page bounds
//        contentContext->G(0);
//        contentContext->w(1);
//        contentContext->re(0,421,297.5,421);
//        contentContext->S();

        status = pdfWriter.EndPageContentContext(contentContext);
        if(status != eSuccess)
            break;
        status = pdfWriter.WritePageAndRelease(page);
        if(status != eSuccess)
            break;

        status = pdfWriter.EndPDF();
        if(status != eSuccess)
            break;
    }while(false);


    if(eSuccess == status)
    cout<<"Succeeded in creating PDF file\n";
    else
    cout<<"Failed in creating PDF file\n";

}

PdfGenerator::~PdfGenerator()
{

}

#endif // Q_OS_WIN32
