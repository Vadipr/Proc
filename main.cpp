#include <gtest/gtest.h>
#include "figure.h"
using namespace std;
using namespace figure_space;

int main(int argc, char* argv[]) {
    // Если некорректно введены аргументы
    if(argc == 2) {
        testing::InitGoogleTest();
        RUN_ALL_TESTS();
        return 0;
    } else
    if(argc !=3) {
        cout << "incorrect command line! " << endl
             << "Waited: command in_file out_file"
             << endl;
        exit(1);
    }
    ifstream ifst(argv[1]);
    ofstream ofst(argv[2]);
    cout << "Program started"<< endl;
    figure_container c{};
    Init(c);
    In(c, ifst);
    Out(c, ofst);
    ofst << "Sorted:\n";
    Sort(c);
    Out(c, ofst);
    Out(c, ofst, eFigure::CIRCLE);
    Out(c, ofst, eFigure::RECTANGLE);
    cout << "Program ended"<< endl;
    return 0;
}
