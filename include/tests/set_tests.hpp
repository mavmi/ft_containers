#ifndef SET_TESTS_HPP
#define SET_TESTS_HPP

#include <set>

#include "test_utils.hpp"
#include "../set.hpp"

namespace SET_TESTS {

typedef int Key;
typedef std::set<Key> std_set;
typedef ft::set<Key> ft_set;

void CONSTRUCTOR();
void ASSIGNMENT_OPERATOR();
void GET_ALLOCATOR();
void ITERATORS();
void INSERT();
void ERASE();
void FIND();
void BOUND();
void OPERATORS();

void RUN_SET_TESTS();

}

#endif
