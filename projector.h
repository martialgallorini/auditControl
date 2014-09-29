#ifndef PROJECTOR_H
#define PROJECTOR_H

#include <QWidget>
#include "tcpclient.h"

namespace Ui {
class Projector;
}

class Projector : public QWidget
{
    Q_OBJECT

public:
    explicit Projector(QWidget *parent = 0);
    ~Projector();

    bool connection(QString _addr, int _port);
    void closeConnection();

    bool getPowerStatus();
    bool getShutterStatus();
    quint16 getActiveInput();
    void updateStatus();
    void uncheckAll();

    QByteArray parseResponse(QByteArray msg);

public slots:
    void on_pj_pwOn_clicked();
    void on_pj_pwOff_clicked();
    void on_src_vga_clicked();
    void on_src_bnc_clicked();
    void on_src_dvi_clicked();
    void on_src_svideo_clicked();
    void on_src_hdmi_clicked();
    void on_src_comp_clicked();
    void on_src_rgb_clicked();
    void on_pj_mute_clicked();
    void on_pj_unmute_clicked();

    void pj_connected();
    void pj_disconnected();

private slots:

private:
    Ui::Projector *ui;

    TCPClient *pjClient;
};

#endif // PROJECTOR_H
