#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QString>

#include "prefdialog.h"
#include "cablecover.h"
#include "pdfgenerator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onPrefClicked();
    void selectionMade(const QString &current);
    void grabSettings();

    void onCreatePdfClicked();
private:
    Values values;
    Ui::MainWindow *ui;
    QAction *editPrefAct{nullptr};
    QMenu *editMenu{nullptr};
    CableCover *cableCover1{nullptr};

    void createMenus();
    PrefDialog *pref = nullptr;
    const QVector<QString> comboItems = QVector<QString> {"None Selected", "Cable Cover", "Item Two"};
    void createPdfCableCover(const QString &filename);
};

#endif // MAINWINDOW_H
