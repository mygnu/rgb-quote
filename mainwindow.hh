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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QString>
#include <QDir>

#include "cc/ccprefs.hh"
#include "cc/cablecover.hh"
#include "pdfgenerator.hh"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 * creates the main window for the application
 * handles signals and for the bottom buttons
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onPrefClicked();
    void onCalculateClicked();
    void onPdfPrintClicked();
    void selectionMade(const QString &current);

private:
    CCValues ccValues;
    Ui::MainWindow *ui;
    QAction *editPrefAct{nullptr};
    QMenu *editMenu{nullptr};
    CableCover *ccWidget{nullptr};

    void createMenusConnection();
    CCPrefs *pref = nullptr;
    const QVector<QString> comboItems = QVector<QString> {"Cable Cover", "Item Two"};

};

#endif // MAINWINDOW_H
