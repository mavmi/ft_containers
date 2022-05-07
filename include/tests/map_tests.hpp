#ifndef MAP_TESTS_HPP
#define MAP_TESTS_HPP

#include <map>

#include "test_utils.hpp"
#include "../map.hpp"

namespace MAP_TESTS{

typedef int Key;
typedef std::string T;
typedef std::map<Key, T> std_map;
typedef ft::map<Key, T> ft_map;

void CONSTRUCTOR();
void ASSIGNMENT_OPERATOR();
void GET_ALLOCATOR();
void GETTER();
void ITERATORS();
void INSERT();
void ERASE();
void FIND();
void BOUND();
void OPERATORS();

void RUN_MAP_TESTS();

}

#endif
