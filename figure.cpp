
#include "figure.h"
namespace figure_space {

    // Цвета для сопоставления при считывании с файла
    std::string color_strings[8] = {"red", "orange", "yellow", "green", "blue", "sapphire", "purple"};
    const int color_count = 7;

    void in(figure_container &cont, std::ifstream &ifstr) {
        // Чтение до end of file
        while (!ifstr.eof()) {
            // Считываем новый элемент
            node * new_node = new node;
            new_node->f = in(ifstr);
            if (new_node->f == nullptr) { // Если произошла ошибка при считывании
                std::cout << "Can't read file, because it has wrong structure." << std::endl;
                // Очищаем уже заполненные элементы списка
                clear(cont);
                return;
            }

            // Добавляем в список считанный элемент
            append(cont, new_node);
        }
    }

    void append(figure_container &cont, node *new_element) {
        cont.size++;
        if (cont.begin == nullptr) { // Если список пустой
            cont.begin = cont.end = new_element;
        } else {
            cont.end->next = new_element; // Последний элемент хранит ссылку на новый элемент
            cont.end = new_element; // Последний элемент теперь - новый элемент
        }
        new_element->next = nullptr;
    }

    void clear(figure_container &cont) {
        node *it_next = nullptr; // Храним следующий элемент, т.к. будем удалять элементы в цикле
        for (node *it = cont.begin; it != nullptr; it = it_next) {
            it_next = it->next; // Сохраняем следующий элемент
            delete it; // Удаляем элемент
        }
        cont.begin = cont.end = nullptr;
    }

    void figure_space::out(figure *f, std::ofstream &ofstr) {
        ofstr << color_strings[f->figure_color] << " ";
        ofstr << "(Density = " << f->density << ") ";
        switch(f->figure_type) { // Относительно типа объекта вызываем out
            case e_figure::CIRCLE:
                out(f->fc, ofstr);
                break;
            case e_figure::RECTANGLE:
                out(f->fr, ofstr);
                break;
            case e_figure::TRIANGLE:
                out(f->ft, ofstr);
                break;
        }
    }

    void out(figure_circle &fc, std::ofstream &ofstr) {
        ofstr << "circle: ";
        ofstr << "x0 = " << fc.center_x << "; ";
        ofstr << "y0 = " << fc.center_y << "; ";
        ofstr << "radius = " << fc.radius << "; ";
        ofstr << "parameter = " << calculate(fc) << ";\n";
    }

    void out(figure_rectangle &fr, std::ofstream &ofstr) {
        ofstr << "rectangle: ";
        ofstr << "x1 = " << fr.bottom_x << "; ";
        ofstr << "y1 = " << fr.bottom_y << "; ";
        ofstr << "x2 = " << fr.upper_x << "; ";
        ofstr << "y2 = " << fr.upper_y << "; ";
        ofstr << "parameter = " << calculate(fr) << ";\n";
    }

    void out(figure_triangle &ft, std::ofstream &ofstr) {
        ofstr << "triangle: ";
        ofstr << "x1 = " << ft.x1 << "; ";
        ofstr << "y1 = " << ft.y1 << "; ";
        ofstr << "x2 = " << ft.x2 << "; ";
        ofstr << "y2 = " << ft.y2 << "; ";
        ofstr << "x3 = " << ft.x3 << "; ";
        ofstr << "y3 = " << ft.y3 << ";\n";
    }

    void out(figure_container &cont, std::ofstream &ofstr) {
        int index = 0;
        if(cont.begin == nullptr) { // Если пустой контейнер
            ofstr << "Empty container. " << std::endl;
            return;
        }
        for(node *it = cont.begin; it != nullptr; it = it->next) {
            index++;
            // Вывод номера и цвета
            ofstr << index << ". ";
            out(it->f, ofstr);
        }
        std::cout << "Successfully printed to file." << std::endl;
    }

    figure *in(std::ifstream &ifstr) {
        figure *res = new figure; // Указатель на объект, который будет сформирован
        std::string read_line; // Считываемая строка
        char chars[255];
        ifstr.getline(chars, 255);
        // ВВОД ТИПА ФИГУРЫ
        read_line = std::string(chars); // Переводим в строку
        if (read_line == "circle") { // Если вводится круг
            res->figure_type = e_figure::CIRCLE;
        } else if (read_line == "rectangle") { // Если вводится прямоугольник
            res->figure_type = e_figure::RECTANGLE;
        } else if (read_line == "triangle") { // Если вводится треугольник
            res->figure_type = e_figure::TRIANGLE;
        } else {
            delete res;
            return nullptr; // Произошла ошибка при вводе
        }
        if(ifstr.eof()) {
            return nullptr;
        }
        // ВВОД ЦВЕТА ФИГУРЫ
        ifstr.getline(chars, 255);
        read_line = std::string(chars); // Переводим в строку
        for (int i = 0; i < color_count; i++) {
            if (read_line == color_strings[i]) { // Если узнали, что за цвет
                res->figure_color = (Color) i; // Сохраняем цвет
                break;
            } else if (i + 1 == color_count) { // Если цвет не был распознан
                delete res;
                return nullptr; // Произошла ошибка при вводе
            }
        }
        // ВВОД ПЛОТНОСТИ
        double dens;
        ifstr >> dens;
        res->density = dens;
        // ВВОД ОСТАЛЬНЫХ ХАРАКТЕРИСТИК
        switch (res->figure_type) {
            case e_figure::CIRCLE:
                in(res->fc, ifstr);
                break;
            case e_figure::RECTANGLE:
                in(res->fr, ifstr);
                break;
            case e_figure::TRIANGLE:
                in(res->ft, ifstr);
                break;
        }
        return res;

    }

