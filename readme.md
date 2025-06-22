# ZooPark v2 (parkv2)

![CMake](https://img.shields.io/badge/CMake-4.0.3-informational?style=flat&logo=cmake) ![ImGui](https://img.shields.io/badge/ImGui-1.92.0_(WIP)-informational?style=flat&logo=opengl) ![GCC](https://img.shields.io/badge/GCC-15.1.1-informational?style=flat&logo=gnu) ![Arch](https://img.shields.io/badge/OS-Arch_Linux-informational?style=flat&logo=arch-linux) ![C++](https://img.shields.io/badge/C++-17-informational?style=flat&logo=c%2B%2B)

Проект для изучения ООП в C++, реализации паттернов проектирования (MVP) и создания игр с графическим интерфейсом.

## О проекте
Игра "ZooPark" - симулятор управления зоопарком в альтернативной вселенной. Игрок выступает в роли директора, принимая решения о развитии зоопарка, покупке животных и управлении ресурсами. 

**Основные цели проекта:**
- Практика ООП принципов в C++
- Реализация паттерна MVP (Model-View-Presenter)
- Создание кроссплатформенного GUI с ImGui
- Изучение архитектуры игровых движков
- Разработка игровой логики и механик

## Структура проекта
```txt
parkv2
├── CMakeLists.txt
├── include
│   ├── model
│   │   ├── GameLogic.h
│   │   └── Model.h
│   ├── presenter
│   │   └── Presenter.h
│   └── view
│       ├── GameWindow.h
│       ├── ImGuiTheme.h
│       ├── SettingsWindow.h
│       └── View.h
├── lib
│   └── imgui
│       └── CMakeLists.txt
└── src
    ├── main.cpp
    ├── model
    │   ├── GameLogic.cpp
    │   └── Model.cpp
    ├── presenter
    │   └── Presenter.cpp
    └── view
        ├── GameWindow.cpp
        ├── ImGuiTheme.cpp
        ├── SettingsWindow.cpp
        └── View.cpp
```

## Компоненты архитектуры MVP

### Model (Модель)
- `GameLogic.h/cpp`: Ядро игровой логики
- `Model.h/cpp`: Управление данными состояния игры
- **Ответственность:**
  - Хранение состояния зоопарка
  - Бизнес-логика игры
  - Расчет экономики и механик
  - Валидация игровых действий

### View (Представление)
- `GameWindow.h/cpp`: Основное игровое окно
- `SettingsWindow.h/cpp`: Окно настроек
- `ImGuiTheme.h/cpp`: Кастомизация интерфейса
- **Ответственность:**
  - Визуализация игрового состояния
  - Обработка пользовательского ввода
  - Рендеринг интерфейса
  - Управление окнами

### Presenter (Презентер)
- `Presenter.h/cpp`: Посредник между Model и View
- **Ответственность:**
  - Обработка пользовательских действий
  - Обновление модели
  - Уведомление View об изменениях
  - Координация компонентов

## Сборка проекта

### Требования
- Компилятор GCC 15.1.1+
- CMake 3.20+
- Библиотеки: glfw, glew, imgui

### Инструкция
```bash
# Клонирование репозитория
git clone https://github.com/Mark-TinZ/ZooPark_v2.git ./parkv2
cd parkv2

# Создание директории сборки
mkdir build && cd build

# Генерация Makefile
cmake ..

# Компиляция
make

# Запуск
./prog
```

## Игровой процесс
- Управление бюджетом зоопарка
- Покупка/продажа животных
- Строительство вольеров и инфраструктуры
- Наем персонала
- Динамические события