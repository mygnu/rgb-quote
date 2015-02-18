#ifndef PREFDIALOG_H
#define PREFDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>

#include "values.h"

namespace Ui {
class PrefDialog;
}

class PrefDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrefDialog(Values &val, QWidget *parent = 0);
    ~PrefDialog();

private slots:
    void onAccept();

private:
    Values *values{nullptr};
    Ui::PrefDialog *ui;
    void loadValuesInGui();

    void saveValues();
    double getDoubleValue(QLineEdit *lineEdit);
    void setDoubleValue(QLineEdit *le, QString name);
    void setDoubleValue(QDoubleSpinBox *sb, QString name);
};

#endif // PREFDIALOG_H
