# ZooPark v2 (parkv2)

![CMake](https://img.shields.io/badge/CMake-4.0.3-informational?style=flat&logo=cmake) ![ImGui](https://img.shields.io/badge/ImGui-1.92.0_(WIP)-informational?style=flat&logo=opengl) ![GCC](https://img.shields.io/badge/GCC-15.1.1-informational?style=flat&logo=gnu) ![Arch](https://img.shields.io/badge/OS-Arch_Linux-informational?style=flat&logo=arch-linux) ![C++](https://img.shields.io/badge/C++-17-informational?style=flat&logo=c%2B%2B)

Проект для изучения ООП в C++, создание игры с графическим интерфейсом.

## О проекте
Игра "ZooPark" - симулятор управления зоопарком в альтернативной вселенной. Игрок выступает в роли директора, принимая решения о развитии зоопарка, покупке животных и управлении ресурсами. 

**Основные цели проекта:**
- Практика ООП принципов в C++
- Сдать пероду лабы по Япам
- Проверить на практике материал лекций

### Требования
- Компилятор GCC 15.1.1+
- CMake 3.20+
- Библиотеки: glfw, glew, SDL2, SDL2_image, imgui

### Инструкция
Для linux:
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

## Скриншоты игры ZooPark

1. Окно при старте игры:
   ![Img_Okno_pri_startye_igry](https://raw.githubusercontent.com/Mark-TinZ/ZooPark-v2/8342d7b05732de880667074e4c74877e0d9e3d91/Screenshot%20From%202025-06-25%2015-47-48.png)

2. Добавлена возможность перетаскивать окна в игре:
   ![Img_Dobavlena_vozmozhnost_peretaskivat_okna_v_igre](https://raw.githubusercontent.com/Mark-TinZ/ZooPark-v2/8342d7b05732de880667074e4c74877e0d9e3d91/Screenshot%20From%202025-06-25%2015-48-08.png)

3. Menubar:
   ![Img_menubar](https://raw.githubusercontent.com/Mark-TinZ/ZooPark-v2/8342d7b05732de880667074e4c74877e0d9e3d91/Screenshot%20From%202025-06-25%2015-48-08.png)

4. Мини обучение санбоя:
   ![Img_Mini_obucheniye_sanboya](https://raw.githubusercontent.com/Mark-TinZ/ZooPark-v2/8342d7b05732de880667074e4c74877e0d9e3d91/Screenshot%20From%202025-06-25%2015-48-49.png)

5. Обучение в меню игры:
   ![Img_Obucheniye_v_menyu_igry](https://raw.githubusercontent.com/Mark-TinZ/ZooPark-v2/8342d7b05732de880667074e4c74877e0d9e3d91/Screenshot%20From%202025-06-25%2015-49-16.png)

6. Таблица с животными:
   ![Img_Tablitsa_s_zhivotnymi](https://raw.githubusercontent.com/Mark-TinZ/ZooPark-v2/8342d7b05732de880667074e4c74877e0d9e3d91/Screenshot%20From%202025-06-25%2015-54-11.png)

7. Основное меню игры:
   ![Img_Osnovnoye_menyu_igry](https://raw.githubusercontent.com/Mark-TinZ/ZooPark-v2/8342d7b05732de880667074e4c74877e0d9e3d91/Screenshot%20From%202025-06-25%2015-54-35.png)
