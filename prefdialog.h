#ifndef PREFDIALOG_H
#define PREFDIALOG_H

#include <QDialog>
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

private:
    Values *values{nullptr};
    Ui::PrefDialog *ui;
    void setDefaults();

};

#endif // PREFDIALOG_H
