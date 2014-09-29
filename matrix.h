#ifndef MATRIX_H
#define MATRIX_H

#include <QWidget>
#include "tcpclient.h"

namespace Ui {
class Matrix;
}

class Matrix : public QWidget
{
    Q_OBJECT

public:
    explicit Matrix(QWidget *parent = 0);
    ~Matrix();


    // *************************************
    bool connection(QString _addr, int _port);
    void closeConnection();

    void uncheckAll();
    void updateStatus();
    void viewTiedOutputs(QByteArray input);
    bool getHdcpStatus(QByteArray input);
    bool getMuteStatus(int output);


    // *************************************


    QByteArray inDXP;
    QVector<bool> outDXP;


public slots:
    void on_dxp_out_1_clicked(bool checked);
    void on_dxp_out_2_clicked(bool checked);
    void on_dxp_out_3_clicked(bool checked);
    void on_dxp_out_4_clicked(bool checked);
    void on_dxp_in_1_clicked();
    void on_dxp_in_2_clicked();
    void on_dxp_in_3_clicked();
    void on_dxp_in_4_clicked();
    void on_dxp_enter_clicked();

    void dxp_connected();
    void dxp_disconnected();

private slots:
    void on_dxp_clear_clicked();
    void on_dxp_hdcp1_toggled(bool checked);
    void on_dxp_hdcp2_toggled(bool checked);
    void on_dxp_hdcp3_toggled(bool checked);
    void on_dxp_hdcp4_toggled(bool checked);

    void on_dxp_mute1_toggled(bool checked);
    void on_dxp_mute2_toggled(bool checked);
    void on_dxp_mute3_toggled(bool checked);
    void on_dxp_mute4_toggled(bool checked);


private:
    Ui::Matrix *ui;

    TCPClient *dxpClient;
};

#endif // MATRIX_H
