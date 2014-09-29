#include "matrix.h"
#include "ui_matrix.h"

Matrix::Matrix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Matrix)
{
    ui->setupUi(this);

    inDXP = "";
    for(int i = 0; i< 4; i++)
    {
        outDXP.append(false);
    };

    dxpClient = new TCPClient(this);
    connect(dxpClient, SIGNAL(sigConnected()), this, SLOT(dxp_connected()));
    connect(dxpClient, SIGNAL(sigDisconnected()), this, SLOT(dxp_disconnected()));

    this->setEnabled(false);
}

Matrix::~Matrix()
{
    delete ui;
}


// ***************** TO DO ********************
// *************************************

void Matrix::on_dxp_enter_clicked()
{
    //DXP ENTER

    // TODO : Désactiver sortie quand bouton désélectionné
    // TODO : utiliser les QuickTime -> affectation E/S en une commande

    for(int i = 0; i < outDXP.size(); i++)
    {
        if(outDXP.at(i))
        {
            dxpClient->sendCommand(inDXP + "*" + QByteArray::number(i+1) + "!\r");
        }
    }
}

void Matrix::viewTiedOutputs(QByteArray input)
{
    ui->dxp_out_1->setChecked(false);
    ui->dxp_out_2->setChecked(false);
    ui->dxp_out_3->setChecked(false);
    ui->dxp_out_4->setChecked(false);
    for(int out = 1; out < 5; out++)
    {
        if(dxpClient->sendQuery(QByteArray::number(out) + "!\r").trimmed() == input)
        {
            switch(out)
            {
            case 1:
                ui->dxp_out_1->setChecked(true);
                break;
            case 2:
                ui->dxp_out_2->setChecked(true);
                break;
            case 3:
                ui->dxp_out_3->setChecked(true);
                break;
            case 4:
                ui->dxp_out_4->setChecked(true);
                break;
            }
            outDXP.replace(out-1, true);
        }
        else
        {
            outDXP.replace(out-1, false);
        }
    }
}

// *************************************
// ************ END TO DO *********************


void Matrix::uncheckAll()
{
    ui->dxp_in_1->setAutoExclusive(false);
    ui->dxp_in_1->setChecked(false);
    ui->dxp_in_1->setAutoExclusive(true);

    ui->dxp_in_2->setAutoExclusive(false);
    ui->dxp_in_2->setChecked(false);
    ui->dxp_in_2->setAutoExclusive(true);

    ui->dxp_in_3->setAutoExclusive(false);
    ui->dxp_in_3->setChecked(false);
    ui->dxp_in_3->setAutoExclusive(true);

    ui->dxp_in_4->setAutoExclusive(false);
    ui->dxp_in_4->setChecked(false);
    ui->dxp_in_4->setAutoExclusive(true);

    ui->dxp_out_1->setChecked(false);
    ui->dxp_out_2->setChecked(false);
    ui->dxp_out_3->setChecked(false);
    ui->dxp_out_4->setChecked(false);

    ui->dxp_mute1->setChecked(false);
    ui->dxp_mute2->setChecked(false);
    ui->dxp_mute3->setChecked(false);
    ui->dxp_mute4->setChecked(false);

    ui->dxp_hdcp1->setChecked(false);
    ui->dxp_hdcp2->setChecked(false);
    ui->dxp_hdcp3->setChecked(false);
    ui->dxp_hdcp4->setChecked(false);
}

bool Matrix::getHdcpStatus(QByteArray input)
{
    QByteArray resp;
    QByteArray esc = "\x1B";
    resp = dxpClient->sendQuery(esc + "E" + input + "HDCP\r").trimmed();
    return resp.toInt();
}

bool Matrix::getMuteStatus(int output)
{
    QByteArray resp;
    QByteArray esc = "\x1B";
    resp = dxpClient->sendQuery(esc + "VM\r");
    return (resp.at(output - 1) == '1' || resp.at(output - 1) == '3');
}

void Matrix::updateStatus()
{
    ui->dxp_hdcp1->setChecked(getHdcpStatus("1"));
    ui->dxp_hdcp2->setChecked(getHdcpStatus("2"));
    ui->dxp_hdcp3->setChecked(getHdcpStatus("3"));
    ui->dxp_hdcp4->setChecked(getHdcpStatus("4"));

    ui->dxp_mute1->setChecked(getMuteStatus(1));
    ui->dxp_mute2->setChecked(getMuteStatus(2));
    ui->dxp_mute3->setChecked(getMuteStatus(3));
    ui->dxp_mute4->setChecked(getMuteStatus(4));
}

bool Matrix::connection(QString _addr, int _port)
{
    if(dxpClient->connection(_addr, _port))
    {
        return true;
    }
    return false;
}

void Matrix::closeConnection()
{
    dxpClient->closeConnection();
}




// DXP SLOTS ------------------

