#include "mainwindow.h"
#include "TaskModel.h"
#include "TaskViewModel.h"

#include <QComboBox>
#include <QDateTimeEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QSplitter>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_taskModel{new TaskModel(this)}
    , m_viewModel(new TaskViewModel(m_taskModel, this))
{
    SetupUI();
    SetupConnections();

    // Подключаем систему уведомлений
    //NotificationSystem& notifier = NotificationSystem::instance();
    //connect(&notifier, &NotificationSystem::notificationReceived,
    //        this, &MainWindow::onShowNotification);
}

void MainWindow::SetupUI()
{
    // === 1. СОЗДАЕМ ЦЕНТРАЛЬНЫЙ ВИДЖЕТ И ОСНОВНОЙ LAYOUT ===
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    // === 2. СОЗДАЕМ SPLITTER ДЛЯ РАЗДЕЛЕНИЯ ОБЛАСТЕЙ ===
    QSplitter* splitter = new QSplitter(Qt::Horizontal, centralWidget);

    // === 3. ЛЕВАЯ ПАНЕЛЬ - СПИСОК ЗАДАЧ ===
    QWidget* leftPanel = new QWidget(splitter);
    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);

    // Заголовок списка задач
    QLabel* taskListLabel = new QLabel("Список задач", leftPanel);
    taskListLabel->setStyleSheet("font-weight: bold; font-size: 14px;");

    // Список задач
    m_taskList = new QListWidget(leftPanel);
    m_taskList->setAlternatingRowColors(true);
    m_taskList->setSelectionMode(QListWidget::SingleSelection);

    // Кнопки управления списком
    QHBoxLayout* listButtonsLayout = new QHBoxLayout();
    QPushButton* removeButton = new QPushButton("Удалить задачу", leftPanel);
    QPushButton* toggleButton = new QPushButton("Отметить выполненной", leftPanel);

    listButtonsLayout->addWidget(removeButton);
    listButtonsLayout->addWidget(toggleButton);

    // Собираем левую панель
    leftLayout->addWidget(taskListLabel);
    leftLayout->addWidget(m_taskList);
    leftLayout->addLayout(listButtonsLayout);

    // === 4. ПРАВАЯ ПАНЕЛЬ - РЕДАКТИРОВАНИЕ ЗАДАЧ ===
    QWidget* rightPanel = new QWidget(splitter);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

    // Группа "Добавление/редактирование задачи"
    QGroupBox* editGroup = new QGroupBox("Добавление / Редактирование задачи", rightPanel);
    QFormLayout* formLayout = new QFormLayout(editGroup);

    // Поля ввода
    m_titleEdit = new QLineEdit(editGroup);
    m_titleEdit->setPlaceholderText("Введите название задачи");

    m_descriptionEdit = new QTextEdit(editGroup);
    m_descriptionEdit->setMaximumHeight(100);
    m_descriptionEdit->setPlaceholderText("Введите описание задачи");

    m_priorityCombo = new QComboBox(editGroup);
    m_priorityCombo->addItems({"Низкий", "Средний", "Высокий"});
    m_priorityCombo->setCurrentIndex(1); // Средний по умолчанию

    m_dueDateEdit = new QDateTimeEdit(editGroup);
    m_dueDateEdit->setDateTime(QDateTime::currentDateTime().addDays(1));
    m_dueDateEdit->setCalendarPopup(true);
    m_dueDateEdit->setDisplayFormat("dd.MM.yyyy HH:mm");

    // Добавляем поля в форму
    formLayout->addRow("Название:", m_titleEdit);
    formLayout->addRow("Описание:", m_descriptionEdit);
    formLayout->addRow("Приоритет:", m_priorityCombo);
    formLayout->addRow("Срок выполнения:", m_dueDateEdit);

    // Кнопки управления
    QHBoxLayout* editButtonsLayout = new QHBoxLayout();
    QPushButton* addButton = new QPushButton("Добавить задачу", editGroup);
    QPushButton* updateButton = new QPushButton("Обновить задачу", editGroup);
    QPushButton* clearButton = new QPushButton("Очистить", editGroup);

    addButton->setDefault(true);
    addButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; }");

    editButtonsLayout->addWidget(addButton);
    editButtonsLayout->addWidget(updateButton);
    editButtonsLayout->addWidget(clearButton);

    formLayout->addRow(editButtonsLayout);

    // Группа "Информация о задаче"
    QGroupBox* infoGroup = new QGroupBox("Информация о выбранной задаче", rightPanel);
    QVBoxLayout* infoLayout = new QVBoxLayout(infoGroup);

    QLabel* selectedTaskInfo = new QLabel("Выберите задачу из списка", infoGroup);
    selectedTaskInfo->setWordWrap(true);
    selectedTaskInfo->setStyleSheet("padding: 10px; background-color: #f5f5f5; border-radius: 5px;");
    selectedTaskInfo->setMinimumHeight(80);

    infoLayout->addWidget(selectedTaskInfo);

    // Собираем правую панель
    rightLayout->addWidget(editGroup);
    rightLayout->addWidget(infoGroup);
    rightLayout->addStretch(); // Растягиваемый промежуток

    // === 5. НАСТРОЙКА SPLITTER ===
    splitter->addWidget(leftPanel);
    splitter->addWidget(rightPanel);
    splitter->setStretchFactor(0, 1); // Левая панель - растягиваемая
    splitter->setStretchFactor(1, 2); // Правая панель - больше места

    // === 6. СОБИРАЕМ ГЛАВНЫЙ LAYOUT ===
    mainLayout->addWidget(splitter);

    // === 7. СОЗДАЕМ МЕНЮ И ПАНЕЛЬ ИНСТРУМЕНТОВ ===
    //setupMenuAndToolbar();

    // === 8. СОЗДАЕМ СТРОКУ СОСТОЯНИЯ ===
    //setupStatusBar();

    // === 9. УСТАНАВЛИВАЕМ ЦЕНТРАЛЬНЫЙ ВИДЖЕТ ===
    setCentralWidget(centralWidget);

    // === 10. НАСТРОЙКА ОКНА ===
    setWindowTitle("Менеджер задач - Qt Signals/Slots Demo");
    setMinimumSize(800, 600);
    resize(1000, 700);

    // Сохраняем указатели на кнопки для подключения сигналов
    m_addButton = addButton;
    m_removeButton = removeButton;
    m_toggleButton = toggleButton;
    m_updateButton = updateButton;
    m_clearButton = clearButton;
    m_selectedTaskInfo = selectedTaskInfo;
}

void MainWindow::SetupConnections()
{
  // ViewModel -> View
  connect(m_viewModel, &TaskViewModel::TasksListUpdated,
            this, &MainWindow::OnTasksListUpdated);

  connect(m_viewModel, &TaskViewModel::ShowNotification,
          this, &MainWindow::OnShowNotification);


  // View -> ViewModel
  connect(this, &MainWindow::AddTaskRequested,
          m_viewModel, &TaskViewModel::OnAddTaskRequested);
}


//slots
void MainWindow::OnAddButtonClicked()
{

}

void MainWindow::OnRemoveButtonClicked()
{

}

void MainWindow::OnTaskSelectionChanged()
{

}

void MainWindow::OnTasksListUpdated(const QList<Task> &tasks)
{

}

void MainWindow::OnShowNotification(const QString &message, const QString &type)
{

}
