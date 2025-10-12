#include "trafficlight.h"

#include <QTimer>
#include <QDebug>

TrafficLight::TrafficLight(QWidget * parent)
    : QWidget(parent)
    , m_currentState(TrafficLightColors::Red)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &TrafficLight::NextLight);
}

//Это могли бы быть управляемые поля класса.
//Для учебного примера просто константы.
constexpr int RED_INTERVAL = 3000;   //интервал переключения в милисекундах
constexpr int YELLOW_TIME = 1000;    //интервал желтого цвета
//(предположим желтый горит и после красного и после зеленого одинаковое время)
constexpr int GREEN_INTERVAL = 3000; //интервал зеленого цвета

void TrafficLight::Start()
{
    m_timer->start(RED_INTERVAL);
    NextLight();
}

void TrafficLight::Stop()
{
    m_timer->stop();
}

void TrafficLight::NextLight()
{
    switch(m_currentState)
    {
    case TrafficLightColors::Red:
        emit RedLightOn();
        emit LightChanged("RED", RED_INTERVAL);
        qDebug() << "🔴 Red light - STOP!";
        m_timer->setInterval(RED_INTERVAL);
        break;

    case TrafficLightColors::Yellow:
    case TrafficLightColors::YellowAfterGreen:
        emit YellowLightOn();
        emit LightChanged("YELLOW", YELLOW_TIME);
        qDebug() << "🟡 Yellow ligth - ATTENTION!";
        m_timer->setInterval(YELLOW_TIME);
        break;

    case TrafficLightColors::Green:
        emit GreenLightOn();
        emit LightChanged("GREEN", GREEN_INTERVAL);
        qDebug() << "🟢 Green ligth - GO!";
        m_timer->setInterval(GREEN_INTERVAL);
        break;

    default:
        qDebug()<<"TrafficLightColors::Count - Error!";
    }

    m_currentState = GetNextColor(m_currentState);
}
