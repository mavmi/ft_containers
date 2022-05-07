#ifndef STACK_TESTS_HPP
#define STACK_TESTS_HPP

#include <stack>
#include <string>

#include "test_utils.hpp"
#include "../stack.hpp"

namespace STACK_TESTS{

typedef std::string T;
typedef std::stack<T> std_stack;
typedef ft::stack<T> ft_stack;

void CONSTRUCTOR();
void TOP_POP_PUSH();
void OPERATORS();

void RUN_STACK_TESTS();
    
}

#endif
