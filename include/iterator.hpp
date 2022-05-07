#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

#include "iterator.hpp"

namespace ft{

struct output_iterator_tag {};
struct input_iterator_tag {};
struct forward_iterator_tag : public output_iterator_tag, public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename Category, typename T, typename Distance = std::ptrdiff_t, typename Pointer = T*, typename Reference = T&>
struct iterator{
    typedef T           value_type;
    typedef Reference   reference;
    typedef Pointer     pointer;
    typedef Distance    difference_type;
    typedef Category    iterator_category;
};

template <typename Iterator>
struct iterator_traits{
    typedef typename Iterator::value_type           value_type;
    typedef typename Iterator::reference            reference;
    typedef typename Iterator::pointer              pointer;
    typedef typename Iterator::difference_type      difference_type;
    typedef typename Iterator::iterator_category    iterator_category;
};

template <typename T>
struct iterator_traits<T*>{
    typedef T                           value_type;
    typedef T&                          reference;
    typedef T*                          pointer;
    typedef std::ptrdiff_t              difference_type;
    typedef random_access_iterator_tag  iterator_category;
};


namespace implementation{

template <typename Iterator, typename Category>
typename iterator_traits<Iterator>::difference_type _distance(Iterator begin, Iterator end, Category&){
    typename iterator_traits<Iterator>::difference_type dist = 0;

    while (begin != end){
        begin++;
        dist++;
    }

    return dist;
}

template <typename Iterator>
typename iterator_traits<Iterator>::difference_type _distance(Iterator begin, Iterator end, random_access_iterator_tag&){
    return end - begin;
}

template <typename Iterator, typename Category>
void _advance(Iterator& it, int n, Category&){
    if (n < 0){
        return;
    }

    while (n != 0){
        it++;
        n--;
    }
}

template <typename Iterator>
void _advance(Iterator& it, int n, bidirectional_iterator_tag&){
    while (n != 0){
        if (n < 0){
            it--;
            n++;
        } else {
            it++;
            n--;
        }
    }
}

template <typename Iterator>
void _advance(Iterator& it, int n, random_access_iterator_tag&){
    it += n;
}

} // namespace implementation


template <typename Iterator>
typename iterator_traits<Iterator>::difference_type distance(Iterator begin, Iterator end){
    typename iterator_traits<Iterator>::iterator_category category;
    return implementation::_distance(begin, end, category);
}

template <typename Iterator>
void advance(Iterator& it, int n){
    typename iterator_traits<Iterator>::iterator_category category;
    implementation::_advance(it, n, category);
}

template <typename Iterator>
Iterator next(Iterator it, int n = 1){
    Iterator it_cpy = it;

    advance(it_cpy, n);
    return it_cpy;
}

template <typename Iterator>
Iterator prev(Iterator it, int n = 1){
    n *= -1;
    Iterator it_cpy = it;

    advance(it_cpy, n);
    return it_cpy;
}


} // namespace ft

#endif
