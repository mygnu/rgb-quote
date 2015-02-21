#ifndef VALUES_H
#define VALUES_H

#include <QSettings>

class Values
{

public:
    Values();
    ~Values();

    QSettings settings;
    double openEnds{1};
    double oneEndClosed{1};
    double bothEndsClosed{1};

    double flangesCharge{1};

    double thick0_6mmKG{1};
    double thick1_6mmKG{1};
    double thick3_0mmKG{1};

    double galvanisingPKG{1};
    double sprayPanitPMS{1};
    double powderCotePMS{1};

    double profitMargin{1};

    double priceSheet0_6mm{1};
    double priceSheet1_6mm{1};
    double priceSheet3_0mm{1};

    double orderNumber{1};

    void load();
    void addOrder();

private:


};

#endif // VALUES_H
