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

#ifndef PREFDIALOG_H
#define PREFDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>

#include "ccvalues.hh"

namespace Ui {
class PrefDialog;
}

class CCPrefs : public QDialog
{
    Q_OBJECT

public:
    explicit CCPrefs(QWidget *parent = 0, CCValues *val = nullptr);
    ~CCPrefs();

private slots:
    void onAccept();

private:
    CCValues *values{nullptr};
    Ui::PrefDialog *ui;
    void loadValuesInGui();

    void saveValues();
    void setDoubleValue(QLineEdit *le, QString name);
    void setDoubleValue(QDoubleSpinBox *sb, QString name);
};

#endif // PREFDIALOG_H
