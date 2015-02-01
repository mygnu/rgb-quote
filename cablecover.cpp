#include "cablecover.h"
#include "ui_cablecover.h"

CableCover::CableCover(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CableCover)
{
    ui->setupUi(this);
}

CableCover::~CableCover()
{
    delete ui;
}
