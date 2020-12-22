#include "pool.h"

Pool::Pool(QWidget *parent) : QWidget(parent)
{
    QObject::connect(this, &Pool::signalPoolInit, this, &Pool::slotPoolInit, Qt::QueuedConnection);
    QObject::connect(this, &Pool::signalPrintMessage, this, &Pool::slotPrintMessage, Qt::DirectConnection);
    emit signalPoolInit();


}

unsigned int Pool::typeSort() const
{
    return m_typeSort;
}

int Pool::getTimeIteration() const
{
    return m_timeIteration;
}

int Pool::getNumberDiscrets() const
{
    return m_numberDiscrets;
}

void Pool::slotPoolInit()
{
    //m_elements = 200;
    arrayPool.resize(m_numberDiscrets);
    std::srand(std::time(0));

    for(QVector<QPair<int, QColor>>::iterator itb = arrayPool.begin(), ite = arrayPool.end(); itb != ite; ++itb)
    {
        (*itb).first = std::rand() % 100;
        (*itb).second = QColor(255, 255, 255);
    }

    m_pausa = false;
    emit signalPause(!m_pausa);

}

void Pool::setTypeSort(unsigned int typeSort)
{
    m_typeSort = typeSort;
}

void Pool::slotPrintMessage(int posotionX, int positionY, int size, const QString &message, const QColor &colorPen, QPainter &painter)
{
    QFont font("Courier", width() / size, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    painter.setPen(colorPen);
    painter.setFont(font);

    painter.translate( width() / posotionX, height() / positionY);
    painter.drawText(-textWidth/2, 0, message);
}

void Pool::slotNewGame()
{
    m_startSort = true;
    endSort = false;

    arrayPool.resize(m_numberDiscrets);
    std::srand(std::time(0));

    for(QVector<QPair<int, QColor>>::iterator itb = arrayPool.begin(), ite = arrayPool.end(); itb != ite; ++itb)
    {
        (*itb).first = std::rand() % 100;
        (*itb).second = QColor(255, 255, 255);
    }

    m_timerID = startTimer(m_timeIteration);
    emit signalPause(false);
    emit signalStartSort(true);
}

void Pool::setTimeIteration(int timeIteration)
{
    m_timeIteration = timeIteration;
    if(!endSort )
    {
        killTimer(m_timerID);
        if(m_startSort && !m_pausa)
        {
            m_timerID = startTimer(m_timeIteration);
        }
    }
}

void Pool::setNumberDiscrets(int numberDiscrets)
{
    m_numberDiscrets = numberDiscrets;
}

void Pool::setPausa()
{
    m_pausa = !m_pausa;
    if(m_pausa)
    {
        killTimer(m_timerID);
    }
    else
    {
        m_timerID = startTimer(m_timeIteration);
    }
}

void Pool::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(m_startSort)
    {

        const int border = 1;
        const int field = 1;


        double widthFigure = (this->rect().width()  - (border * 2 * m_numberDiscrets) - (field * m_numberDiscrets - 1)) / static_cast<double>(m_numberDiscrets);
        double heightFigure = (this->rect().height() - border - field) / 100.;

        int current = field;


        for(QVector<QPair<int, QColor>>::iterator itb = arrayPool.begin(), ite = arrayPool.end(); itb != ite; ++itb)
        {
            int xLeft = current;
            int yTop = this->rect().height() - (*itb).first * heightFigure - border;
            int xRight = xLeft + std::floor(widthFigure) + border;
            int yBottom = this->rect().height();
            QRect Border(QPoint(xLeft, yTop), QPoint(xRight, yBottom));
            painter.drawRect(Border);
            QRect Figure(QPoint((xLeft + border), yTop + border), QPoint(xRight, yBottom));
            painter.fillRect(Figure, (*itb).second);
            current = current + std::floor(widthFigure) + border + 2 * field;
        }
    }



    if(endSort)
    {

        emit signalPrintMessage(2, 2, 25, "Sort finished!", QColor(Qt::green), painter);
    }
    else
    {
        emit signalPrintMessage(2, 8, 25, "Bubble Sort", QColor(Qt::black), painter);
    }





}


void Pool::timerEvent(QTimerEvent *event)
{
    static int i = 0;
    static int j = 1;



    if(j < m_numberDiscrets)
    {
        qDebug() << "j = " << j << " " << "i = " << i;
        if(i < m_numberDiscrets - j)
        {
            if(i > 0)
                arrayPool[i - 1].second = QColor(Qt::white);
            arrayPool[i].second = QColor(Qt::white);

            arrayPool[i].second = QColor(Qt::blue);
            arrayPool[i+1].second = QColor(Qt::blue);

            if(arrayPool[i].first > arrayPool[i + 1].first)
            {
                arrayPool[i].second = QColor(Qt::red);
                arrayPool[i+1].second = QColor(Qt::red);

                int tmp = arrayPool[i].first;
                arrayPool[i].first = arrayPool[i + 1].first;
                arrayPool[i + 1].first = tmp;
            }
            i++;
        }
        else
        {
            arrayPool[i].second = QColor(Qt::gray);
            if(i > 0)
                arrayPool[i - 1].second = QColor(Qt::white);
            i = 0;
            j++;
        }

    }

    if(arrayPool[1].second == QColor(Qt::gray))
    {
        arrayPool[0].second = QColor(Qt::gray);
        endSort = true;
        j = 1;
        i = 0;
        emit signalStartSort(false);
        m_pausa = false;
        emit signalPause(true);
        killTimer(m_timerID);
    }

    repaint();

}