    void init(figure_container &to_init) {
        // Задаем начальный и последний элементы в нулевой указатель
        to_init.end = to_init.begin = nullptr;
    }

    void in(figure_circle &fc, std::ifstream &ifstr) {

        int _center_x, _center_y;
        double _radius;
        if(ifstr.eof()) {
            return;
        }
        ifstr >> _center_x;
        if(ifstr.fail() || ifstr.eof()) {
            return;
        }
        ifstr >> _center_y;
        if(ifstr.fail() || ifstr.eof()) {
            return;
        }
        ifstr >> _radius;
        fc.center_x = _center_x;
        fc.center_y = _center_y;
        fc.radius = _radius;
        if(!ifstr.eof()) { // Считаем переход на новую строку
            ifstr.get();
        }
    }


    void in(figure_triangle &ft, std::ifstream &ifstr) {
        if(ifstr.eof()) {
            return;
        }
        ifstr >> ft.x1;
        if(ifstr.fail() || ifstr.eof()) {
            return;
        }
        ifstr >> ft.y1;
        if(ifstr.fail() || ifstr.eof()) {
            return;
        }
        ifstr >> ft.x2;
        if(ifstr.fail() || ifstr.eof()) {
            return;
        }
        ifstr >> ft.y2;
        if(ifstr.fail() || ifstr.eof()) {
            return;
        }
        ifstr >> ft.x3;
        if(ifstr.fail() || ifstr.eof()) {
            return;
        }
        ifstr >> ft.y3;
        if(ifstr.fail() || ifstr.eof()) {
            return;
        }
    }

    void in(figure_rectangle &fr, std::ifstream &ifstr) {
        int _bottom_x, _bottom_y;
        int _upper_x, _upper_y;
        if(ifstr.eof()) {
            return;
        }
        ifstr >> _bottom_x;
        if(ifstr.fail() || ifstr.eof()) {
            return;
        }
        ifstr >> _bottom_y;
        if(ifstr.fail() || ifstr.eof()) {
            return;
        }

        ifstr >> _upper_x;
        if(ifstr.fail() || ifstr.eof()) {
            return;
        }

        ifstr >> _upper_y;
        if(ifstr.fail() || ifstr.eof()) {
            return;
        }
        fr.bottom_x = _bottom_x;
        fr.bottom_y = _bottom_y;
        fr.upper_x = _upper_x;
        fr.upper_y = _upper_y;
        if(!ifstr.eof()) { // Считаем переход на новую строку
            ifstr.get();
        }
    }

    double calculate(figure *f) {
        switch(f->figure_type) { // Относительно типа объекта вызываем out
            case e_figure::CIRCLE:
                return calculate(f->fc);
            case e_figure::RECTANGLE:
                return calculate(f->fr);
        }
    }

    double figure_space::calculate(figure_circle &fc) {
        return 2*pi*fc.radius;
    }

    double figure_space::calculate(figure_rectangle &fr) {
        int width = fr.bottom_x - fr.upper_x;
        int height = fr.upper_y - fr.bottom_y;
        return std::abs(2*width) + std::abs(2*height);
    }

    void sort(figure_container &cont) {
        for(node *it = cont.begin; (it) && (it->next); it = it->next) {
            for (node *jt = it->next; jt; jt = jt->next) {
                if(comparator(it->f, jt->f)) {
                    figure* temp = it->f;
                    it->f = jt->f;
                    jt->f = temp;
                }
                std::cout << calculate(it->f) << " vs " << calculate(jt->f) << std::endl;
            }
        }
    }

    bool comparator(figure *first, figure *second) {
        return calculate(first) < calculate(second);
    }

    void multi_method(figure_container &cont, std::ofstream &ofstr) {
        ofstr << "Writing multimethod" << std::endl;
        for(node *it = cont.begin; (it) && (it->next); it = it->next) {
            for (node *jt = cont.begin->next; jt; jt = jt->next) {
                switch(it->f->figure_type) {
                    case CIRCLE:
                        switch(jt->f->figure_type) {
                            case CIRCLE:
                                ofstr << ": CIRCLE and CIRCLE";
                                break;
                            case RECTANGLE:
                                ofstr << ": CIRCLE and RECTANGLE";
                                break;
                            case TRIANGLE:
                                ofstr << ": CIRCLE and TRIANGLE";
                                break;
                        }
                        break;
                    case RECTANGLE:
                        switch(jt->f->figure_type) {
                            case CIRCLE:
                                ofstr << ": RECTANGLE and CIRCLE";
                                break;
                            case RECTANGLE:
                                ofstr << ": RECTANGLE and RECTANGLE";
                                break;
                            case TRIANGLE:
                                ofstr << ": RECTANGLE and TRIANGLE";
                                break;
                        }
                        break;
                    case TRIANGLE:
                        switch(jt->f->figure_type) {
                            case CIRCLE:
                                ofstr << ": TRIANGLE and CIRCLE";
                                break;
                            case RECTANGLE:
                                ofstr << ": TRIANGLE and RECTANGLE";
                                break;
                            case TRIANGLE:
                                ofstr << ": TRIANGLE and TRIANGLE";
                                break;
                        }
                        break;
                }
                ofstr << std::endl;
                out(it->f, ofstr);
                out(jt->f, ofstr);
                ofstr << "______________________" << std::endl;
            }
        }
    }

}
