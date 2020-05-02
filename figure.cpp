
#include "figure.h"
namespace figure_space {

    // Цвета для сопоставления при считывании с файла
    std::string color_strings[8] = {"red", "orange", "yellow", "green", "blue", "sapphire", "purple"};
    const int color_count = 7;

    void In(figure_container &cont, std::ifstream &ifstr) {
        // Чтение до end of file
        while (!ifstr.eof()) {
            // Считываем новый элемент
            Node * new_node = new Node;
            new_node->f = In(ifstr);
            if (new_node->f == nullptr) { // Если произошла ошибка при считывании
                std::cout << "Can't read file, because it has wrong structure." << std::endl;
                // Очищаем уже заполненные элементы списка
                Clear(cont);
                return;
            }

            // Добавляем в список считанный элемент
            Append(cont, new_node);
        }
    }

    void Append(figure_container &cont, Node *new_element) {
        cont.size++;
        if (cont.begin == nullptr) { // Если список пустой
            cont.begin = cont.end = new_element;
        } else {
            cont.end->next = new_element; // Последний элемент хранит ссылку на новый элемент
            cont.end = new_element; // Последний элемент теперь - новый элемент
        }
        new_element->next = nullptr;
    }

    void Clear(figure_container &cont) {
        Node *it_next = nullptr; // Храним следующий элемент, т.к. будем удалять элементы в цикле
        for (Node *it = cont.begin; it != nullptr; it = it_next) {
            it_next = it->next; // Сохраняем следующий элемент
            delete it; // Удаляем элемент
        }
        cont.begin = cont.end = nullptr;
    }

    void figure_space::Out(figure *f, std::ofstream &ofstr) {
        ofstr << color_strings[f->figure_color] << " ";
        switch(f->figure_type) { // Относительно типа объекта вызываем Out
            case eFigure::CIRCLE:
                Out(f->fc, ofstr);
                break;
            case eFigure::RECTANGLE:
                Out(f->fr, ofstr);
                break;
            case eFigure::TRIANGLE:
                Out(f->ft, ofstr);
                break;
        }
    }

    void Out(figure_circle &fc, std::ofstream &ofstr) {
        ofstr << "circle: ";
        ofstr << "x0 = " << fc.center_x << "; ";
        ofstr << "y0 = " << fc.center_y << "; ";
        ofstr << "radius = " << fc.radius << "; ";
        ofstr << "parameter = " << Calculate(fc) << ";\n";
    }

    void Out(figure_rectangle &fr, std::ofstream &ofstr) {
        ofstr << "rectangle: ";
        ofstr << "x1 = " << fr.bottom_x << "; ";
        ofstr << "y1 = " << fr.bottom_y << "; ";
        ofstr << "x2 = " << fr.upper_x << "; ";
        ofstr << "y2 = " << fr.upper_y << "; ";
        ofstr << "parameter = " << Calculate(fr) << ";\n";
    }

    void Out(figure_triangle &ft, std::ofstream &ofstr) {
        ofstr << "triangle: ";
        ofstr << "x1 = " << ft.x1 << "; ";
        ofstr << "y1 = " << ft.y1 << "; ";
        ofstr << "x2 = " << ft.x2 << "; ";
        ofstr << "y2 = " << ft.y2 << "; ";
        ofstr << "x3 = " << ft.x3 << "; ";
        ofstr << "y3 = " << ft.y3 << ";\n";
    }

    void Out(figure_container &cont, std::ofstream &ofstr) {
        int index = 0;
        if(cont.begin == nullptr) { // Если пустой контейнер
            ofstr << "Empty container. " << std::endl;
            return;
        }
        for(Node *it = cont.begin; it != nullptr; it = it->next) {
            index++;
            // Вывод номера и цвета
            ofstr << index << ". ";
            Out(it->f, ofstr);
        }
        std::cout << "Successfully printed to file." << std::endl;
    }

