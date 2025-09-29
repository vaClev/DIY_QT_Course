При установке почему-то не сразу подключился debugger/
Ошибки были такие: 
1. Вместо точки останова на main - проваливается куда-то в ассемблерные команды. Там глухо, ничего не понятно.
2. При запуске "Command aborted"

Не знаю что именно помогает, но точно нужно устанавливать совместимую пару:
Компилятор+Отладчик. https://doc.qt.io/qtcreator/creator-debugger-engines.html
Для Windows 2 Варианта:  
Windows/MinGW	GCC	GDB
Windows/MSVC	Microsoft Visual C++ Compiler	Debugging Tools for Windows/CDB

На моей ОС для QtCreator пошел хорошо MinGW  + GDB. 
Потребовалось скачать https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/downloads
И в настройках добавить конфигурацию. Она установилась сразу, но не подключилась почему-то.
См Скриншот.

в файле .pro
CONFIG += debug

...
дебагер заработал. и ОК
