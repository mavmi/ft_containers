#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft{

template< class InputIt1, class InputIt2 >
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2){
    size_t dist_1 = std::distance(first1, last1);
    size_t dist_2 = std::distance(first2, last2);

    InputIt1 it_1;
    InputIt2 it_2;

    for (it_1 = first1, it_2 = first2; it_1 != last1 && it_2 != last2; it_1++, it_2++){
        if (*it_1 < *it_2){
            return true;
        }
        if (*it_2 < *it_1){
            return false;
        }
    }

    return (dist_1 < dist_2) ? true : false;
}

template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp){
    size_t dist_1 = std::distance(first1, last1);
    size_t dist_2 = std::distance(first2, last2);

    InputIt1 it_1;
    InputIt2 it_2;

    for (it_1 = first1, it_2 = first2; it_1 != last1 && it_2 != last2; it_1++, it_2++){
        if (comp(*it_1, *it_2)){
            return true;
        }
        if (comp(*it_2, *it_1)){
            return false;
        }
    }

    return (dist_1 < dist_2) ? true : false;
}

}

#endif
