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

#include <QDebug>
#include <QScroller>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QString>

#include "cablecover.hh"
#include "ui_cablecover.h"
#include "../pdfgenerator.hh"

CableCover::CableCover(QWidget *parent, CCValues *ccvals) :
    QWidget(parent),
    val(ccvals),
    ui(new Ui::CableCover)
{
    ui->setupUi(this);
    setupMenus();
    QScroller::grabGesture(this, QScroller::TouchGesture);
}

CableCover::~CableCover()
{
    delete ui;
}

void CableCover::setValues(const CCValues *values)
{
    if(values != nullptr && val == nullptr)
        val = values;
}

void CableCover::setupMenus()
{
    for(auto item : designItems)
        ui->designComboBox->addItem(item);
    for(auto item : finishesItems)
        ui->finishComboBox->addItem(item);
    for(auto item : materialItems)
        ui->materialComboBox->addItem(item);
    for(auto item : thicknessItems)
        ui->thicknessComboBox->addItem(item);
    for(auto item : fixingholeItems)
        ui->fixingHolesComboBox->addItem(item);
}

void CableCover::calculate()
{

    if(ui->designComboBox->currentText() == designItems.at(0))
        labourCost = val->getOpenEnds();
    else if(ui->designComboBox->currentText() == designItems.at(1))
        labourCost = val->getOneEndClosed();
    else if(ui->designComboBox->currentText() == designItems.at(2))
        labourCost = val->getBothEndsClosed();
    // if flanges are not required remove $5 from the labour cost
    if(ui->fixingFlangeSB->value() <= 0)
        labourCost -= 5;
    //TODO create variable for labour reduction

// Area = (internal width + (2*depth) + (2*flanges) ) * Length
    area = (ui->widthSB->value() + (ui->DepthSB->value() * 2)
                   + (ui->fixingFlangeSB->value() * 2)) * ui->lengthSB->value();

//    IF Area > 2400 ,  then
//    labour cost = labour cost + labour cost * increase / 100             (default increase is 50)

    if(area > 2400)
    {
        labourCost += (labourCost * 50 / 100); // variable for labour increase if area is
                                               // is greater than 2400mm
    }


    // select material here


    if(ui->materialComboBox->currentText() == materialItems.at(0)) // galvabond
    {
        if(ui->thicknessComboBox->currentText() == thicknessItems.at(0)) // 0.6
        {
            materialCost = val->getGalvbond0_6mmPrice() / 1000000 * area;
            weight = (area /1000000) * val->getGalvbond0_6KGPM() * 1000; // result is calculated by gm/mm3
        }
        else if(ui->thicknessComboBox->currentText() == thicknessItems.at(1)) //1.6
        {
            materialCost = val->getGalvbond1_6mmPrice() / 1000000 * area;
            weight = (area /1000000) * val->getGalvbond1_6KGPM() * 1000;
        }
        else if(ui->thicknessComboBox->currentText() == thicknessItems.at(2)) //3.0
        {
            materialCost = val->getGalvbond3_0mmPrice() / 1000000 * area;
            weight = (area /1000000) * val->getGalvbond3_0KGPM() * 1000;
        }
    }



    if(ui->finishComboBox->currentText() == finishesItems.at(1))
    {
        finishingCost = weight/1000 * val->getGalvanisingPKG();

        finishingCost = finishingCost < val->getGalvanisingMin()
                ? val->getGalvanisingMin() : finishingCost;
    }
    else if(ui->finishComboBox->currentText() == finishesItems.at(2))
    {
        finishingCost = area /1000000 * val->getPowderCotePMS();

        finishingCost = finishingCost < val->getGalvanisingMin()
                ? val->getGalvanisingMin() : finishingCost;
    }
    else if(ui->finishComboBox->currentText() == finishesItems.at(3))
    {
        finishingCost = area /1000000 * val->getSprayPaintPMS();

        finishingCost = finishingCost < val->getSprayPaintMin()
                ? val->getSprayPaintMin() : finishingCost;
    }
    profitMargin = val->getProfitMargin();

}

void CableCover::createPdf(const QString &name, const QString &phone,
                           const QString &company, const QString &email)
{
#ifdef Q_OS_WIN32
    QString filename = QFileDialog::getSaveFileName(this, tr("Save PDF File"),"untitled.pdf",
                                                    tr("PDF Files (*.pdf *.PDF)"));
    if(filename.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Please Select a product befre you can print a pdf");
        msgBox.exec();
        return;
    }
    else
    {
        PdfGenerator pdfgen(filename);
        if(!pdfgen.start())
            return;

        QString oldfilePath(pdfPath); // pdfPath is a const in the header

        QFile file(pdfPath);
        if(!file.exists()) // check if the input flie exist
        {
            oldfilePath = QFileDialog::getOpenFileName(0, tr("Open TEMPLATE PDF File"),"TemplateCableCover.pdf",
                                                       tr("PDF Files (*.pdf *.PDF)"));
        }
        if(pdfgen.createContextFromPdf(oldfilePath))
        {
            pdfgen.putText(getDate(), 490, 700);
            pdfgen.putText(name, 130, 115);
            pdfgen.putText(company, 130, 135);
            // do all the writing in the pdf file
            pdfgen.putText(QString::number(getFinalPrice()), 490, 500);
            //    pdfgen.setFixingFlange("22 mm");
            //    pdfgen.setWidthInternal("12 mm");
            pdfgen.finishAndWrite();
        }
    }


#endif  //Q_OS_WIN32

#ifdef Q_OS_LINUX
   QMessageBox msgBox;
    msgBox.setText("This only works in Windows for now");
    msgBox.exec();
#endif
}
