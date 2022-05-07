#ifndef PAIR_HPP
#define PAIR_HPP

#include <iostream>

namespace ft{

template<class T1, class T2>
class pair{
public:
    typedef T1  first_type;
    typedef T2  second_type;

    pair() : first(first_type()), second(second_type()) {}
    pair(const T1& first, const T2& second) : first(first), second(second) {}
    template<class U1, class U2>
    pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
    ~pair(){}

    pair& operator=(const pair& other){
        first = other.first;
        second = other.second;
        
        return *this;
    }

    first_type first;
    second_type second;
};

template<class T1, class T2>
bool operator==(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<class T1, class T2>
bool operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){
    return !(lhs == rhs);
}

template<class T1, class T2>
bool operator<(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){
    if (lhs.first < rhs.first) return true;
    if (rhs.first < lhs.first) return false;
    return lhs.second < rhs.second;
}

template<class T1, class T2>
bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){
    return !(rhs < lhs);
}

template<class T1, class T2>
bool operator>(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){
    return !(lhs <= rhs);
}

template<class T1, class T2>
bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){
    return !(lhs < rhs);
}

template<class T1, class T2>
ft::pair<T1, T2> make_pair(T1 t, T2 u){
    return ft::pair<T1, T2>(t, u);
}

}

#endif
