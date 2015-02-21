#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScroller>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createMenus();
    values.load();
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

        connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(selectionMade(QString)));
}

void MainWindow::selectionMade(const QString &current)
{
    if(current == "Cable Cover") // if it is cable cover
    {
        cableCover1 = cableCover1 == nullptr ? new CableCover(this) : cableCover1;
        ui->Item_label->setText(cableCover1->name);

        cableCover1->setValues(&values);
        connect(ui->pushButtonCalculate, SIGNAL(clicked()),
                cableCover1, SLOT(calculate()));

        ui->scrollArea->setWidget(cableCover1);
        QScroller::grabGesture(ui->scrollArea, QScroller::TouchGesture);
    }

    else
    {
        if(cableCover1 != nullptr)
        {
            delete cableCover1;
            cableCover1 = nullptr;
        }
    }
}

void MainWindow::grabSettings()
{

}


void MainWindow::onPrefClicked()
{
    pref = new PrefDialog(values, this);
    pref->setAttribute(Qt::WA_DeleteOnClose);
    pref->show();
}
