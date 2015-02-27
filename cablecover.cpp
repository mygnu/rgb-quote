#include <QDebug>
#include <QScroller>
#include "cablecover.hh"
#include "ui_cablecover.h"

CableCover::CableCover(QWidget *parent) :
    QWidget(parent),
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

Result CableCover::calculate()
{
    res.labourCost;
    if(ui->designComboBox->currentText() == designItems.at(0))
        res.labourCost = val->getOpenEnds();
    else if(ui->designComboBox->currentText() == designItems.at(1))
        res.labourCost = val->getOneEndClosed();
    else if(ui->designComboBox->currentText() == designItems.at(2))
        res.labourCost = val->getBothEndsClosed();
    // if flanges are not required remove $5 from the labour cost
    if(ui->fixingFlangeSB->value() <= 0)
        res.labourCost -= 5;
    //TODO create variable for labour reduction

// Area = (internal width + (2*depth) + (2*flanges) ) * Length
    res.area = (ui->widthSB->value() + (ui->DepthSB->value() * 2)
                   + (ui->fixingFlangeSB->value() * 2)) * ui->lengthSB->value();

//    IF Area > 2400 ,  then
//    labour cost = labour cost + labour cost * increase / 100             (default increase is 50)

    if(res.area > 2400)
    {
        res.labourCost += (res.labourCost * 50 / 100); // variable for labour increase if area is
                                               // is greater than 2400mm
    }


    // select material here


    if(ui->materialComboBox->currentText() == materialItems.at(0)) // galvabond
    {
        if(ui->thicknessComboBox->currentText() == thicknessItems.at(0)) // 0.6
        {
            res.materialCost = val->getGalvbond0_6mmPrice() / 1000000 * res.area;
            res.weight = (res.area /1000000) * val->getGalvbond0_6KGPM() * 1000; // result is calculated by gm/mm3
        }
        else if(ui->thicknessComboBox->currentText() == thicknessItems.at(1)) //1.6
        {
            res.materialCost = val->getGalvbond1_6mmPrice() / 1000000 * res.area;
            res.weight = (res.area /1000000) * val->getGalvbond1_6KGPM() * 1000;
        }
        else if(ui->thicknessComboBox->currentText() == thicknessItems.at(2)) //3.0
        {
            res.materialCost = val->getGalvbond3_0mmPrice() / 1000000 * res.area;
            res.weight = (res.area /1000000) * val->getGalvbond3_0KGPM() * 1000;
        }
    }



    if(ui->finishComboBox->currentText() == finishesItems.at(1))
    {
        res.finishingCost = res.weight/1000 * val->getGalvanisingPKG();

        res.finishingCost = res.finishingCost < val->getGalvanisingMin()
                ? val->getGalvanisingMin() : res.finishingCost;
    }
    else if(ui->finishComboBox->currentText() == finishesItems.at(2))
    {
        res.finishingCost = res.area /1000000 * val->getPowderCotePMS();

        res.finishingCost = res.finishingCost < val->getGalvanisingMin()
                ? val->getGalvanisingMin() : res.finishingCost;
    }
    else if(ui->finishComboBox->currentText() == finishesItems.at(3))
    {
        res.finishingCost = res.area /1000000 * val->getSprayPaintPMS();

        res.finishingCost = res.finishingCost < val->getSprayPaintMin()
                ? val->getSprayPaintMin() : res.finishingCost;
    }
    res.profitMargin = val->getProfitMargin();

    res.complete(true);
    return res;
}
