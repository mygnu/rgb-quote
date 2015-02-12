#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScroller>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings(QSettings::IniFormat, QSettings::UserScope, "MyGNU", "RGB-Quote")
{
    ui->setupUi(this);
    createMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus()
{
    editPrefAct =  new QAction(QIcon(), tr("&Preferences"), this);
    connect(editPrefAct, SIGNAL(triggered()), this, SLOT(onPrefClicked()));

    editMenu = ui->mainMenuBar->addMenu(tr("&Edit"));
    editMenu->addAction(editPrefAct);

    for(auto item : comboItems)
        ui->comboBox->addItem(item);

        connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(selectionMade(int)));
}

void MainWindow::selectionMade(const int itemNumber)
{
    qDebug() << "works" << itemNumber;
    if(itemNumber == 1)
    {
        cableCover1 = new CableCover(this);
       
        QScroller::grabGesture(ui->scrollArea, QScroller::TouchGesture);
         ui->scrollArea->setWidget(cableCover1);
        ui->Item_label->setText(cableCover1->name);
        connect(ui->pushButtonCalculate, SIGNAL(clicked()),
                cableCover1, SLOT(calculate()));
    }
}

void MainWindow::onPrefClicked()
{
    pref = new PrefDialog(settings, this);
    pref->setAttribute(Qt::WA_DeleteOnClose);
    pref->show();
}