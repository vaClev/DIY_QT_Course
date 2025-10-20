#pragma once

#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QDateTime>

struct Task
{
    int id;
    QString title;
    QString description;
    QString priority; // "Low", "Medium", "High"
    QDateTime dueDate;
    bool completed;

public:
    Task(const QString &title, const QString &description, const QString &priority, const QDateTime &dueDate);
    explicit Task();
};

#endif // TASK_H
