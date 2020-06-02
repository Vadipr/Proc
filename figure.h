
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
    enum color {
        RED = 0,
        ORANGE = 1,
        YELLOW = 2,
        GREEN = 3,
        BLUE = 4,
        SAPPHIRE = 5,
        PURPLE = 6
    };

    const double pi = 3.1415;

    // Перечисляемый тип, определяющий тип фигуры
    enum e_figure {
        CIRCLE = 1,
        RECTANGLE = 2,
        TRIANGLE = 3
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

    // Структура, описывающая треугольник
    struct figure_triangle {
        // Три точки, задающие целочисленные координаты вершин
        int x1, y1;
        int x2, y2;
        int x3, y3;
    };

    // Структура, объединяющая все виды фигур
    struct figure {
        union { // Обобщение, построенное на основе непосредственного включения специализаций
            figure_circle fc;
            figure_rectangle fr;
            figure_triangle ft;
        };
        double density;
        e_figure figure_type; // Тип объекта
        color figure_color; // Цвет
    };

    struct node {
        Node *next; // Следующий элемент в списке
        figure *f;
    };

    // Контейнер на основе однонаправленного линейного списка.
    // В списке находятся элементы, каждый из них (кроме последнего) имеет ссылку на следующего.
    struct figure_container {

        int size = 0;
        // Начальный элемент
        Node *begin;
        // Последний элемент
        Node *end;
    };

    /// Объявление функций:

    // Инициализация контейнера
    void init(figure_container &to_init);

    // Очищает список от элементов
    void clear(figure_container &cont);

    // Добавить элемент в список
    void append(figure_container &cont, Node *new_element);

    // ЧТЕНИЕ ИЗ ФАЙЛА
    // Требования ко входному файлу:
    // *тип фигуры*
    // *цвет фигуры*
    // *характеристики фигуры*

    // Чтение в контейнер
    void in(figure_container &cont, std::ifstream &ifstr);
    // Чтение одной абстрактной фигуры
    figure *in(std::ifstream &ifstr);
    // Чтение круга
    bool in(figure_circle &fc, std::ifstream &ifstr);
    // Чтение прямоугольника
    bool in(figure_rectangle &fr, std::ifstream &ifstr);
    // Чтение треугольника
    bool in(figure_triangle &ft, std::ifstream &ifstr);

    bool comparator(figure *first, figure *second);

    void sort(figure_container &cont);
    double calculate(figure *f);
    double calculate(figure_circle &fc);
    double calculate(figure_rectangle &fr);
    // Запись в файл
    void out(figure *f, std::ofstream &ofstr);
    void out(figure_circle &fc, std::ofstream &ofstr);
    void out(figure_rectangle &fr, std::ofstream &ofstr);
    void out(figure_triangle &ft, std::ofstream &ofstr);
    void out(figure_container &cont, std::ofstream &ofstr);
    void multi_method(figure_container &cont, std::ofstream &ofstr);
}

#endif //PROCEDURAL_FIGURE_H
