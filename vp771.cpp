#include "vp771.h"
#include "ui_vp771.h"

vp771::vp771(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vp771)
{
    ui->setupUi(this);

    kvpClient = new TCPClient(this);
    connect(kvpClient, SIGNAL(sigConnected()), this, SLOT(kvp_connected()));
    connect(kvpClient, SIGNAL(sigDisconnected()), this, SLOT(kvp_disconnected()));

    this->setEnabled(false);
}

vp771::~vp771()
{
    delete ui;
}

bool vp771::connection(QString _addr, int _port)
{
    if(kvpClient->connection(_addr, _port))
    {
        return true;
    }
    return false;
}

QByteArray vp771::parseResponse(QByteArray msg)
{
    QList<QByteArray> values;
    values = msg.split(',');
    return values.at(2).trimmed();
}

//bool vp771::getHdcpStatus(QByteArray input)
//{
//    QByteArray resp;
//    resp = parseResponse(kvpClient->sendQuery("#Y 1,134\r"));
//    return resp.toInt();
//}

// --------------- SLOTS -------------------

void vp771::closeConnection()
{
    kvpClient->closeConnection();
}

void vp771::kvp_connected()
{
    ui->kvp_status_icon->setPixmap(QPixmap(":/icons/img/ok.png"));
    this->setEnabled(true);
}

void vp771::kvp_disconnected()
{
    ui->kvp_status_icon->setPixmap(QPixmap(":/icons/img/ko.png"));
    this->setEnabled(false);
}

void vp771::on_kvp_hmdi1_clicked()
{
    if(kvpClient->sendCommand("#Y 0,120,13\r"))
    {
        ui->kvp_hdcp->setEnabled(true);
        ui->kvp_hdcpFollow->setEnabled(true);
    }
    else
    {
        qWarning() << "Problem sending command to Scaler";
    }
}

void vp771::on_kvp_hdmi2_clicked()
{
    if(kvpClient->sendCommand("#Y 0,120,14\r"))
    {
        ui->kvp_hdcp->setEnabled(true);
        ui->kvp_hdcpFollow->setEnabled(true);
    }
    else
    {
        qWarning() << "Problem sending command to Scaler";
    }
}

void vp771::on_kvp_sdi_clicked()
{
    if(kvpClient->sendCommand("#Y 0,120,17\r"))
    {
        ui->kvp_hdcp->setEnabled(false);
        ui->kvp_hdcpFollow->setEnabled(false);
    }
    else
    {
        qWarning() << "Problem sending command to Scaler";
    }
}

void vp771::on_kvp_vga1_clicked()
{
    if(kvpClient->sendCommand("#Y 0,120,11\r"))
    {
        ui->kvp_hdcp->setEnabled(false);
        ui->kvp_hdcpFollow->setEnabled(false);
    }
    else
    {
        qWarning() << "Problem sending command to Scaler";
    }
}

void vp771::on_kvp_vga2_clicked()
{
    if(kvpClient->sendCommand("#Y 0,120,12\r"))
    {
        ui->kvp_hdcp->setEnabled(false);
        ui->kvp_hdcpFollow->setEnabled(false);
    }
    else
    {
        qWarning() << "Problem sending command to Scaler";
    }
}

void vp771::on_kvp_dp_clicked()
{
    if(kvpClient->sendCommand("#Y 0,120,16\r"))
    {
        ui->kvp_hdcp->setEnabled(true);
        ui->kvp_hdcpFollow->setEnabled(true);
    }
    else
    {
        qWarning() << "Problem sending command to Scaler";
    }
}

void vp771::on_kvp_cv1_clicked()
{
    if(kvpClient->sendCommand("#Y 0,120,9\r"))
    {
        ui->kvp_hdcp->setEnabled(false);
        ui->kvp_hdcpFollow->setEnabled(false);
    }
    else
    {
        qWarning() << "Problem sending command to Scaler";
    }
}

void vp771::on_kvp_cv2_clicked()
{
    if(kvpClient->sendCommand("#Y 0,120,10\r"))
    {
        ui->kvp_hdcp->setEnabled(false);
        ui->kvp_hdcpFollow->setEnabled(false);
    }
    else
    {
        qWarning() << "Problem sending command to Scaler";
    }
}

void vp771::on_kvp_rgb_clicked()
{
    if(kvpClient->sendCommand("#Y 0,120,15\r"))
    {
        ui->kvp_hdcp->setEnabled(false);
        ui->kvp_hdcpFollow->setEnabled(false);
    }
    else
    {
        qWarning() << "Problem sending command to Scaler";
    }
}

void vp771::on_kvp_blank_toggled(bool checked)
{
    QByteArray command;
    if (checked)
    {
        command = "#Y 0,742,1\r";
    }
    else
    {
        command = "#Y 0,742,0\r";
    }

    if(!kvpClient->sendCommand(command))
    {
        qWarning() << "Problem sending command to Scaler";
    }
}

void vp771::on_kvp_freeze_toggled(bool checked)
{
    QByteArray command;
    if (checked)
    {
        command = "#Y 0,741,1\r";
    }
    else
    {
        command = "#Y 0,741,0\r";
    }

    if(!kvpClient->sendCommand(command))
    {
        qWarning() << "Problem sending command to Scaler";
    }
}


void vp771::on_kvp_pattern_activated(int index)
{
    QByteArray command;
    switch (index)
    {
    case 0 : command = "#Y 0,760,0\r"; break;
    case 1 : command = "#Y 0,760,1\r"; break;
    case 2 : command = "#Y 0,760,2\r"; break;
    default : break;
    }

    if(!kvpClient->sendCommand(command))
    {
        qWarning() << "Problem sending command to Scaler";
    }
}

void vp771::on_kvp_hdcp_toggled(bool checked)
{
    QByteArray command;
    if (checked)
    {
        command = "#Y 0,134,1\r"; // HDCP ON
    }
    else
    {
        command = "#Y 0,134,0\r"; // HDCP OFF
    }

    if(!kvpClient->sendCommand(command))
    {
        qWarning() << "Problem sending command to Scaler";
    }
}

void vp771::on_kvp_hdcpFollow_activated(int index)
{
    QByteArray command;
    switch (index)
    {
    case 0 : command = "#Y 0,635,0\r"; break; // HDCP Follow Output
    case 1 : command = "#Y 0,635,1\r"; break; // HDCP Follow Input
    default : break;
    }

    if(!kvpClient->sendCommand(command))
    {
        qWarning() << "Problem sending command to Scaler";
    }
}

