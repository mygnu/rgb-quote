/*
* Copyright © 2015 Mygnu <me@mygnu.net>
*
*
*
* This file is part of rgb-quote.
*
* rgb-quote is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Final Term is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with rgb-quote. If not, see <http://www.gnu.org/licenses/>.
*/

#include "pdfgenerator.hh"
#include <QMessageBox>
#ifdef Q_OS_WIN32


PdfGenerator::PdfGenerator(const QString &File):
    outFile(File.toStdString())
{}

bool PdfGenerator::start()
{
    if(!outFile.empty())
        status = pdfWriter.StartPDF(outFile,ePDFVersion13);

    if(status == eSuccess)
        return true;

    QMessageBox msgBox;
    msgBox.setText("Unable to start the out file");
    msgBox.exec();
    return false;
  }

PdfGenerator::~PdfGenerator() {}


bool PdfGenerator::createContextFromPdf(const QString &oldPdfFile)
{
    // creating XObjects for all pages of XObjectContent.pdf (2 pages)

    EStatusCodeAndObjectIDTypeList result = pdfWriter.CreateFormXObjectsFromPDF(oldPdfFile.toStdString(),
                                                                                    PDFPageRange(),ePDFPageBoxMediaBox);

    if(result.first != eSuccess)
    {
        status = eFailure;
        QMessageBox msgBox;
        msgBox.setText("Failed to open template pdf file");
        msgBox.exec();
//        qDebug() << "";
        return false;
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

    arialTTF = pdfWriter.GetFontForFile(fontPath.toStdString());
    if(!arialTTF)
    {
        status = eFailure;
        QMessageBox msgBox;
        msgBox.setText("Can't load arial font for pdf creation");
        msgBox.exec();
        delete page;
        return false;
    }
    contentContext->k(0,0,0,1); // set color black

    contentContext->BT();
    contentContext->Tf(arialTTF,1);
    return true;
}

bool PdfGenerator::putText(const QString &text, int xAxis, int yAxis)
{
    if(status != eFailure)
    {
        contentContext->Tm(8,0,0,10,xAxis,yAxis);
        contentContext->Tj(text.toStdString());
        return true;
    }
    return false;
}

bool PdfGenerator::finishAndWrite()
{
    if(status == eFailure)
        return false;

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
        QMessageBox msgBox;
        msgBox.setText("Succeeded in creating PDF file");
        msgBox.exec();
        return true;
    }
    QMessageBox msgBox;
    msgBox.setText("Failed in creating PDF file");
    msgBox.exec();
    return false;
}


#endif // Q_OS_WIN32
