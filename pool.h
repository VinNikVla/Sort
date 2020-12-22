#ifndef POOL_H
#define POOL_H

#include <QWidget>
#include <QVector>
#include <QDateTime>
#include <QRect>
#include <QPoint>
#include <QPainter>
#include <QDebug>
#include <QRandomGenerator>
#include "math.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <QPair>
#include <QTime>
#include <QObject>
#include <QEvent>

class Pool : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(unsigned int typeSort READ typeSort WRITE setTypeSort)
    Q_PROPERTY(int timeIteration READ getTimeIteration WRITE setTimeIteration)
    Q_PROPERTY(int numberDiscrets READ getNumberDiscrets WRITE setNumberDiscrets)


public:
    explicit Pool(QWidget *parent = nullptr);

    unsigned int typeSort() const;
    int getTimeIteration() const;    
    int getNumberDiscrets() const;

signals:
    void signalPoolInit();
    void signalPrintMessage(int posotionX, int positionY, int size, const QString& message, const QColor& colorPen, QPainter& painter);
    void signalStartSort(bool start);
    void signalEndSort(bool end);
    void signalPause(bool pause);

public slots:
    void slotPoolInit();
    void slotNewGame();

    void slotPrintMessage(int posotionX, int positionY, int size, const QString& message, const QColor& colorPen, QPainter& painter);


    void setTypeSort(unsigned int typeSort);
    void setTimeIteration(int timeIteration);    
    void setNumberDiscrets(int numberDiscrets);
    void setPausa();

private:
    int m_elements;
    QVector<QPair<int, QColor>> arrayPool;
    bool endSort = false;
    bool m_startSort;
    bool m_pausa = false;


    // QWidget interface
    unsigned int m_typeSort;
    int m_timeIteration = 1;    
    int m_numberDiscrets = 2;
    int m_timerID;

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void timerEvent(QTimerEvent *event);
};

#endif // POOL_H
