#include "TaskModel.h"

TaskModel::TaskModel(QObject *parent)
    : QObject{parent}
{}

//Получить список задач
QList<Task> TaskModel::GetTasks() const
{
    return QList<Task>(m_tasks);
}

//Получить конкретную задачу по id
Task TaskModel::TaskById(int id) const
{
    auto iter = std::find_if(m_tasks.begin(), m_tasks.end(),
                 [id](Task task){
                    return task.id == id;
    });
    if(iter!= m_tasks.end())
        return *iter;

    return Task();
}


//slots - starts
void TaskModel::AddTask(const QString &title, const QString &description, const QString &priority, const QDateTime &dueDate)
{
    Task newTask(title, description, priority, dueDate);
    newTask.id = m_nextId;
    m_tasks.push_back(newTask);

    ++m_nextId;
}

void TaskModel::RemoveTask(int id)
{
  //TODO
}

void TaskModel::UpdateTask(int id, const Task & updatedTask)
{
  //TODO
}

void TaskModel::SwitchCompleteStatus(int id)
{
    //TODO
}
//slots - end
