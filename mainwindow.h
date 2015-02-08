#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>

#include "prefdialog.h"
#include "cablecover.h"

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
    void selectionMade(const int itemNumber);
private:
    Ui::MainWindow *ui;
    QAction *editPrefAct{nullptr};
    QMenu *editMenu{nullptr};
    CableCover *cableCover1{nullptr};

    QSettings settings;
    void createMenus();
    PrefDialog *pref = nullptr;
    const QVector<QString> comboItems{"None Selected", "Cable Cover", "Item Two"};
};

#endif // MAINWINDOW_H
