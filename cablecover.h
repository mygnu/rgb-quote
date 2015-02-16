#ifndef CABLECOVER_H
#define CABLECOVER_H

#include <QWidget>
#include <QString>
#include <QVector>



namespace Ui {
class CableCover;
}

class CableCover : public QWidget
{
    Q_OBJECT

public:
    const QString name{"Cable Cover"};
    explicit CableCover(QWidget *parent = 0);
    ~CableCover();

    double designVal();
    double flasgesVal();

public slots:
    void calculate();

private:
    Ui::CableCover *ui;
    QVector<QString> designItems = QVector<QString>{"Open Ends", "One End Closed", "Both Ends Closed"};


    void setupMenus();
    void connectSignals();
};

#endif // CABLECOVER_H
