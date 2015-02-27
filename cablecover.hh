#ifndef CABLECOVER_H
#define CABLECOVER_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QLineEdit>
#include "ccvalues.hh"
#include "result.h"

namespace Ui {
class CableCover;
}

class CableCover : public QWidget
{
    Q_OBJECT

public:
    explicit CableCover(QWidget *parent = 0);
    ~CableCover();
    Result getResult() const {return res;}
    void setValues(const CCValues *values);
    Result calculate();

private:
    Ui::CableCover *ui;
    QVector<QString> materialItems = QVector<QString>{"Galvabond", "Zink Anneal", "Laser Plate", "Stainless Steel"};
    QVector<QString> thicknessItems = QVector<QString>{"0.6 MM", "1.6 MM", "3.0 MM"};

    QVector<QString> designItems = QVector<QString>{"Open Ends", "One End Closed", "Both Ends Closed"};
    QVector<QString> fixingholeItems = QVector<QString>{"Yes", "No"};
    QVector<QString> finishesItems = QVector<QString>{"None", "Galvanising", "Powder Cote", "Spray Paint"};

    QLineEdit *customThickness;

    Result res;
    const CCValues  *val;
    void setupMenus();
};



#endif // CABLECOVER_H
