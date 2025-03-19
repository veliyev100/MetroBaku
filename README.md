
# Metro Train Simulation

### Описание
Данный проект представляет собой многопоточное симулирование работы метрополитена в Баку. В симуляции задействованы 4 линии:
- **Redline (Красная линия)**
- **Greenline (Зеленая линия)**
- **Purpleline (Фиолетовая линия)**
- **Lightgreenline (Светло-зеленая линия)**

Каждая линия имеет свой маршрут и отдельные потоки, которые эмулируют работу поездов. 

### Файлы проекта
- `main.cpp` — Основной файл, в котором создаются потоки для всех линий.
- `MetroBaku.h` — Заголовочный файл с объявлениями глобальных переменных и функций.
- `MetroBaku.cpp` — Реализация функций для эмуляции работы поездов.

---

## 📦 Сборка и запуск на Linux
### Условия:
- Установлен компилятор `g++`
- Установлены библиотеки `pthread`

### Шаги:
1. Скомпилируйте проект с помощью команды:
```bash
 g++ -std=c++17 -pthread -o MetroSimulation main.cpp MetroBaku.cpp
```
2. Запустите программу:
```bash
 ./MetroSimulation
```

---

## 📦 Сборка и запуск на Windows
### Условия:
- Установлен компилятор `g++` (например, из состава MinGW)

### Шаги:
1. Скомпилируйте проект с помощью команды:
```bash
 g++ -std=c++17 -o MetroSimulation.exe main.cpp MetroBaku.cpp -lpthread
```
2. Запустите программу:
```bash
 MetroSimulation.exe
```

---

## ⚙️ Настройка параметров
Параметры симуляции можно изменить в файле `main.cpp`:
- `travel_time` — Время движения между станциями (в секундах).
- `stop_time` — Время остановки на станции (в секундах).
- `turnaround_time` — Время разворота в депо (в секундах).
- `train_start_delay` — Задержка между отправлением поездов (в секундах).
- `max_round`, `max_round_1`, `max_round_2`, `max_round_3` — Количество кругов для поездов на каждой линии.

---

## 💡 Пример вывода
```
Red metro train 1 is running.
Green metro train 2 is running.
Purple metro train 1 is running.
Purple metro train 2 is running.
Light green metro train 1 is running.
Light green metro train 2 is running.
Red metro train 1 has finished its round.
Green metro train 2 has finished its round.
...
```
