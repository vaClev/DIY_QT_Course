#include "StatusBarLogger.h"
#include <QLabel>
#include <qboxlayout.h>

StatusBarLogger::StatusBarLogger(QWidget *parent)
    : QWidget{parent}
    , m_statusLabel(new QLabel(this))
{
    SetupUI();

    // Устанавливаем начальное сообщение
    m_statusLabel->setText("Готов к работе");
    m_statusLabel->setStyleSheet("background-color : black; text-shadow:1px 1px 1px silver, -1px 1px 1px silver; color: white; transition: all .5s;");
}


//----------
//slots definitions - start
void StatusBarLogger::OnInfoMessage(const QString &message)
{
    if(m_statusLabel)
       m_statusLabel->setText(QString("Info =>: %1 ;").arg(message));
}

void StatusBarLogger::OnWarningMessage(const QString &message)
{
    if(m_statusLabel)
       m_statusLabel->setText(QString("Warning =>: %1 ;").arg(message));
}

void StatusBarLogger::OnErrorMessage(const QString &message)
{
    if(m_statusLabel)
       m_statusLabel->setText(QString("Error =>: %1 ;").arg(message));
}
//----------
//slots definitions - end


void StatusBarLogger::SetupUI()
{
    // Создаем layout для размещения метки
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(5, 2, 5, 2); // Убираем лишние отступы

    // Настраиваем метку
    m_statusLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_statusLabel->setMinimumWidth(200);
    m_statusLabel->setFrameStyle(QFrame::NoFrame);
    m_statusLabel->setTextFormat(Qt::PlainText);

    // Добавляем метку в layout
    layout->addWidget(m_statusLabel);

    // Устанавливаем layout для виджета
    setLayout(layout);
}
