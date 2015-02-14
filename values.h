#ifndef VALUES_H
#define VALUES_H

#include <QSettings>

class Values
{
public:
    Values();
    ~Values();

    QSettings settings;
    double openEnds;
    double oneEndClosed;
    double bothEndsClosed;

    double noFlanges;

    double thick0_6mmKG;
    double thick1_6mmKG;
    double thick3_0mmKG;

    double galvanisingPKG;
    double sprayPanitPMS;
    double powderCotePMS;

    double profitMargin;

    double priceSheet0_6mm;
    double priceSheet1_6mm;
    double priceSheet3_0mm;


private:


};

#endif // VALUES_H
