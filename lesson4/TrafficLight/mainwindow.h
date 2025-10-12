#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TrafficLight;
class QLabel;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void OnRedLight();
    void OnYellowLight();
    void OnGreenLight();
    void OnLightChanged(const QString &color, int duration);

private:
    TrafficLight * m_trafficLight;
    QLabel * m_statusLabel;

private:
    void InitConnectSlots();
};
#endif // MAINWINDOW_H
