#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QObject::connect(ui->timeItration, SIGNAL(valueChanged(int)), ui->pool, SLOT(setTimeIteration(int)));
    QObject::connect(ui->buttonBegin, SIGNAL(pressed()), ui->pool, SLOT(slotNewGame()));
    QObject::connect(ui->buttonClose, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->numberDiscrets, SIGNAL(valueChanged(int)), ui->pool, SLOT(setNumberDiscrets(int)));
    ui->numberDiscrets->setRange(2, 300);
    ui->timeItration->setRange(1, 1000);

    QObject::connect(ui->pool, SIGNAL(signalStartSort(bool)), ui->buttonBegin, SLOT(setDisabled(bool)));
    QObject::connect(ui->pool, SIGNAL(signalStartSort(bool)), ui->numberDiscrets, SLOT(setDisabled(bool)));
    //QObject::connect(ui->pool, SIGNAL(signalStartSort(bool)), ui->timeItration, SLOT(setDisabled(bool)));
    QObject::connect(ui->pool, SIGNAL(signalStartSort(bool)), ui->typeSort, SLOT(setDisabled(bool)));

    QObject::connect(ui->pool, SIGNAL(signalPause(bool)), ui->buttonPause, SLOT(setDisabled(bool)));

    QObject::connect(ui->buttonPause, SIGNAL(clicked()), ui->pool, SLOT(setPausa()));
        ui->buttonPause->setCheckable(true);
        ui->labelTimeIteration->setAlignment(Qt::AlignCenter);
        ui->sliderTimeItreation->setTickPosition(QSlider::TicksBothSides);
        ui->sliderTimeItreation->setTickInterval(10);
        ui->sliderTimeItreation->setRange(1, 1000);
    QObject::connect(ui->sliderTimeItreation, SIGNAL(valueChanged(int)), ui->pool, SLOT(setTimeIteration(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeNamePause(bool state)
{
    if(state)
    {
        ui->buttonPause->setText("Возобновить");
    }
    else
    {
        ui->buttonPause->setText("Пауза");
    }
}
