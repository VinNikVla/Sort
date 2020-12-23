#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QRect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QDesktopWidget* p_desktop = QApplication::desktop();
    const QRect sizeDesktop = p_desktop->screenGeometry();

    ui->setupUi(this);
    QObject::connect(ui->buttonBegin, SIGNAL(pressed()), ui->pool, SLOT(slotNewGame()));
    QObject::connect(ui->pool, SIGNAL(signalStartSort(bool)), ui->buttonBegin, SLOT(setDisabled(bool)));

    QObject::connect(ui->buttonClose, SIGNAL(clicked()), this, SLOT(close()));

    QObject::connect(ui->sliderNumberDiscrets, SIGNAL(valueChanged(int)), ui->pool, SLOT(setNumberDiscrets(int)));
    ui->sliderNumberDiscrets->setRange(2, 351);
    //ui->sliderNumberDiscrets->s
    QObject::connect(ui->sliderNumberDiscrets, SIGNAL(valueChanged(int)), ui->labelDisplayNemberDiscrets, SLOT(setNum(int)));
    ui->labelDisplayNemberDiscrets->setText("2");
    QObject::connect(ui->pool, SIGNAL(signalStartSort(bool)), ui->sliderNumberDiscrets, SLOT(setDisabled(bool)));
    ui->labelNumberDiscrets->setAlignment(Qt::AlignCenter);
    ui->labelNumberDiscrets->setText("Число отсчётов, шт");

    QObject::connect(ui->pool, SIGNAL(signalPause(bool)), ui->buttonPause, SLOT(setDisabled(bool)));
    QObject::connect(ui->buttonPause, SIGNAL(clicked()), ui->pool, SLOT(setPausa()));
    ui->buttonPause->setCheckable(true);

    ui->labelTimeIteration->setAlignment(Qt::AlignCenter);
    ui->sliderTimeItreation->setTickInterval(10);
    ui->sliderTimeItreation->setRange(1, 1000);
    QObject::connect(ui->sliderTimeItreation, SIGNAL(valueChanged(int)), ui->pool, SLOT(setTimeIteration(int)));
    ui->labelDisplayTimeIteration->setText("1");
    QObject::connect(ui->sliderTimeItreation, SIGNAL(valueChanged(int)), ui->labelDisplayTimeIteration, SLOT(setNum(int)));
    ui->buttonTypeSort->setText("Тип сортировки");
    QMenu* pMenu = new QMenu(ui->buttonTypeSort);
    pMenu->addAction("Пузырьковая");
    pMenu->addAction("Быстрая");
    pMenu->addAction("Херовая");

    ui->buttonTypeSort->setMenu(pMenu);

    ui->verticalLayout->setGeometry(sizeDesktop);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeNamePause(bool state)
{
    ui->buttonPause->setText(state ? "Возобновить" : "Пауза");
}
