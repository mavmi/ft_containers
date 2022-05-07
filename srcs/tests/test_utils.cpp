#include "../../include/tests/test_utils.hpp"

std::string Printer::color_to_string(Color color){
    if (color == RED){
        return "\033[0;31m";
    } else if (color == YELLOW){
        return "\033[1;33m";
    } else if (color == GREEN){
        return "\033[0;32m";
    } else {
        return "\033[0m";
    }
}

Timer::Timer(){}
Timer::~Timer(){}

void Timer::start(){
    gettimeofday(&begin_, NULL);
}
long Timer::stop(){
    gettimeofday(&end_, NULL);
    return (end_.tv_sec * 1e+6 + end_.tv_usec) - (begin_.tv_sec * 1e+6 + begin_.tv_usec);
}

void print_time(const std::string& func, long long ft_time, long long std_time){
    Printer::print(func + " >> ", false, Printer::GREEN);

    Printer::Color ft_color = (ft_time < std_time) ? Printer::YELLOW : Printer::RED;
    Printer::Color std_color = (ft_color == Printer::RED) ? Printer::YELLOW : Printer::RED;

    Printer::print("ft_time: ", false, Printer::GREEN);
    Printer::print(ft_time, false, ft_color);
    
    std::cout << "  ";

    Printer::print("std_time: ", false, Printer::GREEN);
    Printer::print(std_time, false, std_color);

    std::cout << "  ";

    if (ft_time && std_time){
        long long diff = std::max(ft_time, std_time) / std::min(ft_time, std_time);
        Printer::print("diff: ", false, Printer::GREEN);
        Printer::print(diff, true, Printer::YELLOW);
    } else {
        std::cout << std::endl;
    }
}

void my_assert(bool val){
    if (!val){
        throw std::exception();
    }
}

std::string my_to_string(size_t num){
    std::string result;
    
    while (num != 0){
        result.push_back('0' + num % 10);
        num /= 10;
    }

    std::reverse(result.begin(), result.end());
    return result;
}
