#include "TaskViewModel.h"
#include "TaskModel.h"


TaskViewModel::TaskViewModel(TaskModel * taskModel, QObject *parent)
    : QObject{parent},
    m_taskModel{taskModel}
{}

// Слоты для UI -начало
void TaskViewModel::OnAddTaskRequested(const QString &title, const QString &description, const QString &priority, const QDateTime &dueDate)
{
    //TODO
}

void TaskViewModel::OnRemoveTaskRequested(int id)
{
    //TODO
}

void TaskViewModel::OnUpdateTaskRequested(int id, const Task &task)
{
    //TODO
}

void TaskViewModel::OnToggleCompletionRequested(int id)
{
    //TODO
}
// Слоты для UI - конец


// Слоты для модели
void TaskViewModel::OnTaskAdded(const Task &task)
{
    //TODO
}

void TaskViewModel::OnTaskRemoved(int id)
{
    //TODO
}

void TaskViewModel::OnTaskUpdated(const Task &task)
{
    //TODO
}
// Слоты для модели - конец


