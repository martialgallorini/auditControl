#ifndef VP771_H
#define VP771_H

#include <QWidget>
#include "tcpclient.h"

namespace Ui {
class vp771;
}

class vp771 : public QWidget
{
    Q_OBJECT

public:
    explicit vp771(QWidget *parent = 0);
    ~vp771();

    bool connection(QString _addr, int _port);
    void closeConnection();
    QByteArray parseResponse(QByteArray msg);


public slots:
    void kvp_connected();
    void kvp_disconnected();

private slots:
    void on_kvp_vga1_clicked();

    void on_kvp_hmdi1_clicked();

    void on_kvp_hdmi2_clicked();

    void on_kvp_sdi_clicked();

    void on_kvp_vga2_clicked();

    void on_kvp_dp_clicked();

    void on_kvp_cv1_clicked();

    void on_kvp_cv2_clicked();

    void on_kvp_rgb_clicked();

    void on_kvp_blank_toggled(bool checked);

    void on_kvp_freeze_toggled(bool checked);

    void on_kvp_pattern_activated(int index);

    void on_kvp_hdcp_toggled(bool checked);

    void on_kvp_hdcpFollow_activated(int index);

private:
    Ui::vp771 *ui;
    TCPClient *kvpClient;
};

#endif // VP771_H
