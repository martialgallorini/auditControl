#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpclient.h"
#include "projector.h"
#include "matrix.h"
#include "pulse.h"
#include "vp771.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:

    // ACTIONS SLOTS
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();

private slots:
    void on_actionUpdate_triggered();

private:
    Ui::MainWindow *ui;

    Projector *pjPanel;
    Matrix *dxpPanel;
    Pulse *plsPanel;
    vp771 *kvpPanel;
};

#endif // MAINWINDOW_H
