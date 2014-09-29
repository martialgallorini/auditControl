#include "projector.h"
#include "ui_projector.h"

Projector::Projector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Projector)
{
    ui->setupUi(this);

    pjClient = new TCPClient(this);
    connect(pjClient, SIGNAL(sigConnected()), this, SLOT(pj_connected()));
    connect(pjClient, SIGNAL(sigDisconnected()), this, SLOT(pj_disconnected()));

    this->setEnabled(false);
}

Projector::~Projector()
{
    delete ui;
}

bool Projector::connection(QString _addr, int _port)
{
    if(pjClient->connection(_addr, _port))
    {
        return true;
    }
    return false;
}

void Projector::closeConnection()
{
    pjClient->closeConnection();
}

//// ************ TO DO *********************

void Projector::updateStatus()
{
    if(this->getPowerStatus())
    {
        ui->pj_pwOn->setChecked(true);
    }
    else
    {
        ui->pj_pwOff->setChecked(true);
    }

    if(this->getShutterStatus())
    {
        ui->pj_mute->setChecked(true);
    }
    else
    {
        ui->pj_unmute->setChecked(true);
    }

    switch(this->getActiveInput())
    {
        case 0: ui->src_vga->setChecked(true); break;
        case 1: ui->src_bnc->setChecked(true); break;
        case 2: ui->src_dvi->setChecked(true); break;
        case 4: ui->src_svideo->setChecked(true); break;
        case 5: ui->src_comp->setChecked(true); break;
        case 6: ui->src_rgb->setChecked(true); break;
        case 8: ui->src_hdmi->setChecked(true); break;
    }
}

void Projector::uncheckAll()
{
    ui->pj_pwOn->setAutoExclusive(false);
    ui->pj_pwOn->setChecked(false);
    ui->pj_pwOn->setAutoExclusive(true);

    ui->pj_pwOff->setAutoExclusive(false);
    ui->pj_pwOff->setChecked(false);
    ui->pj_pwOff->setAutoExclusive(true);

    ui->pj_mute->setAutoExclusive(false);
    ui->pj_mute->setChecked(false);
    ui->pj_mute->setAutoExclusive(true);

    ui->pj_unmute->setAutoExclusive(false);
    ui->pj_unmute->setChecked(false);
    ui->pj_unmute->setAutoExclusive(true);

    ui->src_vga->setAutoExclusive(false);
    ui->src_vga->setChecked(false);
    ui->src_vga->setAutoExclusive(true);

    ui->src_bnc->setAutoExclusive(false);
    ui->src_bnc->setChecked(false);
    ui->src_bnc->setAutoExclusive(true);

    ui->src_dvi->setAutoExclusive(false);
    ui->src_dvi->setChecked(false);
    ui->src_dvi->setAutoExclusive(true);

    ui->src_svideo->setAutoExclusive(false);
    ui->src_svideo->setChecked(false);
    ui->src_svideo->setAutoExclusive(true);

    ui->src_comp->setAutoExclusive(false);
    ui->src_comp->setChecked(false);
    ui->src_comp->setAutoExclusive(true);

    ui->src_rgb->setAutoExclusive(false);
    ui->src_rgb->setChecked(false);
    ui->src_rgb->setAutoExclusive(true);

    ui->src_hdmi->setAutoExclusive(false);
    ui->src_hdmi->setChecked(false);
    ui->src_hdmi->setAutoExclusive(true);
}

bool Projector::getPowerStatus()
{
    QByteArray resp;
    resp = this->parseResponse(pjClient->sendQuery(":POWR ?\r"));
    return atoi(resp);
}

bool Projector::getShutterStatus()
{
    QByteArray resp;
    //resp = this->parseResponse(pjClient->sendQuery(":SHUT ?\r"));
    resp = this->parseResponse(pjClient->sendQuery(":PMUT ?\r"));
    return atoi(resp);
    //return (resp == "1" ? true : false);
}

quint16 Projector::getActiveInput()
{
    QByteArray resp;
    //resp = this->parseResponse(pjClient->sendQuery(":IABS ?\r"));
    resp = pjClient->sendQuery(":IABS ?\r");
    resp = this->parseResponse(resp);
    return atoi(resp);
    //return (resp == "1" ? true : false);
}


// * HANDLE DEVICE RESPONSE FROM QUERY *

QByteArray Projector::parseResponse(QByteArray msg)
{
    return msg.remove(0, 10);
}

// ************ END TO DO *********************












// PROJECTOR SLOTS ------------------

void Projector::pj_connected()
{
    ui->pj_status_icon->setPixmap(QPixmap(":/icons/img/ok.png"));
    this->setEnabled(true);
    this->updateStatus();
}

void Projector::pj_disconnected()
{
    ui->pj_status_icon->setPixmap(QPixmap(":/icons/img/ko.png"));
    this->uncheckAll();
    this->setEnabled(false);
}

void Projector::on_pj_pwOn_clicked()
{
    //Projector power on
    if(!pjClient->sendCommand(":POWR 1\r"))
    {
        qWarning() << "Problem sending command to projector";
    }
}

void Projector::on_pj_pwOff_clicked()
{
    //projector power off
    if(!pjClient->sendCommand(":POWR 0\r"))
    {
        qWarning() << "Problem sending command to projector";
    }
}

void Projector::on_src_vga_clicked()
{
    //projector source VGA
    if(!pjClient->sendCommand(":IVGA\r"))
    {
        qWarning() << "Problem sending command to projector";
    }
}

void Projector::on_src_bnc_clicked()
{
    //projector source BNC
    if(!pjClient->sendCommand(":IBNC\r"))
    {
        qWarning() << "Problem sending command to projector";
    }
}

void Projector::on_src_dvi_clicked()
{
    //projector source DVI
    if(!pjClient->sendCommand(":IDVI\r"))
    {
        qWarning() << "Problem sending command to projector";
    }
}

void Projector::on_src_svideo_clicked()
{
    //projector source svideo
    if(!pjClient->sendCommand(":ISVI\r"))
    {
        qWarning() << "Problem sending command to projector";
    }
}

void Projector::on_src_hdmi_clicked()
{
    //projector source hdmi
    if(!pjClient->sendCommand(":IHDM\r"))
    {
        qWarning() << "Problem sending command to projector";
    }
}

void Projector::on_src_comp_clicked()
{
    //projector source composite
    if(!pjClient->sendCommand(":ICVI\r"))
    {
        qWarning() << "Problem sending command to projector";
    }
}

void Projector::on_src_rgb_clicked()
{
    //projector source rgb
    if(!pjClient->sendCommand(":IYPP\r"))
    {
        qWarning() << "Problem sending command to projector";
    }
}

void Projector::on_pj_mute_clicked()
{
    //projector avmute on
    if(!pjClient->sendCommand(":SHUT 1\r"))
    {
        qWarning() << "Problem sending command to projector";
    }
}

void Projector::on_pj_unmute_clicked()
{
    //projector avmute off
    if(!pjClient->sendCommand(":SHUT 0\r"))
    {
        qWarning() << "Problem sending command to projector";
    }
}
