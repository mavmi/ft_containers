#ifndef VECTOR_TESTS_HPP
#define VECTOR_TESTS_HPP

#include <vector>

#include "test_utils.hpp"
#include "../vector.hpp"

namespace VECTOR_TESTS{

template <typename T>
void CONSTRUCTOR(const T& value){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    {
        timer.start();
        std::vector<T> STD;
        total_std_time += timer.stop();

        timer.start();
        ft::vector<T> FT;
        total_ft_time += timer.stop();

        my_assert(FT.size() == STD.size());
            my_assert(FT.capacity() == STD.capacity());
    }

    {
        for (size_t size = 0; size < max_val; size += 500){
            timer.start();
            std::vector<T> STD(size);
            total_std_time += timer.stop();

            timer.start();
            ft::vector<T> FT(size);
            total_ft_time += timer.stop();

            my_assert(FT.size() == STD.size());
            my_assert(FT.capacity() == STD.capacity());
        }
    }

    {
        for (size_t size = 0; size < max_val; size += 500){
            std::vector<T> input(size, value);

            timer.start();
            std::vector<T> STD(input.begin(), input.end());
            total_std_time += timer.stop();

            timer.start();
            ft::vector<T> FT(input.begin(), input.end());
            total_ft_time += timer.stop();

            my_assert(FT.size() == STD.size());
            my_assert(FT.capacity() == STD.capacity());
        }
    }

    {
        for (size_t size = 0; size < max_val; size += 500){
            std::vector<T> input(size, value);
            std::vector<T> STD(input.begin(), input.end());
            ft::vector<T> FT(input.begin(), input.end());

            timer.start();
            std::vector<T> STD_cpy(STD);
            total_std_time += timer.stop();

            timer.start();
            ft::vector<T> FT_cpy(FT);
            total_ft_time += timer.stop();

            my_assert(FT.size() == STD.size());
            my_assert(FT.capacity() == STD.capacity());
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

template <typename T>
void ASSIGNMENT_OPERATOR(const T& value){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;
    
    {
        for (size_t size = 0; size < max_val; size += 500){
            std::vector<T> input(size, value);
            std::vector<T> STD(input.begin(), input.end());
            ft::vector<T> FT(input.begin(), input.end());

            timer.start();
            std::vector<T> STD_cpy = STD;
            total_std_time += timer.stop();

            timer.start();
            ft::vector<T> FT_cpy = FT;
            total_ft_time += timer.stop();

            my_assert(FT.size() == STD.size());
            my_assert(FT.capacity() == STD.capacity());
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

template <typename T>
void ASSIGN(const T& value){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;
    
    {
        for (size_t size = 0; size < max_val; size += 500){
            std::vector<T> STD;
            ft::vector<T> FT;

            timer.start();
            STD.assign(size, value);
            total_std_time += timer.stop();

            timer.start();
            FT.assign(size, value);
            total_ft_time += timer.stop();

            my_assert(FT.size() == STD.size());
            my_assert(FT.capacity() == STD.capacity());
        }
    }

    {
        for (size_t size = 0; size < max_val; size += 500){
            std::vector<T> input(size, value);
            std::vector<T> STD;
            ft::vector<T> FT;

            timer.start();
            STD.assign(input.begin(), input.end());
            total_std_time += timer.stop();

            timer.start();
            FT.assign(input.begin(), input.end());
            total_ft_time += timer.stop();

            my_assert(FT.size() == STD.size());
            my_assert(FT.capacity() == STD.capacity());
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

template <typename T>
void GET_ALLOCATOR(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;
    
    {
        std::vector<T> STD;
        ft::vector<T> FT;

        my_assert(FT.get_allocator() == STD.get_allocator());
        my_assert(FT.size() == STD.size());
        my_assert(FT.capacity() == STD.capacity());
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

template <typename T>
void GETTER(const T& value){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    {
        for (size_t size = 0; size < max_val; size += 500){
            std::vector<T> input(size, value);
            std::vector<T> STD(input.begin(), input.end());
            ft::vector<T> FT(input.begin(), input.end());

            my_assert(FT.size() == STD.size());
            my_assert(FT.capacity() == STD.capacity());
            
            for (size_t i = 0; i < FT.size(); i++){
                {
                    timer.start();
                    T& std_ = STD.at(i);
                    total_std_time += timer.stop();

                    timer.start();
                    T& ft_ = FT.at(i);
                    total_ft_time += timer.stop();

                    my_assert(ft_ == std_);
                }

                {
                    timer.start();
                    T& std_ = STD[i];
                    total_std_time += timer.stop();

                    timer.start();
                    T& ft_ = FT[i];
                    total_ft_time += timer.stop();

                    my_assert(ft_ == std_);
                }
            }

            try{
                FT.at(FT.size());
                my_assert(false);
            } catch (std::exception&){

            }

            try{
                FT.at(FT.size() + 1);
                my_assert(false);
            } catch (std::exception&){

            }

            try{
                FT.at(FT.size() * 2);
                my_assert(false);
            } catch (std::exception&){

            }
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

template <typename T>
void FRONT_BACK(const T& value){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    {
        for (size_t size = 10; size < max_val; size += 500){
            std::vector<T> input(size, value);
            std::vector<T> STD(input.begin(), input.end());
            ft::vector<T> FT(input.begin(), input.end());

            {   
                timer.start();
                T& std_front = STD.front();
                total_std_time += timer.stop();

                timer.start();
                T& ft_front = FT.front();
                total_ft_time += timer.stop();

                timer.start();
                T& std_back = STD.back();
                total_std_time += timer.stop();

                timer.start();
                T& ft_back = FT.back();
                total_ft_time += timer.stop();

                my_assert(ft_front == std_front);
                my_assert(ft_back == std_back);
            }

            my_assert(FT.size() == STD.size());
            my_assert(FT.capacity() == STD.capacity());
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

template <typename T>
void ITERATORS(const T& value){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    {
        for (size_t size = 10; size < max_val; size += 500){
            std::vector<T> input(size, value);
            std::vector<T> STD(input.begin(), input.end());
            ft::vector<T> FT(input.begin(), input.end());

            {
                typename std::vector<T>::iterator std_iter = STD.begin();
                typename ft::vector<T>::iterator ft_iter = FT.begin();

                my_assert(FT.size() == STD.size());
                my_assert(FT.capacity() == STD.capacity());
            
                while (std_iter != STD.end()){
                    timer.start();
                    T& std_ = *std_iter;
                    total_std_time += timer.stop();
                    
                    timer.start();
                    T& ft_ = *ft_iter;
                    total_ft_time += timer.stop();

                    my_assert(std_ == ft_);
                    std_iter++;
                    ft_iter++;
                }

                std_iter--;
                ft_iter--;
                while (true){
                    timer.start();
                    T& std_ = *std_iter;
                    total_std_time += timer.stop();
                    
                    timer.start();
                    T& ft_ = *ft_iter;
                    total_ft_time += timer.stop();

                    my_assert(std_ == ft_);
                    if (std_iter == STD.begin()){
                        break;
                    }

                    std_iter--;
                    ft_iter--;
                }
            }

            {
                typename std::vector<T>::reverse_iterator std_iter = STD.rbegin();
                typename ft::vector<T>::reverse_iterator ft_iter = FT.rbegin();

                my_assert(FT.size() == STD.size());
                my_assert(FT.capacity() == STD.capacity());
            
                while (std_iter != STD.rend()){
                    timer.start();
                    T& std_ = *std_iter;
                    total_std_time += timer.stop();
                    
                    timer.start();
                    T& ft_ = *ft_iter;
                    total_ft_time += timer.stop();

                    my_assert(std_ == ft_);
                    std_iter++;
                    ft_iter++;
                }

                std_iter--;
                ft_iter--;
                while (true){
                    timer.start();
                    T& std_ = *std_iter;
                    total_std_time += timer.stop();
                    
                    timer.start();
                    T& ft_ = *ft_iter;
                    total_ft_time += timer.stop();

                    my_assert(std_ == ft_);
                    if (std_iter == STD.rbegin()){
                        break;
                    }

                    std_iter--;
                    ft_iter--;
                }
            }
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

template <typename T>
void RESERVE(const T& value){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    {
        for (size_t size = 0; size < max_val; size += 500){
            std::vector<T> input(size, value);
            std::vector<T> STD(input.begin(), input.end());
            ft::vector<T> FT(input.begin(), input.end());

            for (size_t cap = 0; cap < 1000; cap += 10){
                timer.start();
                STD.reserve(cap);
                total_std_time += timer.stop();

                timer.start();
                FT.reserve(cap);
                total_ft_time += timer.stop();

                my_assert(FT.empty() == STD.empty());
                my_assert(FT.size() == STD.size());
                my_assert(FT.capacity() == STD.capacity());
            }

            STD.clear();
            FT.clear();
            my_assert(FT.empty() == STD.empty());
            my_assert(FT.size() == STD.size());
            my_assert(FT.capacity() == STD.capacity());
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

template <typename T>
void INSERT(const T& value){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    {
        for (size_t size = 0; size < max_val; size += 500){
            std::vector<T> input(size, value);
            std::vector<T> STD(input.begin(), input.end());
            ft::vector<T> FT(input.begin(), input.end());

            timer.start();
            STD.insert(STD.begin(), value);
            STD.insert(STD.begin() + STD.size() / 2, value);
            STD.insert(STD.end(), value);
            total_std_time += timer.stop();

            timer.start();
            FT.insert(FT.begin(), value);
            FT.insert(FT.begin() + FT.size() / 2, value);
            FT.insert(FT.end(), value);
            total_ft_time += timer.stop();

            my_assert(FT.empty() == STD.empty());
            my_assert(FT.size() == STD.size());
            my_assert(FT.capacity() == STD.capacity());
            for (size_t i = 0; i < FT.size(); i++){
                my_assert(FT[i] == STD[i]);
            }
        }
    }

    {
        for (size_t size = 0; size < max_val; size += 500){
            std::vector<T> input(size, value);
            std::vector<T> STD(input.begin(), input.end());
            ft::vector<T> FT(input.begin(), input.end());

            for (size_t count = 1000; count < 5000; count += 1000){
                timer.start();
                STD.insert(STD.begin(), count, value);
                STD.insert(STD.begin() + STD.size() / 2, count, value);
                STD.insert(STD.end(), count, value);
                total_std_time += timer.stop();

                timer.start();
                FT.insert(FT.begin(), count, value);
                FT.insert(FT.begin() + FT.size() / 2, count, value);
                FT.insert(FT.end(), count, value);
                total_ft_time += timer.stop();

                my_assert(FT.empty() == STD.empty());
                my_assert(FT.size() == STD.size());
                my_assert(FT.capacity() == STD.capacity());
                for (size_t i = 0; i < FT.size(); i++){
                    my_assert(FT[i] == STD[i]);
                }
            }
        }
    }

    {
        for (size_t size = 0; size < max_val; size += 500){
            std::vector<T> input(size, value);
            std::vector<T> STD(input.begin(), input.end());
            ft::vector<T> FT(input.begin(), input.end());

            size_t count = input.size() / 2;
            timer.start();
            STD.insert(STD.begin(), input.begin(), input.begin() + count);
            STD.insert(STD.begin() + STD.size() / 2, input.begin(), input.begin() + count);
            STD.insert(STD.end(), input.begin(), input.begin() + count);
            total_std_time += timer.stop();

            timer.start();
            FT.insert(FT.begin(), input.begin(), input.begin() + count);
            FT.insert(FT.begin() + FT.size() / 2, input.begin(), input.begin() + count);
            FT.insert(FT.end(), input.begin(), input.begin() + count);
            total_ft_time += timer.stop();

            my_assert(FT.empty() == STD.empty());
            my_assert(FT.size() == STD.size());
            my_assert(FT.capacity() == STD.capacity());
            for (size_t i = 0; i < FT.size(); i++){
                my_assert(FT[i] == STD[i]);
            }
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

template <typename T>
void ERASE(const T& value){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    {
        for (size_t size = 1000; size < max_val; size += 1000){
            std::vector<T> input(size, value);
            std::vector<T> STD(input.begin(), input.end());
            ft::vector<T> FT(input.begin(), input.end());

            timer.start();
            STD.erase(STD.begin());
            STD.erase(STD.begin() + STD.size() / 2);
            STD.erase(STD.end() - 1);
            STD.erase(STD.begin(), STD.begin() + STD.size() / 2);
            total_std_time += timer.stop();

            timer.start();
            FT.erase(FT.begin());
            FT.erase(FT.begin() + FT.size() / 2);
            FT.erase(FT.end() - 1);
            FT.erase(FT.begin(), FT.begin() + FT.size() / 2);
            total_ft_time += timer.stop();

            my_assert(FT.empty() == STD.empty());
            my_assert(FT.size() == STD.size());
            my_assert(FT.capacity() == STD.capacity());
            for (size_t i = 0; i < FT.size(); i++){
                my_assert(FT[i] == STD[i]);
            }
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

template <typename T>
void PUSH_BACK(const T& value){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    std::vector<T> STD;
    ft::vector<T> FT;

    for (size_t i = 0; i < max_val; i++){
        timer.start();
        STD.push_back(value);
        total_std_time += timer.stop();

        timer.start();
        FT.push_back(value);
        total_ft_time += timer.stop();

        my_assert(FT.empty() == STD.empty());
        my_assert(FT.size() == STD.size());
        my_assert(FT.capacity() == STD.capacity());
        for (size_t i = 0; i < FT.size(); i++){
            my_assert(FT[i] == STD[i]);
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

template <typename T>
void POP_BACK(const T& value){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    std::vector<T> STD;
    ft::vector<T> FT;

    for (size_t i = 0; i < max_val; i++){
        STD.push_back(value);
        FT.push_back(value);
    }

    while (!FT.empty()) {
        timer.start();
        STD.pop_back();
        total_std_time += timer.stop();

        timer.start();
        FT.pop_back();
        total_ft_time += timer.stop();

        my_assert(FT.empty() == STD.empty());
        my_assert(FT.size() == STD.size());
        my_assert(FT.capacity() == STD.capacity());
        for (size_t i = 0; i < FT.size(); i++){
            my_assert(FT[i] == STD[i]);
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

template <typename T>
void RESIZE(){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    std::vector<T> STD;
    ft::vector<T> FT;

    for (size_t i = 0; i < max_val; i++){
        timer.start();
        STD.resize(i);
        total_std_time += timer.stop();

        timer.start();
        FT.resize(i);
        total_ft_time += timer.stop();

        my_assert(FT.empty() == STD.empty());
        my_assert(FT.size() == STD.size());
        my_assert(FT.capacity() == STD.capacity());
        for (size_t i = 0; i < FT.size(); i++){
            my_assert(FT[i] == STD[i]);
        }
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

template <typename T>
void OPERATORS(const T& value){
    Timer timer;
    long long total_ft_time = 0, total_std_time = 0;

    for (size_t i = 0; i < 1000; i++){
        std::vector<T> input(i, value);

        std::vector<T> STD1(input.begin(), input.begin() + input.size() / 2);
        std::vector<T> STD2(input.begin() + input.size() / 2, input.end());
        std::vector<T> STD3(input.begin(), input.end());

        ft::vector<T> FT1(input.begin(), input.begin() + input.size() / 2);
        ft::vector<T> FT2(input.begin() + input.size() / 2, input.end());
        ft::vector<T> FT3(input.begin(), input.end());

        my_assert((STD1 == STD2) == (FT1 == FT2));
        my_assert((STD1 == STD3) == (FT1 == FT3));
        my_assert((STD3 == STD2) == (FT3 == FT2));

        my_assert((STD1 != STD2) == (FT1 != FT2));
        my_assert((STD1 != STD3) == (FT1 != FT3));
        my_assert((STD3 != STD2) == (FT3 != FT2));

        my_assert((STD1 < STD2) == (FT1 < FT2));
        my_assert((STD1 < STD3) == (FT1 < FT3));
        my_assert((STD3 < STD2) == (FT3 < FT2));

        my_assert((STD1 <= STD2) == (FT1 <= FT2));
        my_assert((STD1 <= STD3) == (FT1 <= FT3));
        my_assert((STD3 <= STD2) == (FT3 <= FT2));

        my_assert((STD1 > STD2) == (FT1 > FT2));
        my_assert((STD1 > STD3) == (FT1 > FT3));
        my_assert((STD3 > STD2) == (FT3 > FT2));

        my_assert((STD1 >= STD2) == (FT1 >= FT2));
        my_assert((STD1 >= STD3) == (FT1 >= FT3));
        my_assert((STD3 >= STD2) == (FT3 >= FT2));
    }

    print_time(__FUNCTION__, total_ft_time, total_std_time);
}

void RUN_VECTOR_TESTS();

}

#endif
