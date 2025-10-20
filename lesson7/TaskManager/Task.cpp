#include "Task.h"

Task::Task(const QString &titleArg, const QString &descriptionArg, const QString &priorityArg, const QDateTime &dueDateArg)
    :
    id{0},
    title{titleArg},
    description{descriptionArg},
    priority{priorityArg},
    dueDate{dueDateArg},
    completed{false}
{
}

Task::Task() = default;
