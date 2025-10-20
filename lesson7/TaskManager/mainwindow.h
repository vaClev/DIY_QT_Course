#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Task.h"

class QListWidget;
class QLineEdit;
class QTextEdit;
class QComboBox;
class QDateTimeEdit;
class QPushButton;
class QLabel;

class TaskViewModel;
class TaskModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    TaskModel* m_taskModel;
    TaskViewModel* m_viewModel;

    // UI элементы
    QListWidget* m_taskList;
    QLineEdit* m_titleEdit;
    QTextEdit* m_descriptionEdit;
    QComboBox* m_priorityCombo;
    QDateTimeEdit* m_dueDateEdit;

    //кнопки управления
    QPushButton * m_addButton;
    QPushButton * m_removeButton;
    QPushButton * m_toggleButton;
    QPushButton * m_updateButton;
    QPushButton * m_clearButton;
    QLabel * m_selectedTaskInfo;

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void SetupUI();
    void SetupConnections();
    void ClearInputFields();

private slots:
    void OnAddButtonClicked();
    void OnRemoveButtonClicked();
    void OnTaskSelectionChanged();
    void OnTasksListUpdated(const QList<Task>& tasks);
    void OnShowNotification(const QString& message, const QString& type);


};
#endif // MAINWINDOW_H
