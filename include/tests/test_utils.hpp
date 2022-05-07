#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <sys/time.h>

const size_t max_val = 15000;

class Printer{
public:
    enum Color{
        DEFAULT,
        RED,
        YELLOW,
        GREEN
    };

    template <typename T>
    static void print(const T& str, bool new_line = true, Color color = DEFAULT){
        std::cout
            << color_to_string(color)
            << str
            << color_to_string(DEFAULT);
        if (new_line){
            std::cout << std::endl;
        }
    }

private:
    static std::string color_to_string(Color color);

};

class Timer{
public:
    Timer();
    ~Timer();

    void start();
    long stop();

private:
    timeval begin_;
    timeval end_;

};

void print_time(const std::string& func, long long ft_time, long long std_time);
void my_assert(bool val);
std::string my_to_string(size_t num);

#endif
