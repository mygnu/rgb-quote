#include <QDebug>
#include <QScroller>
#include "cablecover.h"
#include "ui_cablecover.h"

CableCover::CableCover(QWidget *parent) :
    QWidget(parent),
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
    for(auto item : flangesItems)
        ui->flangesComboBox->addItem(item);
    for(auto item : materialItems)
        ui->materialComboBox->addItem(item);
    for(auto item : thicknessItems)
        ui->thicknessComboBox->addItem(item);
    for(auto item : fixingholeItems)
        ui->fixingHolesComboBox->addItem(item);


    qDebug() << ui->designComboBox->currentData().toDouble();
}


void CableCover::connectSignals()
{

}

void CableCover::calculate()
{
    double labourCost;
    if(ui->designComboBox->currentText() == "Open Ends")
        labourCost = values->openEnds;
    else if(ui->designComboBox->currentText() == "One End Closed")
        labourCost = values->oneEndClosed;
    else if(ui->designComboBox->currentText() == "Both Ends Closed")
        labourCost = values->bothEndsClosed;
    qDebug() << labourCost;

    //double density = values->weight / (1000 * 1000 * 3);
}
