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

private:
    Ui::CableCover *ui;

};

#endif // CABLECOVER_H
