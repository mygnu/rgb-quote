
#include "pdfgenerator.h"
#include <QDebug>

#ifdef Q_OS_WIN32

PdfGenerator::PdfGenerator()
{
    PDFWriter pdfWriter;
    EStatusCode status;
    do
    {
    status = pdfWriter.StartPDF("C:\\Users\\mygnu\\Documents\\GitHub\\rgb-quote\\build\\RGB-Quote-Desktop_Qt_5_4_0_MSVC2013_64bit-Debug\\debug\\BasicImageAndText.pdf",ePDFVersion13);
    if(status != eSuccess)
    break;
    // Create a new page
    PDFPage* pdfPage = new PDFPage();
    pdfPage->SetMediaBox(PDFRectangle(0,0,595,842));
    // Create an image object from image
    PDFFormXObject* image = pdfWriter.CreateFormXObjectFromJPGFile("C:\\Users\\mygnu\\Documents\\GitHub\\rgb-quote\\build\\RGB-Quote-Desktop_Qt_5_4_0_MSVC2013_64bit-Debug\\debug\\otherStage.JPG");
    if(!image)
    {
        status = eFailure;

        break;
    }
    // Create a content context for the page
    PageContentContext* pageContentContext = pdfWriter.StartPageContentContext(pdfPage);
    // Place the image in the center of the page
    pageContentContext->q();
    pageContentContext->cm(0.4,0,0,0.4,57.5,241);
    pageContentContext->Do(pdfPage->GetResourcesDictionary().AddFormXObjectMapping(image->GetObjectID()));
    pageContentContext->Q();
    // Image object can be deleted right after i was used
    delete image;
    // Create a title text over the image
   PDFUsedFont* arialTTF = pdfWriter.GetFontForFile("C:\\Users\\mygnu\\Documents\\GitHub\\rgb-quote\\build\\RGB-Quote-Desktop_Qt_5_4_0_MSVC2013_64bit-Debug\\debug\\arial.ttf");
    if(!arialTTF)
    {
    status = eFailure;
    qDebug() << "cant' open this";
    break;
    }
    pageContentContext->BT();
    pageContentContext->k(0,0,0,1);
    pageContentContext->Tf(arialTTF,20);
    pageContentContext->Tm(1,0,0,1,90,610);
    pageContentContext->Tj("San Antonio Pass, Cordillera Huayhuash, Peru");
    pageContentContext->ET();
    // End content context, and write the page
    status = pdfWriter.EndPageContentContext(pageContentContext);
    if(status != eSuccess)
    break;
    status = pdfWriter.WritePageAndRelease(pdfPage);
    if(status != eSuccess)
    break;
    status = pdfWriter.EndPDF();
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
