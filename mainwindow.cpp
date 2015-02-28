#include <QDebug>

#include <QScroller>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createMenusConnection();
    values.load();
    if(values.getOpenAtStartup())
        onPrefClicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenusConnection()
{
    editPrefAct =  new QAction(QIcon(), tr("&Preferences"), this);
    connect(editPrefAct, SIGNAL(triggered()), this, SLOT(onPrefClicked()));

    editMenu = ui->mainMenuBar->addMenu(tr("&Edit"));
    editMenu->addAction(editPrefAct);

    for(auto item : comboItems)
        ui->comboBox->addItem(item);

    selectionMade(ui->comboBox->currentText());

    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(selectionMade(QString)));
    connect(ui->pushButtonPrintPdf, SIGNAL(clicked()),
            this, SLOT(onPdfPrintClicked()));
    connect(ui->pushButtonCalculate, SIGNAL(clicked()),
            this, SLOT(onCalculateClicked()));
}

void MainWindow::selectionMade(const QString &current)
{
    if(current == comboItems.at(0)) // if it is cable cover
    {
        ccWidget = ccWidget == nullptr
                ? new CableCover(this) : ccWidget;
        ui->Item_label->setText(comboItems.at(0));

        ccWidget->setValues(&values);
        ui->scrollArea->setWidget(ccWidget);
        QScroller::grabGesture(ui->scrollArea, QScroller::TouchGesture);
    }

    else
    {
        if(ccWidget != nullptr)
        {
            delete ccWidget;
            ccWidget = nullptr;
        }
    }
}

void MainWindow::onCalculateClicked()
{
    if(ui->comboBox->currentText() == comboItems.at(0))
    {
        ccWidget->calculate();
        ui->pushButtonPrintPdf->setEnabled(true);
    }
    else if(ui->comboBox->currentText() == comboItems.at(1))
    {
        QMessageBox msgBox;
        msgBox.setText("Please select an Item before you can calculate");
        msgBox.exec();
        ui->pushButtonPrintPdf->setEnabled(false);
    }
}

void MainWindow::onPdfPrintClicked()
{
    if(ccWidget != nullptr)
    {
        ccWidget->createPdf(ui->nameLE->text(), ui->phoneLE->text(),
                            ui->companyLE->text(), ui->emailLE->text());
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Please Calculate an Item before you can printpdf");
        msgBox.exec();
        ui->pushButtonPrintPdf->setEnabled(false);
    }

}

void MainWindow::onPrefClicked()
{
    pref = new CCPrefDialog(values, this);
    pref->setAttribute(Qt::WA_DeleteOnClose);
    pref->show();
}
