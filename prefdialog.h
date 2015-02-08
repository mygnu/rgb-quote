#ifndef PREFDIALOG_H
#define PREFDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class PrefDialog;
}

class PrefDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrefDialog(QSettings &settings, QWidget *parent = 0);
    ~PrefDialog();

private:
    Ui::PrefDialog *ui;


};

#endif // PREFDIALOG_H
