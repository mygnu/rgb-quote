#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QString>
#include <QDir>

#include "ccprefdialog.hh"
#include "cablecover.hh"
#include "pdfgenerator.hh"

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
    void onCalculateClicked();
    void onPdfPrintClicked();
    void selectionMade(const QString &current);

private:
    CCValues values;
    Ui::MainWindow *ui;
    QAction *editPrefAct{nullptr};
    QMenu *editMenu{nullptr};
    CableCover *ccWidget{nullptr};

    void createMenusConnection();
    CCPrefDialog *pref = nullptr;
    const QVector<QString> comboItems = QVector<QString> {"Cable Cover", "Item Two"};

};

#endif // MAINWINDOW_H
