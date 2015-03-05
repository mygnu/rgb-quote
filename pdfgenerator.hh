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