void Matrix::dxp_connected()
{
    ui->dxp_status_icon->setPixmap(QPixmap(":/icons/img/ok.png"));
    this->setEnabled(true);
    this->updateStatus();
}

void Matrix::dxp_disconnected()
{
    ui->dxp_status_icon->setPixmap(QPixmap(":/icons/img/ko.png"));
    this->uncheckAll();
    this->setEnabled(false);
}

void Matrix::on_dxp_out_1_clicked(bool checked)
{
    //DXP output 1
    outDXP.replace(0, checked);
}

void Matrix::on_dxp_out_2_clicked(bool checked)
{
    //DXP output 2
    outDXP.replace(1, checked);
}

void Matrix::on_dxp_out_3_clicked(bool checked)
{
    //DXP output 3
    outDXP.replace(2, checked);
}

void Matrix::on_dxp_out_4_clicked(bool checked)
{
    //DXP output 4
    outDXP.replace(3, checked);
}

void Matrix::on_dxp_in_1_clicked()
{
    //DXP input 1
    inDXP = "1";
    ui->dxp_in_1->setChecked(true);
    this->viewTiedOutputs("1");
}

void Matrix::on_dxp_in_2_clicked()
{
    //DXP input 2
    inDXP = "2";
    ui->dxp_in_2->setChecked(true);
    this->viewTiedOutputs("2");
}

void Matrix::on_dxp_in_3_clicked()
{
    //DXP input 3
    inDXP = "3";
    ui->dxp_in_3->setChecked(true);
    this->viewTiedOutputs("3");
}

void Matrix::on_dxp_in_4_clicked()
{
    //DXP input 4
    inDXP = "4";
    ui->dxp_in_4->setChecked(true);
    this->viewTiedOutputs("4");
}

void Matrix::on_dxp_clear_clicked()
{
    ui->dxp_in_1->setAutoExclusive(false);
    ui->dxp_in_1->setChecked(false);
    ui->dxp_in_1->setAutoExclusive(true);

    ui->dxp_in_2->setAutoExclusive(false);
    ui->dxp_in_2->setChecked(false);
    ui->dxp_in_2->setAutoExclusive(true);

    ui->dxp_in_3->setAutoExclusive(false);
    ui->dxp_in_3->setChecked(false);
    ui->dxp_in_3->setAutoExclusive(true);

    ui->dxp_in_4->setAutoExclusive(false);
    ui->dxp_in_4->setChecked(false);
    ui->dxp_in_4->setAutoExclusive(true);

    ui->dxp_out_1->setChecked(false);
    ui->dxp_out_2->setChecked(false);
    ui->dxp_out_3->setChecked(false);
    ui->dxp_out_4->setChecked(false);
}

void Matrix::on_dxp_hdcp1_toggled(bool checked)
{
    QByteArray esc = "\x1B";
    if(checked)
    {
        dxpClient->sendCommand(esc + "E1*1HDCP\r");
    }
    else
    {
        dxpClient->sendCommand(esc + "E1*0HDCP\r");
    }
}

void Matrix::on_dxp_hdcp2_toggled(bool checked)
{
    QByteArray esc = "\x1B";
    if(checked)
    {
        dxpClient->sendCommand(esc + "E2*1HDCP\r");
    }
    else
    {
        dxpClient->sendCommand(esc + "E2*0HDCP\r");
    }
}

void Matrix::on_dxp_hdcp3_toggled(bool checked)
{
    QByteArray esc = "\x1B";
    if(checked)
    {
        dxpClient->sendCommand(esc + "E3*1HDCP\r");
    }
    else
    {
        dxpClient->sendCommand(esc + "E3*0HDCP\r");
    }
}

void Matrix::on_dxp_hdcp4_toggled(bool checked)
{
    QByteArray esc = "\x1B";
    if(checked)
    {
        dxpClient->sendCommand(esc + "E4*1HDCP\r");
    }
    else
    {
        dxpClient->sendCommand(esc + "E4*0HDCP\r");
    }
}

void Matrix::on_dxp_mute1_toggled(bool checked)
{
    if(checked)
    {
        dxpClient->sendCommand("1*1B1*1Z\r");
    }
    else
    {
        dxpClient->sendCommand("1*0B1*0Z\r");
    }
}

void Matrix::on_dxp_mute2_toggled(bool checked)
{
    if(checked)
    {
        dxpClient->sendCommand("2*1B2*1Z\r");
    }
    else
    {
        dxpClient->sendCommand("2*0B2*0Z\r");
    }
}

void Matrix::on_dxp_mute3_toggled(bool checked)
{
    if(checked)
    {
        dxpClient->sendCommand("3*1B3*1Z\r");
    }
    else
    {
        dxpClient->sendCommand("3*0B3*0Z\r");
    }
}

void Matrix::on_dxp_mute4_toggled(bool checked)
{
    if(checked)
    {
        dxpClient->sendCommand("4*1B4*1Z\r");
    }
    else
    {
        dxpClient->sendCommand("4*0B4*0Z\r");
    }
}

