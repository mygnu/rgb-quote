#include "cablecover.h"
#include "ui_cablecover.h"
#include <QDebug>
#include <QScroller>

CableCover::CableCover(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CableCover)
{
    ui->setupUi(this);
    setupMenus();
    connectSignals();
    ui->fixingFlangeLineEdit->setValidator(new QDoubleValidator(0, 1000, 2, this));
    QScroller::grabGesture(this, QScroller::TouchGesture);
}

CableCover::~CableCover()
{
    delete ui;
}

void CableCover::setupMenus()
{
    double price = 10.0;

    for(auto item : designItems)
        ui->designComboBox->addItem(item, QVariant(price + 5));
    qDebug() << ui->designComboBox->currentData().toDouble();
}

double CableCover::designVal()
{

    return 0.0;
}

void CableCover::setValues(Values *val)
{
    this->values = val;
}

void CableCover::connectSignals()
{

}

void CableCover::calculate()
{
        ui->lableResult->setText(ui->fixingFlangeLineEdit->text());
}
