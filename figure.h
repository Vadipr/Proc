
#ifndef PROCEDURAL_FIGURE_H
#define PROCEDURAL_FIGURE_H
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

namespace figure_space {

    // Параметры, общие для всех альтернатив:
    // Цвет фигуры (перечислимый тип)
    // {красный, оранжевый, желтый, зеленый, голубой, синий, фиолетовый}
    enum Color {
        RED = 0,
        ORANGE = 1,
        YELLOW = 2,
        GREEN = 3,
        BLUE = 4,
        SAPPHIRE = 5,
        PURPLE = 6
    };


    // Перечисляемый тип, определяющий тип фигуры
    enum eFigure {
        CIRCLE = 1,
        RECTANGLE = 2
    };

    // Структура, описывающая круг
    struct figure_circle {
        // Координаты центра (целочисленные)
        int center_x;
        int center_y;
        // Радиус
        double radius;
    };

    // Структура, описывающая прямоугольник
    struct figure_rectangle {
        // Координаты левого верхнего угла (целочисленные)
        int upper_x;
        int upper_y;
        // Координаты нижнего правого угла (целочисленные)
        int bottom_x;
        int bottom_y;
    };

    // Структура, объединяющая все виды фигур
    struct figure {
        union { // Обобщение, построенное на основе непосредственного включения специализаций
            figure_circle fc;
            figure_rectangle fr;
        };
        eFigure figure_type; // Тип объекта
        Color figure_color; // Цвет
        figure *next; // Следующий элемент в списке
    };

    // Контейнер на основе однонаправленного линейного списка.
    // В списке находятся элементы, каждый из них (кроме последнего) имеет ссылку на следующего.
    struct figure_container {
        // Начальный элемент
        figure *begin;
        // Последний элемент
        figure *end;
    };

    /// Объявление функций:

    // Инициализация контейнера
    void Init(figure_container &to_init);

    // Очищает список от элементов
    void Clear(figure_container &cont);

    // Добавить элемент в список
    void Append(figure_container &cont, figure *new_element);

    // ЧТЕНИЕ ИЗ ФАЙЛА
    // Требования ко входному файлу:
    // *тип фигуры*
    // *цвет фигуры*
    // *характеристики фигуры*

    // Чтение в контейнер
    void In(figure_container &cont, std::ifstream &ifstr);
    // Чтение одной абстрактной фигуры
    figure *In(std::ifstream &ifstr);
    // Чтение круга
    void In(figure_circle &fc, std::ifstream &ifstr);
    // Чтение прямоугольника
    void In(figure_rectangle &fr, std::ifstream &ifstr);

    // Запись в файл
    void Out(figure_circle &fc, std::ofstream &ofstr);
    void Out(figure_circle &fr, std::ofstream &ofstr);
    void Out(figure_container &cont, std::ofstream &ofstr);
}

#endif //PROCEDURAL_FIGURE_H
