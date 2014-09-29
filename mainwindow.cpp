#include <QtGui>
#include <QtCore>
#include <QBoxLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "projector.h"
#include "vp771.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //create projector layout
    pjPanel = new Projector(this);
    QVBoxLayout *pjLayout = new QVBoxLayout();
    pjLayout->setSpacing(0);
    pjLayout->setMargin(0);
    pjLayout->addWidget(pjPanel); // add projector panel UI to the layout

    //create pulse layout
    plsPanel = new Pulse(this);
    QVBoxLayout *plsLayout = new QVBoxLayout();
    plsLayout->setSpacing(0);
    plsLayout->setMargin(0);
    plsLayout->addWidget(plsPanel); // add pulse panel UI to the layout

    //create matrix layout
    dxpPanel = new Matrix(this);
    QVBoxLayout *dxpLayout = new QVBoxLayout();
    dxpLayout->setSpacing(0);
    dxpLayout->setMargin(0);
    dxpLayout->addWidget(dxpPanel); // add matrix panel UI to the layout

    //create vp771 layout
    kvpPanel = new vp771(this);
    QVBoxLayout *kvpLayout = new QVBoxLayout();
    kvpLayout->setSpacing(0);
    kvpLayout->setMargin(0);
    kvpLayout->addWidget(kvpPanel); // add Kramer vp-771 panel UI to the layout

    // add layouts to the central widgets in mainwindow
    ui->projectorWidget->setLayout(pjLayout);
    ui->matrixWidget->setLayout(dxpLayout);
    ui->pulseWidget->setLayout(plsLayout);
    ui->kvpWidget->setLayout(kvpLayout);
}

MainWindow::~MainWindow()
{
    delete pjPanel;
    delete dxpPanel;
    delete plsPanel;
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    // close all pending connections...
    plsPanel->closeConnection();
    pjPanel->closeConnection();
    dxpPanel->closeConnection();
    kvpPanel->closeConnection();

    // ...then reconnect
    plsPanel->connection("192.168.5.113", 10500);
    pjPanel->connection("192.168.5.111", 1025);
    dxpPanel->connection("192.168.5.112", 23);
    kvpPanel->connection("192.168.5.115", 5000); // default TCP port = 5000 / UDP = 50000
}

void MainWindow::on_actionDisconnect_triggered()
{
    //Disconnect all
    plsPanel->closeConnection();
    pjPanel->closeConnection();
    dxpPanel->closeConnection();
    kvpPanel->closeConnection();
}

void MainWindow::on_actionUpdate_triggered()
{
    pjPanel->updateStatus();
    dxpPanel->updateStatus();
    plsPanel->updateStatus();
}

