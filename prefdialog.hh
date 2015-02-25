#ifndef PREFDIALOG_H
#define PREFDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>

#include "cablecovervalues.hh"

namespace Ui {
class PrefDialog;
}

class CCPrefDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CCPrefDialog(CCValues &val, QWidget *parent = 0);
    ~CCPrefDialog();

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
