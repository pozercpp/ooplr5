#include<iostream>
#include<memory>

#include<array.h>
#include<figure.h>
#include<five.h>
#include<six.h>
#include<eight.h>

int main() {
    std::cout << "INPUT VECTOR SIZE ";
    int n;
    std::cin >> n;
    std::cin.ignore();
    Array<std::shared_ptr<Figure<double>>> figures;
    std::cout << "5-Five\n6-Six\n8-Eight" << std::endl;
    for (int i = 0; i < n; ++i) {
        char c;
        std::cin >> c;
        std::cin.ignore();
        std::shared_ptr<Figure<double>> f;
        if (c == '5') {
            f = std::make_shared<Five<double>>();
        } else if (c == '6') {
            f = std::make_shared<Six<double>>();
        } else if (c == '8') {
            f = std::make_shared<Eight<double>>();
        } else {
            std::cout << "ERROR" << std::endl;
            break;
        }
        std::cin >> *f;
        figures.push(f);
    }
    long double res{0.0};
    for (int i = 0; i < figures.size(); ++i) {
        auto fig = figures[i];
        res += fig->Area();
        std::cout << fig->Centr() << ' ';
    }
    std::cout << std::endl;
    std::cout << res << std::endl;
    return 0;
}