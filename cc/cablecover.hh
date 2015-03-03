#ifndef CABLECOVER_H
#define CABLECOVER_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QLineEdit>
#include <QDir>
#include <QDate>

#include "values.hh"

namespace Ui {
class CableCover;
}

static const QString pdfPath = QDir::currentPath() + "/TemplateCableCover.pdf";
class CableCover : public QWidget
{
    Q_OBJECT

public:
    explicit CableCover(QWidget *parent = 0);
    ~CableCover();
    void setValues(const CCValues *values);
    void calculate();
    void createPdf(const QString &name, const QString &phone, const QString &company, const QString &email);

private:
    Ui::CableCover *ui;
    QVector<QString> materialItems = QVector<QString>{"Galvabond", "Zink Anneal", "Laser Plate", "Stainless Steel"};
    QVector<QString> thicknessItems = QVector<QString>{"0.6 MM", "1.6 MM", "3.0 MM"};

    QVector<QString> designItems = QVector<QString>{"Open Ends", "One End Closed", "Both Ends Closed"};
    QVector<QString> fixingholeItems = QVector<QString>{"Yes", "No"};
    QVector<QString> finishesItems = QVector<QString>{"None", "Galvanising", "Powder Cote", "Spray Paint"};

    QLineEdit *customThickness;
    const CCValues  *val;
    void setupMenus();
    void createPdfCableCover(const QString &filename);

    double labourCost{0};
    double area{0};
    double materialCost{0};
    double weight{0};
    double finishingCost{0};
    double profitMargin{0};
    double getTotalCost() const {return labourCost + materialCost + finishingCost;}
    double getFinalPrice() const {return getTotalCost() + (getTotalCost() * profitMargin / 100);}
    QString getDate() const { return QDate::currentDate().toString("dd MMMM yyyy");}
};



#endif // CABLECOVER_H
