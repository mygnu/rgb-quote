#include <QDebug>

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QScroller>
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createMenus();
    values.load();
    if(values.getOpenAtStartup())
        onPrefClicked();
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
    connect(ui->pushButtonPrintPdf, SIGNAL(clicked()),
            this, SLOT(onCreatePdfClicked()));
}

void MainWindow::selectionMade(const QString &current)
{
    if(current == comboItems.at(1)) // if it is cable cover
    {
        cableCover1 = cableCover1 == nullptr ? new CableCover(this, comboItems.at(1)) : cableCover1;
        ui->Item_label->setText(comboItems.at(1));

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

void MainWindow::onCreatePdfClicked()
{
#ifdef Q_OS_WIN32
    if(ui->comboBox->currentText() == comboItems.at(1))
        {
            QString filename = QFileDialog::getSaveFileName(this, tr("Save PDF File"),"untitled.pdf",
                                                            tr("PDF Files (*.pdf *.PDF)"));
            if(!filename.isEmpty())
            {
                createPdfCableCover(filename);
            }
        }

    else
    {
        QMessageBox msgBox;
        msgBox.setText("Please Select a product befre you can print a pdf");
        msgBox.exec();
    }


#endif  //Q_OS_WIN32

#ifdef Q_OS_LINUX
   QMessageBox msgBox;
    msgBox.setText("This only works in Windows for now");
    msgBox.exec();
#endif
}

void MainWindow::createPdfCableCover(const QString &filename)
{
#ifdef Q_OS_WIN32
    PdfGenerator pdfgen(filename);

    QString oldfilePath(pdfPath);

    QFile file(pdfPath);
    if(!file.exists())
    {
        oldfilePath = QFileDialog::getOpenFileName(0, tr("Open TEMPLATE PDF File"),"TemplateCableCover.pdf",
                                                   tr("PDF Files (*.pdf *.PDF)"));
    }
    pdfgen.createContextFromPdf(oldfilePath);


    pdfgen.setFixingFlange("22 mm");
    pdfgen.setWidthInternal("12 mm");
#endif  //Q_OS_WIN32
}