    figure *In(std::ifstream &ifstr) {
        figure *res = new figure; // Указатель на объект, который будет сформирован
        std::string readLine; // Считываемая строка
        char chars[255];
        ifstr.getline(chars, 255);
        // ВВОД ТИПА ФИГУРЫ
        readLine = std::string(chars); // Переводим в строку
        if (readLine == "circle") { // Если вводится круг
            res->figure_type = eFigure::CIRCLE;
        } else if (readLine == "rectangle") { // Если вводится прямоугольник
            res->figure_type = eFigure::RECTANGLE;
        } else if (readLine == "triangle") { // Если вводится треугольник
            res->figure_type = eFigure::TRIANGLE;
        } else {
            delete res;
            return nullptr; // Произошла ошибка при вводе
        }

        // ВВОД ЦВЕТА ФИГУРЫ
        ifstr.getline(chars, 255);
        readLine = std::string(chars); // Переводим в строку
        for (int i = 0; i < color_count; i++) {
            if (readLine == color_strings[i]) { // Если узнали, что за цвет
                res->figure_color = (Color) i; // Сохраняем цвет
                break;
            } else if (i + 1 == color_count) { // Если цвет не был распознан
                delete res;
                return nullptr; // Произошла ошибка при вводе
            }
        }
        // ВВОД ОСТАЛЬНЫХ ХАРАКТЕРИСТИК
        switch (res->figure_type) {
            case eFigure::CIRCLE:
                In(res->fc, ifstr);
                break;
            case eFigure::RECTANGLE:
                In(res->fr, ifstr);
                break;
            case eFigure::TRIANGLE:
                In(res->ft, ifstr);
                break;
        }
        return res;
    }

    void Init(figure_container &to_init) {
        // Задаем начальный и последний элементы в нулевой указатель
        to_init.end = to_init.begin = nullptr;
    }

    void In(figure_circle &fc, std::ifstream &ifstr) {
        int _center_x, _center_y;
        double _radius;
        ifstr >> _center_x >> _center_y >> _radius;
        fc.center_x = _center_x;
        fc.center_y = _center_y;
        fc.radius = _radius;
        if(!ifstr.eof()) { // Считаем переход на новую строку
            ifstr.get();
        }
    }


    void In(figure_triangle &ft, std::ifstream &ifstr) {
        ifstr >> ft.x1 >> ft.y1;
        ifstr >> ft.x2 >> ft.y2;
        ifstr >> ft.x3 >> ft.y3;
        if(!ifstr.eof()) { // Считаем переход на новую строку
            ifstr.get();
        }
    }

    void In(figure_rectangle &fr, std::ifstream &ifstr) {
        int _bottom_x, _bottom_y;
        int _upper_x, _upper_y;
        ifstr >> _bottom_x >> _bottom_y >> _upper_x >> _upper_y;
        fr.bottom_x = _bottom_x;
        fr.bottom_y = _bottom_y;
        fr.upper_x = _upper_x;
        fr.upper_y = _upper_y;
        if(!ifstr.eof()) { // Считаем переход на новую строку
            ifstr.get();
        }
    }

    double Calculate(figure *f) {
        switch(f->figure_type) { // Относительно типа объекта вызываем Out
            case eFigure::CIRCLE:
                return Calculate(f->fc);
            case eFigure::RECTANGLE:
                return Calculate(f->fr);
        }
    }

    double figure_space::Calculate(figure_circle &fc) {
        return 2*PI*fc.radius;
    }

    double figure_space::Calculate(figure_rectangle &fr) {
        int width = fr.bottom_x - fr.upper_x;
        int height = fr.upper_y - fr.bottom_y;
        return std::abs(2*width) + std::abs(2*height);
    }

    void Sort(figure_container &cont) {
        for(Node *it = cont.begin; (it) && (it->next); it = it->next) {
            for (Node *jt = it->next; jt; jt = jt->next) {
                if(Comparator(it->f, jt->f)) {
                    figure* temp = it->f;
                    it->f = jt->f;
                    jt->f = temp;
                }
                std::cout << Calculate(it->f) << " vs " << Calculate(jt->f) << std::endl;
            }
        }
    }

    bool Comparator(figure *first, figure *second) {
        return Calculate(first) < Calculate(second);
    }

}