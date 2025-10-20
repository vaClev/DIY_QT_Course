#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QObject>
#include <QList>

#include "Task.h"

class TaskModel : public QObject
{
    Q_OBJECT

private:
    QList<Task> m_tasks;
    int m_nextId{1};

public:
    explicit TaskModel(QObject *parent = nullptr);

public:// Методы для работы с данными. TODO вынести в интерфейс
    QList<Task> GetTasks() const;
    Task TaskById(int id) const;


public slots:
    void AddTask(const QString& title, const QString& description,
                 const QString& priority, const QDateTime& dueDate);
    void RemoveTask(int id);
    void UpdateTask(int id, const Task& updatedTask);
    void SwitchCompleteStatus(int id);

signals:
    void TaskAdded(const Task& task);
    void TaskRemoved(int id);
    void TaskUpdated(const Task& task);
    void ErrorOccurred(const QString& error);
};

#endif // TASKMODEL_H
