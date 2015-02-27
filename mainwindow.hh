#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QString>
#include <QDir>

#include "ccprefdialog.hh"
#include "cablecover.hh"
#include "pdfgenerator.hh"
#include "result.h"

namespace Ui {
class MainWindow;
}
static const QString pdfPath = QDir::currentPath() + "/TemplateCableCover.pdf";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onPrefClicked();
    void selectionMade(const QString &current);
    void onCreatePdfClicked();
    void calculate();
private:
    Result res;
    CCValues values;
    Ui::MainWindow *ui;
    QAction *editPrefAct{nullptr};
    QMenu *editMenu{nullptr};
    CableCover *cableCover1{nullptr};

    void createMenus();
    CCPrefDialog *pref = nullptr;
    const QVector<QString> comboItems = QVector<QString> {"Cable Cover", "Item Two"};
    void createPdfCableCover(const QString &filename, const Result &res);
};

#endif // MAINWINDOW_H
