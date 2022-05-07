#include "../../include/tests/map_tests.hpp"

namespace MAP_TESTS{

std_map STD_input;
ft_map FT_input;

void CONSTRUCTOR(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    {
        timer.start();
        std_map STD;
        total_std_time += timer.stop();

        timer.start();
        ft_map FT;
        total_ft_time += timer.stop();
    }

    {
        timer.start();
        std_map STD(STD_input.begin(), STD_input.end());
        total_std_time += timer.stop();

        timer.start();
        ft_map FT(FT_input.begin(), FT_input.end());
        total_ft_time += timer.stop();

        my_assert(FT.size() == STD.size());
        std_map::iterator std_iter = STD.begin();
        ft_map::iterator ft_iter = FT.begin();
        while (ft_iter != FT.end()){
            my_assert(ft_iter->first == std_iter->first);
            my_assert(ft_iter->second == std_iter->second);
            ft_iter++;
            std_iter++;
        }
    }

    {
        ft_map FT(FT_input);
        my_assert(FT.size() == FT_input.size());
        ft_map::iterator ft_iter = FT.begin();
        ft_map::iterator ft_input_iter = FT_input.begin();
        while (ft_iter != FT.end()){
            my_assert(ft_iter->first == ft_input_iter->first);
            my_assert(ft_iter->second == ft_input_iter->second);
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
    std_map STD = STD_input;
    total_std_time += timer.stop();
    
    timer.start();
    ft_map FT = FT_input;
    total_ft_time += timer.stop();

    my_assert(FT.size() == FT_input.size());
    ft_map::iterator ft_iter = FT.begin();
    ft_map::iterator ft_input_iter = FT_input.begin();
    while (ft_iter != FT.end()){
        my_assert(ft_iter->first == ft_input_iter->first);
        my_assert(ft_iter->second == ft_input_iter->second);
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

void GETTER(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    std_map::iterator std_iter = STD_input.begin();

    while (std_iter != STD_input.end()){
        const Key& key = std_iter->first;

        {
            timer.start();
            const T& std_ = STD_input[key];
            total_std_time += timer.stop();

            timer.start();
            const T& ft_ = FT_input[key];
            total_ft_time += timer.stop();

            my_assert(ft_ == std_);
        }

        {
            timer.start();
            const T& std_ = STD_input.at(key);
            total_std_time += timer.stop();

            timer.start();
            const T& ft_ = FT_input.at(key);
            total_ft_time += timer.stop();

            my_assert(ft_ == std_);
        }

        my_assert(FT_input[std_iter->first] == std_iter->second);
        my_assert(FT_input.at(std_iter->first) == std_iter->second);

        std_iter++;
    }

    try{
        ft_map::iterator iter = FT_input.end();
        iter--;
        FT_input.at(iter->first * 100);
        my_assert(false);
    } catch (std::exception&){

    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void ITERATORS(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    {
        std_map::iterator std_iter = STD_input.begin();
        ft_map::iterator ft_iter = FT_input.begin();

        while (std_iter != STD_input.end()){
            my_assert(ft_iter->first == std_iter->first);
            my_assert(ft_iter->second == std_iter->second);
            
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
            my_assert(ft_iter->first == std_iter->first);
            my_assert(ft_iter->second == std_iter->second);
            
            timer.start();
            std_iter--;
            total_std_time += timer.stop();
            
            timer.start();
            ft_iter--;
            total_ft_time += timer.stop();
        }
    }

    {
        std_map::reverse_iterator std_iter = STD_input.rbegin();
        ft_map::reverse_iterator ft_iter = FT_input.rbegin();

        while (std_iter != STD_input.rend()){
            my_assert(ft_iter->first == std_iter->first);
            my_assert(ft_iter->second == std_iter->second);

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
            my_assert(ft_iter->first == std_iter->first);
            my_assert(ft_iter->second == std_iter->second);

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
        std_map STD(STD_input.begin(), STD_input.end());
        ft_map FT(FT_input.begin(), FT_input.end());

        for (int i = static_cast<int>(STD_input.size()); i < static_cast<int>(max_val) * 2; i++){
            timer.start();
            STD.insert(std::make_pair<Key, T>(i, my_to_string(i)));
            total_std_time += timer.stop();

            timer.start();
            FT.insert(ft::make_pair<Key, T>(i, my_to_string(i)));
            total_ft_time += timer.stop();
        }

        my_assert(FT.size() == STD.size());
        std_map::iterator std_iter = STD.begin();
        ft_map::iterator ft_iter = FT.begin();
        while (std_iter != STD.end()){
            my_assert(ft_iter->first == std_iter->first);
            my_assert(ft_iter->second == std_iter->second);
            std_iter++;
            ft_iter++;
        }
    }

    {
        std_map STD;
        ft_map FT;

        std_map::iterator std_begin = STD_input.begin();
        std_map::iterator std_second = STD_input.begin();
        std_map::iterator std_mid = STD_input.begin();
        std_map::iterator std_end = STD_input.end();

        ft_map::iterator ft_begin = FT_input.begin();
        ft_map::iterator ft_second = FT_input.begin();
        ft_map::iterator ft_mid = FT_input.begin();
        ft_map::iterator ft_end = FT_input.end();

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
        std_map::iterator std_iter = STD.begin();
        ft_map::iterator ft_iter = FT.begin();
        while (std_iter != STD.end()){
            my_assert(ft_iter->first == std_iter->first);
            my_assert(ft_iter->second == std_iter->second);
            std_iter++;
            ft_iter++;
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void ERASE(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    std_map STD(STD_input.begin(), STD_input.end());
    ft_map FT(FT_input.begin(), FT_input.end());

    for (size_t key = 10; key < 2000; key += 10){
        timer.start();
        STD.erase(key);
        total_std_time += timer.stop();

        timer.start();
        FT.erase(key);
        total_ft_time += timer.stop();

        my_assert(FT.size() == STD.size());
        std_map::iterator std_iter = STD.begin();
        ft_map::iterator ft_iter = FT.begin();
        while (std_iter != STD.end()){
            my_assert(ft_iter->first == std_iter->first);
            my_assert(ft_iter->second == std_iter->second);
            std_iter++;
            ft_iter++;
        }
    }

    for (int i = 0; i < 700; i++){
        std_map::iterator std_mid = STD.begin();
        ft_map::iterator ft_mid = FT.begin();

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
        std_map::iterator std_iter = STD.begin();
        ft_map::iterator ft_iter = FT.begin();
        while (std_iter != STD.end()){
            my_assert(ft_iter->first == std_iter->first);
            my_assert(ft_iter->second == std_iter->second);
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
        std_map::iterator std_iter = STD_input.find(i);
        total_std_time += timer.stop();

        timer.start();
        ft_map::iterator ft_iter = FT_input.find(i);
        total_ft_time += timer.stop();

        my_assert((std_iter == STD_input.end()) == (ft_iter == FT_input.end()));
        if (std_iter != STD_input.end()){
            my_assert(std_iter->first == ft_iter->first);
            my_assert(std_iter->second == ft_iter->second);
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void BOUND(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    for (int i = 500; i < 2000; i += 100){
        std_map::iterator std_lower = STD_input.lower_bound(i);
        std_map::iterator std_upper = STD_input.upper_bound(i);

        ft_map::iterator ft_lower = FT_input.lower_bound(i);
        ft_map::iterator ft_upper = FT_input.upper_bound(i);

        my_assert((std_lower == STD_input.end()) == (ft_lower == FT_input.end()));
        my_assert((std_upper == STD_input.end()) == (ft_upper == FT_input.end()));
        if (std_lower != STD_input.end()){
            my_assert(ft_lower->first == std_lower->first);
            my_assert(ft_lower->second == std_lower->second);
        }
        if (std_upper != STD_input.end()){
            my_assert(ft_upper->first == std_upper->first);
            my_assert(ft_upper->second == std_upper->second);
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void OPERATORS(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    std_map::iterator std_mid = STD_input.begin();
    ft_map::iterator ft_mid = FT_input.begin();

    for (size_t i = 0; i < STD_input.size() / 2; i++){
        std_mid++;
        ft_mid++;
    }

    std_map STD_1(STD_input.begin(), std_mid);
    std_map STD_2(std_mid, STD_input.end());

    ft_map FT_1(FT_input.begin(), ft_mid);
    ft_map FT_2(ft_mid, FT_input.end());

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

void RUN_MAP_TESTS(){
    Printer::print("\n\t=== MAP TESTS ===", true, Printer::YELLOW);

    for (size_t i = 0; i < max_val; i++){
        STD_input[i] = my_to_string(i);
        FT_input[i] = my_to_string(i);
    }

    CONSTRUCTOR();
    ASSIGNMENT_OPERATOR();
    GET_ALLOCATOR();
    GETTER();
    ITERATORS();
    INSERT();
    ERASE();
    FIND();
    BOUND();
    OPERATORS();
}

}
