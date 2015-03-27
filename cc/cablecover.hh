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

#ifndef CABLECOVER_H
#define CABLECOVER_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QLineEdit>
#include <QDir>
#include <QDate>

#include "../values.hh"
#include "../virtualproduct.hh"

namespace Ui {
class CableCover;
}

/**
 * @brief pdfPath
 * Const path to tempelate pdf file, it will be shipped with the program,
 * but if this doesn't exist user will get a choice to select the template
 */
static const QString pdfPath = QDir::currentPath() + "/TemplateCableCover.pdf";

/**
 * @brief The CableCover class
 * the base class for displaying(as a widget), storing and calculating values
 * related to the product CableCover
 */
class CableCover : public QWidget, public VirtualProduct
{
    Q_OBJECT

public:
    explicit CableCover(QWidget *parent = nullptr, Values *ccvals = nullptr);
    ~CableCover();
    void setValues(const Values *values);
    void calculate();
    void createPdf(const QString &name, const QString &phone, const QString &company, const QString &email);

private:
    Ui::CableCover *ui;
    QVector<QString> materialItems = QVector<QString>{"Galvabond", "Zink Anneal", "Laser Plate", "Stainless Steel"};
    QVector<QString> thicknessItems = QVector<QString>{"0.6 MM", "1.6 MM", "3.0 MM"};

    QVector<QString> designItems = QVector<QString>{"Open Ends", "One End Closed", "Both Ends Closed"};
    QVector<QString> fixingholeItems = QVector<QString>{"Yes", "No"};
    QVector<QString> finishesItems = QVector<QString>{"None", "Galvanising", "Powder Cote", "Spray Paint"};

    QLineEdit *customThickness;
    const Values  *val;
    void setupMenus();
    void createPdfCableCover(const QString &filename);

    double labourCost{0};
    double area{0};
    double materialCost{0};
    double weight{0};
    double finishingCost{0};
    double profitMargin{0};
    double getTotalCost() const {return labourCost + materialCost + finishingCost;}
    double getFinalPrice() const {return getTotalCost() + (getTotalCost() * profitMargin / 100);}
    QString getDate() const { return QDate::currentDate().toString("dd MMMM yyyy");}
};



#endif // CABLECOVER_H
