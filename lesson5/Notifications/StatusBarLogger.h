#ifndef STATUSBARLOGGER_H
#define STATUSBARLOGGER_H

#include <QWidget>
class QLabel;

class StatusBarLogger : public QWidget
{
    Q_OBJECT

private:
    QLabel * m_statusLabel;

public:
    explicit StatusBarLogger(QWidget *parent = nullptr);

public slots:
    void OnInfoMessage(const QString & message);
    void OnWarningMessage(const QString & message);
    void OnErrorMessage(const QString & message);

private:
    void SetupUI();
};

#endif // STATUSBARLOGGER_H
