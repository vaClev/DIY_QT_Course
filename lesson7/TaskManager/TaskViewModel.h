#ifndef TASKVIEWMODEL_H
#define TASKVIEWMODEL_H

#include <QObject>
#include "Task.h"
class TaskModel;

class TaskViewModel : public QObject
{
    Q_OBJECT

private:
    TaskModel* m_taskModel;


public:
    explicit TaskViewModel(TaskModel * taskModel, QObject *parent = nullptr);

public slots:// Слоты для UI
    void OnAddTaskRequested(const QString& title, const QString& description,
                            const QString& priority, const QDateTime& dueDate);
    void OnRemoveTaskRequested(int id);
    void OnUpdateTaskRequested(int id, const Task& task);
    void OnToggleCompletionRequested(int id);

public slots:// Слоты для модели
    void OnTaskAdded(const Task& task);
    void OnTaskRemoved(int id);
    void OnTaskUpdated(const Task& task);


signals: // Сигналы для UI
    void TasksListUpdated(const QList<Task>& tasks);
    void TaskAddedToView(const Task& task);
    void TaskRemovedFromView(int id);
    void TaskUpdatedInView(const Task& task);
    void ShowNotification(const QString& message, const QString& type);

signals: // Сигналы для модели
    void AddTaskToModel(const QString& title, const QString& description,
                        const QString& priority, const QDateTime& dueDate);
    void RemoveTaskFromModel(int id);
    void UpdateTaskInModel(int id, const Task& task);
};

#endif // TASKVIEWMODEL_H
