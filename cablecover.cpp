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

    double thickness;
    if(ui->thicknessComboBox->currentText() == thicknessItems.at(0))
        thickness = 0.6;
    else if(ui->thicknessComboBox->currentText() == thicknessItems.at(1))
        thickness = 1.6;
    else
        thickness = 3.00;
    // select material here
    double materialCost{0};

    if(ui->materialComboBox->currentText() == materialItems.at(0))
    {

    }


    double density = 0.00761333; // gm/mm cube
    double weight = area * thickness * density; // grams

    // calculate material cost


//    IF finishing chosen = Galvanising Then
//        Finishting_cost = weight *(Galvanise finishing)
//        IF Finishing_cost < 2.0
//            Finishing_cost == 2.0
    double finishingCost = 0;
    if(ui->finishComboBox->currentText() == "Galvanising")
    {
        finishingCost = weight/1000 * values->getGalvanisingPKG();
    }
    else if(ui->finishComboBox->currentText() == "Powder Cote")
    {
        finishingCost = area /1000000 * values->getPowderCotePMS();
    }
    else if(ui->finishComboBox->currentText() == "Spray Paint")
    {
        finishingCost = area /1000000 * values->getSprayPaintPMS();
    }

    double totalCost = labourCost + materialCost + finishingCost;
    double finalPrice = totalCost + totalCost * values->getProfitMargin() / 100;


    qDebug() << labourCost << "area CM:" << area /100 << "weight" << weight
             << "\nfinishing cost" << finishingCost << "total cost" << totalCost << "final price" << finalPrice;

    //double density = values->weight / (1000 * 1000 * 3);
}
