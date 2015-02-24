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

void CableCover::setValues(const Values *val)
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
    if(ui->designComboBox->currentText() == "Open Ends")
        labourCost = values->getOpenEnds();
    else if(ui->designComboBox->currentText() == "One End Closed")
        labourCost = values->getOneEndClosed();
    else if(ui->designComboBox->currentText() == "Both Ends Closed")
        labourCost = values->getBothEndsClosed();
    // if flanges are not required remove $5 from the labour cost
    if(ui->fixingFlangeSB->value() <= 0)
        labourCost -= 5;
// Area = (internal width + (2*depth) + (2*flanges) ) * Length
    double area = (ui->widthSB->value() + (ui->DepthSB->value() * 2)
                   + (ui->fixingFlangeSB->value() * 2)) * ui->lengthSB->value();

//    IF Area > 2400 ,  then
//    labour cost = labour cost + labour cost * increase / 100             (default increase is 50)

    if(area > 2400)
    {
        labourCost += labourCost * 50 / 100;
    }
    double thickness;
    if(ui->thicknessComboBox->currentText() == "0.6 MM")
        thickness = 0.6;
    else if(ui->thicknessComboBox->currentText() == "1.6 MM")
        thickness = 1.6;
    else
        thickness = 3.00;

    double density = 0.00761333; // gm/mm cube

    double weight = area * thickness * density; // grams

//    IF finishing chosen = Galvanising Then
//        Finishting_cost = weight *(Galvanise finishing)
//        IF Finishing_cost < 2.0
//            Finishing_cost == 2.0
    double finishingCost = 0;
    if(ui->finishComboBox->currentText() == "Galvanising")
    {
        finishingCost = weight * values->getGalvanisingPKG() * 1000;
    }
    else if(ui->finishComboBox->currentText() == "Power Cote")
    {
        finishingCost = area * values->getPowderCotePMS() * 1000;
    }
    else if(ui->finishComboBox->currentText() == "Spray Paint")
    {
        finishingCost = area * values->getSprayPaintPMS() * 1000;
    }
    qDebug() << labourCost << "area:" << area << "weight" << weight
             << "\nfinishing cost" << finishingCost;

    //double density = values->weight / (1000 * 1000 * 3);
}
