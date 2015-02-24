#ifndef VALUES_H
#define VALUES_H

#include <QSettings>

class Values
{

public:
    Values();
    ~Values();

    QSettings settings;

    void load();
    void addOrder();
    double getOpenEnds()const {return openEnds;}
    double getOneEndClosed()const {return oneEndClosed;}
    double getBothEndsClosed()const {return bothEndsClosed;}
    double getFlangesCharge()const {return flangesCharge;}
    double getThick0_6mmKG()const {return thick0_6mmKG;}
    double getThick1_6mmKG()const {return thick1_6mmKG;}
    double getThick3_0mmKG()const {return thick3_0mmKG;}
    double getGalvanisingPKG()const {return galvanisingPKG;}
    double getSprayPaintPMS()const {return sprayPanitPMS;}
    double getPowderCotePMS()const {return powderCotePMS;}
    double getProfitMargin()const {return profitMargin;}
    double getPriceSheet0_6MM()const {return priceSheet0_6mm;}
    double getPriceSheet1_6MM()const {return priceSheet1_6mm;}
    double getPriceSheet3_0MM()const {return priceSheet3_0mm;}
    double getOrderNumber()const {return orderNumber;}
    bool getOpenAtStartup()const {return openAtStartup;}

private:

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
    bool openAtStartup{true};


};

#endif // VALUES_H
