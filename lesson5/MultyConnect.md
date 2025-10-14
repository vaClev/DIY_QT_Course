1. К одному сигналу можно подключать сколько угодно много слотов.

2. В connect можно передавать лямбда выражение. Например так
```cpp
connect(infoBtn, &QPushButton::clicked, 
    [&notifier]() {
        notifier.SendInfo("This is info");
    });
```
получается три аргумента.

3. Пользовательские классы унаследованные от QWidget можно добавлять в главное окно так:
```cpp
    StatusBarLogger * statusLogger = new StatusBarLogger(this); //наследник QWidget
    MessageHistory * messageHistory = new MessageHistory(this); //наследник QWidget

    //размещаем в интерфейсе
    statusBar()->addWidget(statusLogger);
    setCentralWidget(messageHistory);
```
4. Желательно чтобы у пользовательских виджтов внутри был свой Layout. В главный виджет мы вставляем готовый "кусок".

5. Элементам UI можно устанавливать стили CSS. 
```cpp
    m_statusLabel->setStyleSheet("background-color : black; text-shadow:1px 1px 1px silver, -1px 1px 1px silver; color: white; transition: all .5s;");
```
Хорошая практика не хардкодить, а подключать файл с ресурсами. Тогда можно будет менять стили не меняю исходныей код
```cpp
  m_statusLabel->setStyleSheet(R_StatusBarStyle);
  m_button->setStyleSheet(R_SmallButtonsStyle);
```