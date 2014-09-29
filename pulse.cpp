#include "pulse.h"
#include "ui_pulse.h"

Pulse::Pulse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pulse)
{
    ui->setupUi(this);

    plsInput = "0";
    plsLayer = "2";

    plsClient = new TCPClient(this);
    connect(plsClient, SIGNAL(sigConnected()), this, SLOT(pls_connected()));
    connect(plsClient, SIGNAL(sigDisconnected()), this, SLOT(pls_disconnected()));

    this->setEnabled(false);
}

Pulse::~Pulse()
{
    delete ui;
}

bool Pulse::connection(QString _addr, int _port)
{
    if(plsClient->connection(_addr, _port))
    {
        return true;
    }
    return false;
}

void Pulse::closeConnection()
{
    plsClient->closeConnection();
}


// ************ TO DO *********************
// ADD PIP INPUT

QByteArray Pulse::parseResponse(QByteArray msg)
{
    return msg.remove(0, 2);
}

bool Pulse::getPowerStatus()
{
    QByteArray resp;
    //resp = this->parseResponse(plsClient->sendQuery("wS"));
    resp = plsClient->sendQuery("wS");
    resp = this->parseResponse(resp);

    return atoi(resp);
}

bool Pulse::getAutotakeStatus()
{
    QByteArray resp;
    resp = this->parseResponse(plsClient->sendQuery("YT"));
    return atoi(resp);
}

void Pulse::uncheckAll()
{
    ui->pls_on->setAutoExclusive(false);
    ui->pls_on->setChecked(false);
    ui->pls_on->setAutoExclusive(true);

    ui->pls_off->setAutoExclusive(false);
    ui->pls_off->setChecked(false);
    ui->pls_off->setAutoExclusive(true);

    ui->pls_in_1->setChecked(false);
    ui->pls_in_2->setChecked(false);
    ui->pls_in_3->setChecked(false);
    ui->pls_in_4->setChecked(false);
    ui->pls_in_5->setChecked(false);
    ui->pls_in_6->setChecked(false);
    ui->pls_dvi1->setChecked(false);
    ui->pls_dvi2->setChecked(false);
    ui->pls_sdi1->setChecked(false);
    ui->pls_sdi2->setChecked(false);

    ui->autoTakeOn->setAutoExclusive(false);
    ui->autoTakeOn->setChecked(false);
    ui->autoTakeOn->setAutoExclusive(true);

    ui->autoTakeOFF->setAutoExclusive(false);
    ui->autoTakeOFF->setChecked(false);
    ui->autoTakeOFF->setAutoExclusive(true);
}

void Pulse::updateStatus()
{
    if(!this->getPowerStatus())
    {
        ui->pls_on->setChecked(true);
    }
    else
    {
        ui->pls_off->setChecked(true);
    }

    if(this->getAutotakeStatus())
    {
        ui->autoTakeOn->setChecked(true);
    }
    else
    {
        ui->autoTakeOFF->setChecked(true);
    }

    // inputs
    // output layers
}

// ************ END TO DO *********************









// PULSE SLOTS ------------------

void Pulse::pls_connected()
{
    ui->pls_status_icon->setPixmap(QPixmap(":/icons/img/ok.png"));
    this->setEnabled(true);
    this->updateStatus();
}

void Pulse::pls_disconnected()
{
    ui->pls_status_icon->setPixmap(QPixmap(":/icons/img/ko.png"));
    this->uncheckAll();
    this->setEnabled(false);
}

void Pulse::on_pls_in_1_clicked()
{
    //Pulse input 1
    //ui->pls_in_1->setChecked(true);
    plsInput = "1";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_in_2_clicked()
{
    //Pulse input 2
    plsInput = "2";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_in_3_clicked()
{
    //Pulse input 3
    plsInput = "3";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_in_4_clicked()
{
    //Pulse input 4
    plsInput = "4";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_in_5_clicked()
{
    //Pulse input 5
    plsInput = "5";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_in_6_clicked()
{
    //Pulse input 6
    plsInput = "6";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_black_clicked()
{
    //Pulse input BLACK
    plsInput = "0";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_dvi1_clicked()
{
    //Pulse input DVI1
    plsInput = "9";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_dvi2_clicked()
{
    //Pulse input DVI2
    plsInput = "10";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_sdi1_clicked()
{
    //Pulse input SDI1
    plsInput = "11";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_sdi2_clicked()
{
    //Pulse input SDI2
    plsInput = "12";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_freeze_clicked()
{
    //Pulse input FREEZE
    if(!plsClient->sendCommand(plsInput + "," + "1Sf"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_unfreeze_clicked()
{
    //Pulse input UNFREEZE
    if(!plsClient->sendCommand(plsInput + "," + "0Sf"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_bgFrame_clicked()
{
    //Pulse output FRAME
    plsLayer = "0";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_bgLive_clicked()
{
    //Pulse output LIVE
    plsLayer = "2";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_pip_clicked()
{
    //Pulse output PIP
    plsLayer = "3";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_logo_clicked()
{
    //Pulse output LOGO
    plsLayer = "6";
    if(!plsClient->sendCommand("1," + plsLayer + "," + plsInput + "IN"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_take_clicked()
{
    //Pulse TAKE
    if(!plsClient->sendCommand("1TK"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_pls_on_clicked()
{
    if(!plsClient->sendCommand("0wQ"))
    {
        qWarning() << "Problem sending command to DXP";
    }
}

void Pulse::on_pls_off_clicked()
{
    if(!plsClient->sendCommand("1wQ"))
    {
        qWarning() << "Problem sending command to DXP";
    }
}

void Pulse::on_pvwID_clicked()
{
    //Pulse disable preview ID
    if(!plsClient->sendCommand("1bI"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_autoTakeOn_clicked()
{
    //Pulse autotake on
    if(!plsClient->sendCommand("1YT"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}

void Pulse::on_autoTakeOFF_clicked()
{
    //Pulse autotake off
    if(!plsClient->sendCommand("OYT"))
    {
        qWarning() << "Problem sending command to Pulse";
    }
}
