#include "main_window.hpp"

#include <QApplication>
#include <QtCore/QCoreApplication>

#include <iostream>

#include <vector>
#include <string>
#include <dlfcn.h>
#include <iostream>

Base base;

int main(int argc, char *argv[])
{
    const char *action_function = "_ZN8antlogic9GetActionERKNS_3AntEPA3_NS_9AntSensorE";
    base.coords = {{1, 1}, {MY_FIELD_SIZE - 2, 1}, {1, MY_FIELD_SIZE - 2}, {MY_FIELD_SIZE - 2, MY_FIELD_SIZE - 2}};
    std::cout << "Enter file path for 4 strategies (.so)" << std::endl;
    for (int i = 0; i < MY_PLAYER_COUNT; ++i) {
        std::string s;
        std::cin >> s;
        base.strategy.push_back(dlsym(dlopen(s.c_str(), RTLD_LAZY), action_function));
    }
    std::string option;
    std::cout << "Enter 'console' if you want to see throught console visualizer" << std::endl;
    std::cin >> option;
    if (option != "console") {
        QApplication a(argc, argv);
        main_window win;

        win.show();
        return a.exec();
    }
    AntManager manager(MY_FIELD_SIZE, MY_FIELD_SIZE, MY_PLAYER_COUNT, MY_ANT_COUNT, base);
    std::cout << "Enter day length" << std::endl;
    unsigned n;
    std::cin >> n;
    manager.setCui();
    manager.consolePlay(n);
    return 0;
}
