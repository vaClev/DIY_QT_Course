#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    /*Макрос Q_OBJECT: Классы, которые используют сигналы и слоты, обязательно должны иметь макрос Q_OBJECT
     в начале объявления класса (в private: секции).
     Это позволяет moc (Meta-Object Compiler) сгенерировать необходимый код.*/
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButtonClicked();

private:
    Ui::MainWindow *ui;
    QSlider * m_slider;
private:
    void InitSliderProgress();
};
#endif // MAINWINDOW_H
