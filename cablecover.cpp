#include <QDebug>
#include <QScroller>
#include "cablecover.hh"
#include "ui_cablecover.h"

CableCover::CableCover(QWidget *parent, const QString &n) :
    QWidget(parent),
    name(n),
    ui(new Ui::CableCover)
{
    ui->setupUi(this);
    setupMenus();
    connectSignals();
    QScroller::grabGesture(this, QScroller::TouchGesture);
}

CableCover::~CableCover()
{
    delete ui;
}

double CableCover::getResult()
{
    return result;
}

void CableCover::setValues(const CCValues *val)
{
    values = val;
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


void CableCover::connectSignals()
{

}

void CableCover::calculate()
{
    double labourCost;
    if(ui->designComboBox->currentText() == designItems.at(0))
        labourCost = values->getOpenEnds();
    else if(ui->designComboBox->currentText() == designItems.at(1))
        labourCost = values->getOneEndClosed();
    else if(ui->designComboBox->currentText() == designItems.at(2))
        labourCost = values->getBothEndsClosed();
    // if flanges are not required remove $5 from the labour cost
    if(ui->fixingFlangeSB->value() <= 0)
        labourCost -= 5;
    //TODO create variable for labour reduction

// Area = (internal width + (2*depth) + (2*flanges) ) * Length
    double area = (ui->widthSB->value() + (ui->DepthSB->value() * 2)
                   + (ui->fixingFlangeSB->value() * 2)) * ui->lengthSB->value();

//    IF Area > 2400 ,  then
//    labour cost = labour cost + labour cost * increase / 100             (default increase is 50)

    if(area > 2400)
    {
        labourCost += (labourCost * 50 / 100); // variable for labour increase if area is
                                               // is greater than 2400mm
    }


    // select material here
    double materialCost;
    double weight; // grams

    if(ui->materialComboBox->currentText() == materialItems.at(0)) // galvabond
    {
        if(ui->thicknessComboBox->currentText() == thicknessItems.at(0)) // 0.6
        {
            materialCost = values->getGalvbond0_6mmPrice() / 1000000 * area;
            weight = (area /1000000) * values->getGalvbond0_6KGPM() * 1000; // result is calculated by gm/mm3
        }
        else if(ui->thicknessComboBox->currentText() == thicknessItems.at(1)) //1.6
        {
            materialCost = values->getGalvbond1_6mmPrice() / 1000000 * area;
            weight = (area /1000000) * values->getGalvbond1_6KGPM() * 1000;
        }
        else if(ui->thicknessComboBox->currentText() == thicknessItems.at(2)) //3.0
        {
            materialCost = values->getGalvbond3_0mmPrice() / 1000000 * area;
            weight = (area /1000000) * values->getGalvbond3_0KGPM() * 1000;
        }
    }


    double finishingCost = 0;
    if(ui->finishComboBox->currentText() == finishesItems.at(1))
    {
        finishingCost = weight/1000 * values->getGalvanisingPKG();

        finishingCost = finishingCost < values->getGalvanisingMin()
                ? values->getGalvanisingMin() : finishingCost;
    }
    else if(ui->finishComboBox->currentText() == finishesItems.at(2))
    {
        finishingCost = area /1000000 * values->getPowderCotePMS();

        finishingCost = finishingCost < values->getGalvanisingMin()
                ? values->getGalvanisingMin() : finishingCost;
    }
    else if(ui->finishComboBox->currentText() == finishesItems.at(3))
    {
        finishingCost = area /1000000 * values->getSprayPaintPMS();

        finishingCost = finishingCost < values->getSprayPaintMin()
                ? values->getSprayPaintMin() : finishingCost;
    }

    double totalCost = labourCost + materialCost + finishingCost;
    double finalPrice = totalCost + totalCost * values->getProfitMargin() / 100;


    qDebug() << labourCost << "area CM:" << area /100 << "weight" << weight
             << "\nfinishing cost" << finishingCost << "total cost" << totalCost << "final price" << finalPrice;

    //double density = values->weight / (1000 * 1000 * 3);
}
