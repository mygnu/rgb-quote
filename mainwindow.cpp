/*
* Copyright © 2015 Mygnu <me@mygnu.net>
*
*
*
* This file is part of rgb-quote.
*
* rgb-quote is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Final Term is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with rgb-quote. If not, see <http://www.gnu.org/licenses/>.
*/

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
    ui->setupUi(this); // setup the user interface from .ui file
    createMenusConnection();
    ccValues.load();

    if(ccValues.getOpenAtStartup())
        onPrefClicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief MainWindow::createMenusConnection
 * creates QActions for edit menu
 * connects the signals for the combobox selection to be handeled
 */
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
/**
 * @brief MainWindow::selectionMade
 * chages the main widget according to the selection text
 *
 * @param current is the text from the combobox
 *
 */
void MainWindow::selectionMade(const QString &current)
{
    if(current == comboItems.at(0)) // if it is cable cover
    {
        // if ccWidget is null create new otherwise asignt the
        // same value
        ccWidget = ccWidget == nullptr
                ? new CableCover(this, &ccValues) : ccWidget;

        ui->Item_label->setText(comboItems.at(0));
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
    pref = new CCPrefs(this, &ccValues);
    pref->setAttribute(Qt::WA_DeleteOnClose);
    pref->show();
}
