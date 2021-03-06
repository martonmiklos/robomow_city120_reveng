#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qtcsv/include/qtcsv/csvreader.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonOpenPort_clicked(bool checked)
{
    if (checked) {
        if (m_port.isOpen())
            m_port.close();
        m_port.setPortName(ui->comboBoxSerialPort->currentText());
        m_port.setBaudRate(19200);
        m_port.setDataBits(QSerialPort::Data8);
        m_port.setParity(QSerialPort::NoParity);
        m_port.setStopBits(QSerialPort::OneStop);
        m_port.open(QSerialPort::ReadWrite);
        if (!m_port.isOpen()) {
            ui->pushButtonOpenPort->setChecked(false);
            return;
        }
        ui->pushButtonOpenPort->setText(tr("Close"));
    }
}

void MainWindow::on_pushButton_clicked()
{
    QByteArray data;
//    data.append()
}

void MainWindow::on_pushButtonDecodeSaleaeLog_clicked()
{
    QString csvPath = QFileDialog::getOpenFileName(this,
                                                   tr("Open CSV data"),
                                                   m_settings.value("lastSaleaeCSVPath", QDir::homePath()).toString());
    if (!csvPath.isEmpty()) {
        m_settings.setValue("lastSaleaeCSVPath", csvPath);
        QtCSV::Reader reader;
        QList<QStringList> data = reader.readToList(csvPath);
        qWarning() << data;
        QByteArray dataBuffer;

        for (auto lineData : data) {
            if (lineData.count() >= 3) {
                auto byteStr = lineData.at(2);
                if (byteStr.startsWith("0x")) {
                    dataBuffer.append((char)byteStr.toInt(nullptr, 16));


                }
            }
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    /*
     * AA 07 14 03 00 00 37 <- during sensor poll it is rarely sent
     * AA 07 14 01 00 00 39 <- continous polling */

    QByteArray data;
    data.append(0xAA);
    data.append(0x07);
    data.append(0x14);
    data.append(0x01);
    data.append((quint8)0x00);
    data.append((quint8)0x00);
    data.append(0x39);
    m_port.write(data);
}

void MainWindow::on_pushButton_3_clicked()
{
    QByteArray data;
    data.append(0x23);
    data.append((quint8)0x00);
    data.append((quint8)0x18);
    data.append(0xC4);
    m_port.write(data);
}
