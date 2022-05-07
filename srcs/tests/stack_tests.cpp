#include "../../include/tests/stack_tests.hpp"

namespace STACK_TESTS{

void CONSTRUCTOR(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    {
        timer.start();
        std_stack STD;
        total_std_time += timer.stop();

        timer.start();
        ft_stack FT;
        total_ft_time += timer.stop();
    }

    {
        std_stack STD;
        ft_stack FT;

        for (int i = 0; i < 100000; i++){
            STD.push(my_to_string(i));
            FT.push(my_to_string(i));
        }
        timer.start();
        std_stack STD_cpy(STD);
        total_std_time += timer.stop();

        timer.start();
        ft_stack FT_cpy(FT);
        total_ft_time += timer.stop();

        my_assert(FT_cpy.size() == STD_cpy.size());
        while (!FT_cpy.empty()){
            my_assert(FT_cpy.top() == STD_cpy.top());
            FT_cpy.pop();
            STD_cpy.pop();
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void TOP_POP_PUSH(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    std_stack STD;
    ft_stack FT;

    for (int i = 0; i < 100000; i++){
        STD.push(my_to_string(i));
        FT.push(my_to_string(i));
    }

    timer.start();
    std_stack STD_cpy = STD;
    total_std_time += timer.stop();

    timer.start();
    ft_stack FT_cpy = FT;
    total_ft_time += timer.stop();

    my_assert(FT_cpy.size() == STD_cpy.size());
    while (FT_cpy.size()){
        my_assert(FT_cpy.top() == STD_cpy.top());
        FT_cpy.pop();
        STD_cpy.pop();
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void OPERATORS(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    std_stack STD1, STD2, STD3;
    ft_stack FT1, FT2, FT3;

    for (int i = 0; i < 50000; i++){
        STD1.push(my_to_string(i));
        FT1.push(my_to_string(i));

        STD2.push(my_to_string(i));
        FT2.push(my_to_string(i));
    }

    for (int i = 30000; i < 100000; i++){
        STD1.push(my_to_string(i));
        FT1.push(my_to_string(i));

        STD3.push(my_to_string(i));
        FT3.push(my_to_string(i));
    }

    my_assert((STD1 == STD2) == (FT1 == FT2));
    my_assert((STD3 == STD2) == (FT3 == FT2));
    my_assert((STD3 == STD1) == (FT3 == FT1));

    my_assert((STD1 != STD2) == (FT1 != FT2));
    my_assert((STD3 != STD2) == (FT3 != FT2));
    my_assert((STD3 != STD1) == (FT3 != FT1));

    my_assert((STD1 < STD2) == (FT1 < FT2));
    my_assert((STD3 < STD2) == (FT3 < FT2));
    my_assert((STD3 < STD1) == (FT3 < FT1));

    my_assert((STD1 <= STD2) == (FT1 <= FT2));
    my_assert((STD3 <= STD2) == (FT3 <= FT2));
    my_assert((STD3 <= STD1) == (FT3 <= FT1));

    my_assert((STD1 > STD2) == (FT1 > FT2));
    my_assert((STD3 > STD2) == (FT3 > FT2));
    my_assert((STD3 > STD1) == (FT3 > FT1));

    my_assert((STD1 >= STD2) == (FT1 >= FT2));
    my_assert((STD3 >= STD2) == (FT3 >= FT2));
    my_assert((STD3 >= STD1) == (FT3 >= FT1));

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void RUN_STACK_TESTS(){
    Printer::print("\n\t=== STACK TESTS ===", true, Printer::YELLOW);

    CONSTRUCTOR();
    TOP_POP_PUSH();
    OPERATORS();
}

}
