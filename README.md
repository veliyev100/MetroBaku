# 🚇 MetroBaku — Симуляция Метро Баку

**MetroBaku** — это многопоточная симуляция работы метрополитена в Баку.  
Поддерживаются 4 линии метро с отдельными потоками поездов.

---

## 🔗 Репозиторий проекта

**GitHub:** [https://github.com/veliyev100/MetroBaku](https://github.com/veliyev100/MetroBaku)

---

## 📥 Скачивание проекта

1. Откройте терминал или командную строку.
2. Клонируйте репозиторий с GitHub:

```bash
git clone https://github.com/veliyev100/MetroBaku.git

    Перейдите в папку проекта:

cd MetroBaku

⚙️ Сборка и запуск
📦 На Linux

Условия:

    Установлен компилятор g++

    Установлены библиотеки pthread

Сборка:

g++ -std=c++17 -pthread -o MetroSimulation main.cpp MetroBaku.cpp

Запуск:

./MetroSimulation

🪟 На Windows

Условия:

    Установлен компилятор g++ (например, MinGW)

Сборка:

g++ -std=c++17 -o MetroSimulation.exe main.cpp MetroBaku.cpp -lpthread

Запуск:

MetroSimulation.exe

⚙️ Настройки симуляции

Параметры можно изменить в файле main.cpp:
Параметр	Описание
travel_time	Время движения между станциями (в секундах)
stop_time	Время остановки на станции (в секундах)
turnaround_time	Время разворота поезда в депо
train_start_delay	Задержка между отправлением поездов
max_round, max_round_1, ...	Количество кругов (рейсов) для каждой линии
💡 Пример вывода

Red metro train 1 is running.
Green metro train 2 is running.
Purple metro train 1 is running.
Light green metro train 2 is running.
Red metro train 1 has finished its round.
...

