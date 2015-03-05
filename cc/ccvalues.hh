/*
* Copyright © 2015 Mygnu <me@mygnu.net>
*
*
*
* This file is part of rgb-quote.
*
* rgb-quote is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Final Term is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with rgb-quote. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VALUES_H
#define VALUES_H

#include <QSettings>

class CCValues
{

public:
    CCValues();
    ~CCValues();

    QSettings settings;

    void load();
    void addOrder();
    double getOpenEnds()const {return openEndsPrice;}
    double getOneEndClosed()const {return oneEndClosedPrice;}
    double getBothEndsClosed()const {return bothEndsClosedPrice;}

    double getFlangesCharge()const {return flangesCharge;}

    double getGalvbond0_6KGPM()const {return galvbond0_6KGPM;}
    double getGalvbond1_6KGPM()const {return galvbond1_6KGPM;}
    double getGalvbond3_0KGPM()const {return galvbond3_0KGPM;}

    double getGalvanisingPKG()const {return galvanisingPKG;}
    double getSprayPaintPMS()const {return sprayPanitPMS;}
    double getPowderCotePMS()const {return powderCotePMS;}

    double getGalvanisingMin() const {return galvanisingMin;}
    double getSprayPaintMin()const {return sprayPanitMin;}
    double getPowderCoteMin()const {return powderCoteMin;}

    double getGalvbond0_6mmPrice()const {return galvbond0_6mmPrice;}
    double getGalvbond1_6mmPrice()const {return galvbond1_6mmPrice;}
    double getGalvbond3_0mmPrice()const {return galvbond3_0mmPrice;}

    double getZinkA0_6mmPrice() const {return zinkA0_6mmPrice;}
    double getZinkA1_6mmPrice() const {return zinkA1_6mmPrice;}
    double getZinkA3_0mmPrice() const {return zinkA3_0mmPrice;}

    double getProfitMargin()const {return profitMargin;}
    double getOrderNumber()const {return orderNumber;}
    bool getOpenAtStartup()const {return openAtStartup;}

private:

    double openEndsPrice{1};
    double oneEndClosedPrice{1};
    double bothEndsClosedPrice{1};

    double flangesCharge{1};

    double galvanisingPKG{1};
    double sprayPanitPMS{1};
    double powderCotePMS{1};

    double galvanisingMin{1};
    double sprayPanitMin{1};
    double powderCoteMin{1};

    double galvbond0_6KGPM{1};
    double galvbond1_6KGPM{1};
    double galvbond3_0KGPM{1};

    double galvbond0_6mmPrice{1};
    double galvbond1_6mmPrice{1};
    double galvbond3_0mmPrice{1};

    double zinkA0_6mmPrice{1};
    double zinkA1_6mmPrice{1};
    double zinkA3_0mmPrice{1};


    double profitMargin{1};
    double orderNumber{1};
    bool openAtStartup{true};


};

#endif // VALUES_H
