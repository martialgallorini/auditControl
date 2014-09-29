#ifndef PULSE_H
#define PULSE_H

#include <QWidget>
#include "tcpclient.h"

namespace Ui {
class Pulse;
}

class Pulse : public QWidget
{
    Q_OBJECT

public:
    explicit Pulse(QWidget *parent = 0);
    ~Pulse();

    bool connection(QString _addr, int _port);
    void closeConnection();

    QByteArray plsInput;
    QByteArray plsLayer;

    //*************************************

    QByteArray pipLayer;

    QByteArray parseResponse(QByteArray msg);
    bool getPowerStatus();
    bool getAutotakeStatus();
    void uncheckAll();
    void updateStatus();

    //*************************************

public slots:
    void on_pls_in_1_clicked();
    void on_pls_in_2_clicked();
    void on_pls_in_3_clicked();
    void on_pls_in_4_clicked();
    void on_pls_in_5_clicked();
    void on_pls_in_6_clicked();
    void on_pls_black_clicked();
    void on_pls_dvi1_clicked();
    void on_pls_dvi2_clicked();
    void on_pls_sdi1_clicked();
    void on_pls_sdi2_clicked();
    void on_pls_freeze_clicked();
    void on_pls_unfreeze_clicked();
    void on_pls_bgFrame_clicked();
    void on_pls_bgLive_clicked();
    void on_pls_pip_clicked();
    void on_pls_logo_clicked();
    void on_pls_take_clicked();
    void on_pvwID_clicked();
    void on_autoTakeOn_clicked();
    void on_autoTakeOFF_clicked();
    void on_pls_on_clicked();
    void on_pls_off_clicked();

    void pls_connected();
    void pls_disconnected();

private slots:

private:
    Ui::Pulse *ui;

    TCPClient *plsClient;
};

#endif // PULSE_H
