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
    void grabSettings();

    void onCreatePdfClicked();
private:
    CCValues values;
    Ui::MainWindow *ui;
    QAction *editPrefAct{nullptr};
    QMenu *editMenu{nullptr};
    CableCover *cableCover1{nullptr};

    void createMenus();
    CCPrefDialog *pref = nullptr;
    const QVector<QString> comboItems = QVector<QString> {"Cable Cover", "Item Two"};
    void createPdfCableCover(const QString &filename);
};

#endif // MAINWINDOW_H
