#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QWidget>
#include "trafficlightcolors.h"


class TrafficLight : public QWidget
{
    Q_OBJECT
public:
    explicit TrafficLight(QWidget *parent = nullptr);

signals:
    //пользовательские сигналы
    void RedLightOn();
    void YellowLightOn();
    void GreenLightOn();
    void LightChanged(const QString & color, int duration);

public slots:
    void Start();     // Запустить светофор (включить)
    void Stop();      // Остановить работу светофора
    void NextLight(); // Переключить на следующий свет

private:
    QTimer * m_timer;
    TrafficLightColors m_currentState;
};

#endif // TRAFFICLIGHT_H
