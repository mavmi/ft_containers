#include "../../include/tests/set_tests.hpp"

namespace SET_TESTS {

std_set STD_input;
ft_set FT_input;

void CONSTRUCTOR(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    {
        timer.start();
        std_set STD;
        total_std_time += timer.stop();

        timer.start();
        ft_set FT;
        total_ft_time += timer.stop();
    }

    {
        timer.start();
        std_set STD(STD_input.begin(), STD_input.end());
        total_std_time += timer.stop();

        timer.start();
        ft_set FT(FT_input.begin(), FT_input.end());
        total_ft_time += timer.stop();

        my_assert(FT.size() == STD.size());
        std_set::iterator std_iter = STD.begin();
        ft_set::iterator ft_iter = FT.begin();
        while (ft_iter != FT.end()){
            my_assert(*ft_iter == *std_iter);
            ft_iter++;
            std_iter++;
        }
    }

    {
        ft_set FT(FT_input);
        my_assert(FT.size() == FT_input.size());
        ft_set::iterator ft_iter = FT.begin();
        ft_set::iterator ft_input_iter = FT_input.begin();
        while (ft_iter != FT.end()){
            my_assert(*ft_iter == *ft_input_iter);
            ft_iter++;
            ft_input_iter++;
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void ASSIGNMENT_OPERATOR(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    timer.start();
    std_set STD = STD_input;
    total_std_time += timer.stop();
    
    timer.start();
    ft_set FT = FT_input;
    total_ft_time += timer.stop();

    my_assert(FT.size() == FT_input.size());
    ft_set::iterator ft_iter = FT.begin();
    ft_set::iterator ft_input_iter = FT_input.begin();
    while (ft_iter != FT.end()){
        my_assert(*ft_iter == *ft_input_iter);
        ft_iter++;
        ft_input_iter++;
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void GET_ALLOCATOR(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    my_assert(FT_input.get_allocator() == STD_input.get_allocator());

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void ITERATORS(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    {
        std_set::iterator std_iter = STD_input.begin();
        ft_set::iterator ft_iter = FT_input.begin();

        while (std_iter != STD_input.end()){
            my_assert(*ft_iter == *std_iter);
            
            timer.start();
            std_iter++;
            total_std_time += timer.stop();

            timer.start();
            ft_iter++;
            total_ft_time += timer.stop();
        }

        std_iter--;
        ft_iter--;

        while (std_iter != STD_input.begin()){
            my_assert(*ft_iter == *std_iter);
            
            timer.start();
            std_iter--;
            total_std_time += timer.stop();
            
            timer.start();
            ft_iter--;
            total_ft_time += timer.stop();
        }
    }

    {
        std_set::reverse_iterator std_iter = STD_input.rbegin();
        ft_set::reverse_iterator ft_iter = FT_input.rbegin();

        while (std_iter != STD_input.rend()){
            my_assert(*ft_iter == *std_iter);

            timer.start();
            std_iter++;
            total_std_time += timer.stop();

            timer.start();
            ft_iter++;
            total_ft_time += timer.stop();
        }

        std_iter--;
        ft_iter--;

        while (std_iter != STD_input.rbegin()){
            my_assert(*ft_iter == *std_iter);

            timer.start();
            std_iter--;
            total_std_time += timer.stop();

            timer.start();
            ft_iter--;
            total_ft_time += timer.stop();
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void INSERT(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    {
        std_set STD(STD_input.begin(), STD_input.end());
        ft_set FT(FT_input.begin(), FT_input.end());

        for (int i = static_cast<int>(STD_input.size()); i < static_cast<int>(max_val) * 2; i++){
            timer.start();
            STD.insert(i);
            total_std_time += timer.stop();

            timer.start();
            FT.insert(i);
            total_ft_time += timer.stop();
        }

        my_assert(FT.size() == STD.size());
        std_set::iterator std_iter = STD.begin();
        ft_set::iterator ft_iter = FT.begin();
        while (std_iter != STD.end()){
            my_assert(*ft_iter == *std_iter);
            std_iter++;
            ft_iter++;
        }
    }

    {
        std_set STD;
        ft_set FT;

        std_set::iterator std_begin = STD_input.begin();
        std_set::iterator std_second = STD_input.begin();
        std_set::iterator std_mid = STD_input.begin();
        std_set::iterator std_end = STD_input.end();

        ft_set::iterator ft_begin = FT_input.begin();
        ft_set::iterator ft_second = FT_input.begin();
        ft_set::iterator ft_mid = FT_input.begin();
        ft_set::iterator ft_end = FT_input.end();

        std_second++;
        ft_second++;
        for (size_t i = 0; i < STD_input.size() / 2; i++){
            std_mid++;
            ft_mid++;
        }

        timer.start();
        STD.insert(std_begin, std_second);
        STD.insert(std_begin, std_mid);
        STD.insert(std_second, std_end);
        total_std_time += timer.stop();

        timer.start();
        FT.insert(ft_begin, ft_second);
        FT.insert(ft_begin, ft_mid);
        FT.insert(ft_second, ft_end);
        total_ft_time += timer.stop();

        my_assert(FT.size() == STD.size());
        std_set::iterator std_iter = STD.begin();
        ft_set::iterator ft_iter = FT.begin();
        while (std_iter != STD.end()){
            my_assert(*ft_iter == *std_iter);
            std_iter++;
            ft_iter++;
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void ERASE(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    std_set STD(STD_input.begin(), STD_input.end());
    ft_set FT(FT_input.begin(), FT_input.end());

    for (size_t key = 10; key < 2000; key += 10){
        timer.start();
        STD.erase(key);
        total_std_time += timer.stop();

        timer.start();
        FT.erase(key);
        total_ft_time += timer.stop();

        my_assert(FT.size() == STD.size());
        std_set::iterator std_iter = STD.begin();
        ft_set::iterator ft_iter = FT.begin();
        while (std_iter != STD.end()){
            my_assert(*ft_iter == *std_iter);
            std_iter++;
            ft_iter++;
        }
    }

    for (int i = 0; i < 700; i++){
        std_set::iterator std_mid = STD.begin();
        ft_set::iterator ft_mid = FT.begin();

        for (size_t j = 0; j < STD.size() / 2; j++){
            std_mid++;
            ft_mid++;
        }

        timer.start();
        STD.erase(std_mid);
        total_std_time += timer.stop();

        timer.start();
        FT.erase(ft_mid);
        total_ft_time += timer.stop();

        my_assert(FT.size() == STD.size());
        std_set::iterator std_iter = STD.begin();
        ft_set::iterator ft_iter = FT.begin();
        while (std_iter != STD.end()){
            my_assert(*ft_iter == *std_iter);
            std_iter++;
            ft_iter++;
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void FIND(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    for (int i = -10000; i < 10000; i++){
        timer.start();
        std_set::iterator std_iter = STD_input.find(i);
        total_std_time += timer.stop();

        timer.start();
        ft_set::iterator ft_iter = FT_input.find(i);
        total_ft_time += timer.stop();

        my_assert((std_iter == STD_input.end()) == (ft_iter == FT_input.end()));
        if (std_iter != STD_input.end()){
            my_assert(*std_iter == *ft_iter);
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void BOUND(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    for (int i = 500; i < 2000; i += 100){
        std_set::iterator std_lower = STD_input.lower_bound(i);
        std_set::iterator std_upper = STD_input.upper_bound(i);

        ft_set::iterator ft_lower = FT_input.lower_bound(i);
        ft_set::iterator ft_upper = FT_input.upper_bound(i);

        my_assert((std_lower == STD_input.end()) == (ft_lower == FT_input.end()));
        my_assert((std_upper == STD_input.end()) == (ft_upper == FT_input.end()));
        if (std_lower != STD_input.end()){
            my_assert(*ft_lower == *std_lower);
        }
        if (std_upper != STD_input.end()){
            my_assert(*ft_upper == *std_upper);
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void OPERATORS(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    std_set::iterator std_mid = STD_input.begin();
    ft_set::iterator ft_mid = FT_input.begin();

    for (size_t i = 0; i < STD_input.size() / 2; i++){
        std_mid++;
        ft_mid++;
    }

    std_set STD_1(STD_input.begin(), std_mid);
    std_set STD_2(std_mid, STD_input.end());

    ft_set FT_1(FT_input.begin(), ft_mid);
    ft_set FT_2(ft_mid, FT_input.end());

    my_assert((STD_input == STD_1) == (FT_input == FT_1));
    my_assert((STD_input == STD_2) == (FT_input == FT_2));
    my_assert((STD_2 == STD_1) == (FT_2 == FT_1));

    my_assert((STD_input != STD_1) == (FT_input != FT_1));
    my_assert((STD_input != STD_2) == (FT_input != FT_2));
    my_assert((STD_2 != STD_1) == (FT_2 != FT_1));

    my_assert((STD_input < STD_1) == (FT_input < FT_1));
    my_assert((STD_input < STD_2) == (FT_input < FT_2));
    my_assert((STD_2 < STD_1) == (FT_2 < FT_1));

    my_assert((STD_input <= STD_1) == (FT_input <= FT_1));
    my_assert((STD_input <= STD_2) == (FT_input <= FT_2));
    my_assert((STD_2 <= STD_1) == (FT_2 <= FT_1));

    my_assert((STD_input > STD_1) == (FT_input > FT_1));
    my_assert((STD_input > STD_2) == (FT_input > FT_2));
    my_assert((STD_2 > STD_1) == (FT_2 > FT_1));

    my_assert((STD_input >= STD_1) == (FT_input >= FT_1));
    my_assert((STD_input >= STD_2) == (FT_input >= FT_2));
    my_assert((STD_2 >= STD_1) == (FT_2 >= FT_1));

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void RUN_SET_TESTS(){
    Printer::print("\n\t=== SET TESTS ===", true, Printer::YELLOW);

    for (size_t i = 0; i < max_val; i++){
        STD_input.insert(i);
        FT_input.insert(i);
    }

    CONSTRUCTOR();
    ASSIGNMENT_OPERATOR();
    GET_ALLOCATOR();
    ITERATORS();
    INSERT();
    ERASE();
    FIND();
    BOUND();
    OPERATORS();
}

}