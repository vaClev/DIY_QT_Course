#include "unittest.h"

#include "TaskModel.h"
UnitTest::UnitTest() {}

void UnitTest::RunTaskModelTest() const
{
    TaskModel model;

    model.AddTask("Work", "make code of this app", "Low", QDateTime::currentDateTime());
    model.AddTask("Work2", "make noise trrrr", "Middle", QDateTime::currentDateTime());

    auto && tasks = model.GetTasks(); //Получаем список копий!
    tasks[0].description="BAD BAD BAD Romance";

    Task task1 = model.TaskById(1); // Получаем Копию!
}
