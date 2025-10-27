#include "TaskViewModel.h"
#include "TaskModel.h"


TaskViewModel::TaskViewModel(TaskModel * taskModel, QObject *parent)
    : QObject{parent},
    m_taskModel{taskModel}
{
    SetupConnections();
}

// Слоты для UI -начало
void TaskViewModel::OnAddTaskRequested(const QString &title, const QString &description, const QString &priority, const QDateTime &dueDate)
{
    //Нормальные ли данные?
    bool isBadData = title.isEmpty() || description.isEmpty() || priority.isEmpty();

    if(isBadData)
        emit ShowNotification("Empty parameter", "Error");
    else
        emit AddTaskToModel(title, description, priority, dueDate);
}

void TaskViewModel::OnRemoveTaskRequested(int id)
{
    //TODO можно с проверкой. Но для упрощения учебного примера - сразу испувкаем сигнал
    emit RemoveTaskFromModel(id);
}

void TaskViewModel::OnUpdateTaskRequested(int id, const Task &task)
{
    //TODO можно с проверкой. Но для упрощения учебного примера - сразу испувкаем сигнал
    emit UpdateTaskInModel(id, task);
}

void TaskViewModel::OnToggleCompletionRequested(int id)
{
    //TODO для примера.
    if( id>=0 )
      emit SwitchCompleteTaskInModel(id);
}
// Слоты для UI - конец


// Слоты для модели. (Эти функции вызываются как реакция на сигналы модели)
void TaskViewModel::OnTaskAdded(const Task &task)
{
    emit TasksListUpdated(m_taskModel->GetTasks()); //можно так
    emit TaskAddedToView(task);//или так . Тут все по желанию.

    emit ShowNotification(QString("Added New Task %1").arg(task.title), "Info");
    //и например еще залогировать это событие в файл. Испустив соответсвующий сигнал
}

void TaskViewModel::OnTaskRemoved(int id)
{
    emit TaskRemovedFromView(id);
    emit ShowNotification(QString("Task #%1 have been removed").arg(id), "Info");
    //и например залогировать еще это событие
}

void TaskViewModel::OnTaskUpdated(const Task &task)
{
    emit TaskUpdatedInView(task);

}
// Слоты для модели - конец


void TaskViewModel::SetupConnections()
{
    //Реагирование на изменение модели
    connect(m_taskModel, &TaskModel::TaskAdded,
            this, &TaskViewModel::OnTaskAdded);
    connect(m_taskModel, &TaskModel::TaskRemoved,
            this, &TaskViewModel::OnTaskRemoved);
    connect(m_taskModel, &TaskModel::TaskUpdated,
            this, &TaskViewModel::OnTaskUpdated);



    //Подписка модели на сигналы испускаемые ViewModel
    connect(this, &TaskViewModel::AddTaskToModel,
            m_taskModel, &TaskModel::AddTask);
    connect(this, &TaskViewModel::RemoveTaskFromModel,
            m_taskModel, &TaskModel::RemoveTask);
    connect(this, &TaskViewModel::UpdateTaskInModel,
            m_taskModel, &TaskModel::UpdateTask);
    connect(this, &TaskViewModel::SwitchCompleteTaskInModel,
            m_taskModel, &TaskModel::SwitchCompleteStatus);

}

