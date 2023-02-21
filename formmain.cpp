#include "formmain.h"
#include "ui_formmain.h"

#include <QDebug>
#include <QMessageBox>

FormMain::FormMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormMain)
{
    ui->setupUi(this);
}

FormMain::~FormMain()
{
    delete ui;
}


void FormMain::on_pushButtonRepair_clicked()
{
    // 去除空格
    QString code = ui->lineEditCode->text().replace(" ", "");
    // 补全字符串
    ui->lineEditCode->setText(QString(ModbusCRC16(QByteArray::fromHex(code.toLatin1())).toHex(' ')).toUpper());
}

QByteArray FormMain::ModbusCRC16(QByteArray senddata)
{
    int len = senddata.size();
    uint16_t wcrc = 0XFFFF;
    uint8_t temp;
    int i = 0, j = 0;

    for(i = 0; i < len; i++)
    {
        temp = senddata.at(i);
        wcrc ^= temp;

        for(j = 0; j < 8; j++)
        {
            if(wcrc & 0X0001)
            {
                wcrc >>= 1;
                wcrc ^= 0XA001;
            }

            else
            {
                wcrc >>= 1;
            }
        }
    }

    // 将uint16_t转换为QByteArray
    QByteArray crc = QByteArray::fromHex(QString::number(wcrc, 16).toLatin1());

    if (crc.size() == 2)
    {
        // 高低位互换
        return senddata.append(crc.at(1)).append(crc.at(0));
    }

    else
    {
        return "";
    }
}
