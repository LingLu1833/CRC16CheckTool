#ifndef FORMMAIN_H
#define FORMMAIN_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class FormMain;
}
QT_END_NAMESPACE

class FormMain : public QWidget
{
        Q_OBJECT

    public:
        FormMain(QWidget *parent = nullptr);
        ~FormMain();

        QByteArray ModbusCRC16(QByteArray senddata);

    private slots:
        void on_pushButtonRepair_clicked();

    private:
        Ui::FormMain *ui;
};
#endif // FORMMAIN_H
