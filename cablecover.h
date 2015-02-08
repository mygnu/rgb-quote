#ifndef CABLECOVER_H
#define CABLECOVER_H

#include <QWidget>
#include <QString>



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
private:
    Ui::CableCover *ui;
    const QVector<QString> designItems{"Open Ends", "One End Closed", "Both Ends Closed"};


    void setupMenus();
};

#endif // CABLECOVER_H
