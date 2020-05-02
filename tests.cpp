#include "gtest/gtest.h"
#include "figure.h"

using namespace figure_space;

TEST(Functions, Comparator) {
    std::ifstream ifstr("input.txt");
    figure_container c{};
    Init(c);

    In(c, ifstr);
    // Проверка первых двух элементов

    figure *F1 = c.begin->f;
    figure *F2 = c.begin->next->f;
    bool calculate_res = (Calculate(F1)<Calculate(F2));
    bool comparator_res = Comparator(F1, F2);
    EXPECT_EQ(calculate_res, comparator_res);
}

TEST(Functions, Calculate) {
    std::ifstream ifstr("input.txt");
    figure_container c{};
    Init(c);
    In(c, ifstr);
    // Проверка первых двух элементов
    figure *F1 = c.begin->f;
    double calculated1 = Calculate(F1);

    double a,b,d;
    int width, height;
    double actual1 = 0;
    figure_triangle*FT = (figure_triangle*)F1;
    figure_rectangle*FR = (figure_rectangle*)F1;
    figure_circle*FC = (figure_circle*)F1;
    switch(F1->figure_type) {
        case eFigure::TRIANGLE:
            a = (FT->x1-FT->x2)*(FT->x1-FT->x2) + (FT->y1-FT->y2)*(FT->y1-FT->y2);
            b = (FT->x1-FT->x3)*(FT->x1-FT->x3) + (FT->y1-FT->y3)*(FT->y1-FT->y3);
            d = (FT->x3-FT->x2)*(FT->x3-FT->x2) + (FT->y3-FT->y2)*(FT->y3-FT->y2);
            actual1 = a+b+d;
            break;
        case eFigure::RECTANGLE:
            width = FR->bottom_x - FR->upper_x;
            height = FR->upper_y - FR->bottom_y;
            actual1 = std::abs(2*width) + std::abs(2*height);
            break;
        case eFigure::CIRCLE:
            actual1 = 2*PI*FC->radius;
            break;
    }

    EXPECT_EQ(actual1, calculated1);
}

TEST(Functions, Clear) {
    std::ifstream ifstr("input.txt");
    figure_container c{};
    Init(c);
    In(c, ifstr);
    Clear(c);
    auto q = c.begin;
    // Если контейнер очищен, то тест пройден
    EXPECT_EQ(q, nullptr);
}

TEST(Functions, Append) {
    std::ifstream ifstr("input.txt");
    figure_container c{};
    Init(c);
    In(c, ifstr);
    int size1 = c.size;
    Node*CN = new Node;
    CN->f = new figure;
    CN->f->figure_type = eFigure::CIRCLE;
    Append(c,CN);
    int size2 = c.size;
    auto q = c.size;
    // Если контейнер очищен, то тест пройден
    EXPECT_EQ(size1+1, size2);
}


TEST(Functions, Get_size) {
    std::ifstream ifstr("input.txt");
    figure_container c{};
    Init(c);
    int size1 = c.size;
    Node*CN = new Node;
    CN->f = new figure;
    Append(c, CN);
    int size2 = c.size;
    auto q = c.begin;
    // Если контейнер очищен, то тест пройден
    EXPECT_EQ(size1, 0);
    EXPECT_EQ(size2, 1);
}


TEST(Functions, Read) {
    std::ifstream ifstr("input.txt");
    figure_container c{};
    Init(c);
    In(c, ifstr);
    // Если контейнер заполнен
    EXPECT_TRUE(c.size > 0);
}


TEST(Functions, Write) {
    std::ifstream ifstr("input.txt");
    std::ofstream ofstr("output.txt");
    figure_container c{};
    Init(c);
    In(c, ifstr);
    Out(c, ofstr);
    ofstr.close();
    ifstr.close();
    std::ifstream ifstr2("output.txt");
    // Если файл создан и он не пустой
    EXPECT_TRUE(!ifstr2.eof());
}

