#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>

#include "enable_if.hpp"
#include "iterator.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"

namespace ft {

namespace { // vector_iterator

template <typename T>
class vector_iterator{
public:
    typedef typename ft::iterator_traits<T*>::value_type        value_type;
    typedef typename ft::iterator_traits<T*>::reference         reference;
    typedef typename ft::iterator_traits<T*>::pointer           pointer;
    typedef typename ft::iterator_traits<T*>::difference_type   difference_type;
    typedef typename std::random_access_iterator_tag            iterator_category;

    vector_iterator(){
        base_ = pointer();
    }
    vector_iterator(const vector_iterator& another){
        base_ = another.base_;
    }
    vector_iterator(pointer ptr){   
        base_ = ptr;
    }
    ~vector_iterator(){

    }

    vector_iterator& operator=(const vector_iterator& another){
        base_ = another.base_;
        return *this;
    }

    pointer base() const {
        return base_;
    }

    reference operator*() const {
        return *base_;
    }
    pointer operator->() const {
        return base_;
    }

    value_type operator[](difference_type n) const{
        return next(base_, n);
    }

    vector_iterator& operator++(){
        ++base_;
        return *this;
    }
    vector_iterator& operator--(){
        --base_;
        return *this;
    }
    vector_iterator operator++(int){
        vector_iterator tmp = *this;
        
        ++base_;
        return tmp;
    }
    vector_iterator operator--(int){
        vector_iterator tmp = *this;
        
        --base_;
        return tmp;
    }
    vector_iterator operator+(difference_type n) const{
        return vector_iterator(next(base_, n));
    }
    vector_iterator operator-(difference_type n) const{
        return vector_iterator(prev(base_, n));
    }
    vector_iterator& operator+=(difference_type n){
        base_ = next(base_, n);
        return *this;
    }
    vector_iterator& operator-=(difference_type n){
        base_ = prev(base_, n);
        return *this;
    }
    difference_type operator-(const vector_iterator& another){
        return base_ - another.base_;
    }

private:
    pointer base_;

};

template<typename T1, typename T2>
bool operator==(const vector_iterator<T1>& lhs,
                 const vector_iterator<T2>& rhs){
    return lhs.base() == rhs.base();
}
template<typename T1, typename T2>
bool operator!=(const vector_iterator<T1>& lhs,
                 const vector_iterator<T2>& rhs){
    return lhs.base() != rhs.base();
}
template<typename T1, typename T2>
bool operator<(const vector_iterator<T1>& lhs,
                const vector_iterator<T2>& rhs){
    return lhs.base() < rhs.base();
}
template<typename T1, typename T2>
bool operator<=(const vector_iterator<T1>& lhs,
                 const vector_iterator<T2>& rhs){
    return lhs.base() <= rhs.base();
}
template<typename T1, typename T2>
bool operator>(const vector_iterator<T1>& lhs,
                const vector_iterator<T2>& rhs){
    return lhs.base() > rhs.base();
}
template<typename T1, typename T2>
bool operator>=(const vector_iterator<T1>& lhs,
                 const vector_iterator<T2>& rhs){
    return lhs.base() >= rhs.base();
}

} //vector_iterator

namespace { // vector_reverse_iterator

template <typename Iterator>
class vector_reverse_iterator{
public:
    typedef typename ft::iterator_traits<Iterator>::value_type        value_type;
    typedef typename ft::iterator_traits<Iterator>::reference         reference;
    typedef typename ft::iterator_traits<Iterator>::pointer           pointer;
    typedef typename ft::iterator_traits<Iterator>::difference_type   difference_type;
    typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;

    vector_reverse_iterator(){
        base_ = Iterator();
    }
    vector_reverse_iterator(const vector_reverse_iterator& another){
        base_ = another.base();
    }
    vector_reverse_iterator(Iterator iter){
        base_ = iter;
    }
    ~vector_reverse_iterator(){

    }

    vector_reverse_iterator& operator=(const vector_reverse_iterator& another){
        base_ = another.base();
        return *this;
    }

    Iterator base() const {
        return base_;
    }

    reference operator*() const {
        return *base_;
    }
    pointer operator->() const {
        return base_;
    }

    value_type operator[](difference_type n) const{
        return prev(base_, n);
    }

    vector_reverse_iterator& operator++(){
        --base_;
        return *this;
    }
    vector_reverse_iterator& operator--(){
        ++base_;
        return *this;
    }
    vector_reverse_iterator operator++(int){
        vector_reverse_iterator tmp = *this;
        
        --base_;
        return tmp;
    }
    vector_reverse_iterator operator--(int){
        vector_reverse_iterator tmp = *this;
        
        ++base_;
        return tmp;
    }
    vector_reverse_iterator operator+(difference_type n) const{
        return vector_reverse_iterator(prev(base_, n));
    }
    vector_reverse_iterator operator-(difference_type n) const{
        return vector_reverse_iterator(next(base_, n));
    }
    vector_reverse_iterator& operator+=(difference_type n){
        base_ = prev(base_, n);
        return *this;
    }
    vector_reverse_iterator& operator-=(difference_type n){
        base_ = next(base_, n);
        return *this;
    }
    difference_type operator-(const vector_reverse_iterator& another){
        return base_ - another.base_;
    }

private:
    Iterator base_;

};

template<typename Iterator1, typename Iterator2>
bool operator==(const vector_reverse_iterator<Iterator1>& lhs,
                 const vector_reverse_iterator<Iterator2>& rhs){
    return lhs.base() == rhs.base();
}
template<typename Iterator1, typename Iterator2>
bool operator!=(const vector_reverse_iterator<Iterator1>& lhs,
                 const vector_reverse_iterator<Iterator2>& rhs){
    return lhs.base() != rhs.base();
}
template<typename Iterator1, typename Iterator2>
bool operator<(const vector_reverse_iterator<Iterator1>& lhs,
                const vector_reverse_iterator<Iterator2>& rhs){
    return lhs.base() < rhs.base();
}
template<typename Iterator1, typename Iterator2>
bool operator<=(const vector_reverse_iterator<Iterator1>& lhs,
                 const vector_reverse_iterator<Iterator2>& rhs){
    return lhs.base() <= rhs.base();
}
template<typename Iterator1, typename Iterator2>
bool operator>(const vector_reverse_iterator<Iterator1>& lhs,
                const vector_reverse_iterator<Iterator2>& rhs){
    return lhs.base() > rhs.base();
}
template<typename Iterator1, typename Iterator2>
bool operator>=(const vector_reverse_iterator<Iterator1>& lhs,
                 const vector_reverse_iterator<Iterator2>& rhs){
    return lhs.base() >= rhs.base();
}

} // vector_reverse_iterator

template < typename T, typename Allocator = std::allocator<T> >
class vector {
public:
    typedef typename Allocator::size_type                           size_type;
    typedef typename Allocator::value_type                          value_type;
    typedef typename Allocator::pointer                             pointer;
    typedef typename Allocator::const_pointer                       const_pointer;
    typedef typename Allocator::reference                           reference;
    typedef typename Allocator::const_reference                     const_reference;
    typedef typename ft::vector_iterator<value_type>                iterator;
    typedef typename ft::vector_iterator<value_type>                const_iterator;
    typedef typename ft::vector_reverse_iterator<iterator>          reverse_iterator;
    typedef typename ft::vector_reverse_iterator<const_iterator>    const_reverse_iterator;
    typedef typename iterator::difference_type                      difference_type;
    
    // Constructs an empty container with the given allocator alloc
    vector(const Allocator& alloc = Allocator())
        : allocator_(alloc){
        size_ = 0;
        capacity_ = 0;
        data_ = NULL;
    }
    // Constructs the container with [count] copies of elements with value [value]
    explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
                : allocator_(alloc){
        size_ = count;
        capacity_ = count;
        data_ = allocator_.allocate(capacity_);

        for (size_type i = 0; i < size_; i++){
            allocator_.construct(data_ + i, value);
        }
    }
    // Constructs the container with the contents of the range [first, last).
    template <class InputIt>
    vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(),
            typename ft::enable_if<!ft::is_integral<InputIt>::val, InputIt>::type* = NULL) : allocator_(alloc){
        size_type dist = std::distance(first, last);
        
        size_ = dist;
        capacity_ = dist;
        data_ = allocator_.allocate(capacity_);

        InputIt it;
        size_type i;
        for (it = first, i = 0; it != last; it++, i++){
            allocator_.construct(data_ + i, *it);
        }
    }
    // Copy constructor. Constructs the container with the copy of the contents of other
    vector(const vector& other){
        size_ = other.size_;
        capacity_ = other.capacity_;
        allocator_ = other.allocator_;
        data_ = allocator_.allocate(capacity_);

        for (size_type i = 0; i < other.size_; i++){
            allocator_.construct(data_ + i, *(other.data_ + i));
        }
    }

    ~vector(){
        for (size_type i = 0; i < size(); i++){
            allocator_.destroy(data_ + i);
        }
        allocator_.deallocate(data_, 0);
    }

    vector& operator=(const vector& other){
        destroy_data_();

        size_ = other.size_;
        capacity_ = other.capacity_;
        allocator_ = other.allocator_;
        data_ = allocator_.allocate(other.capacity_);

        for (size_type i = 0; i < other.size_; i++){
            allocator_.construct(data_ + i, *(other.data_ + i));
        }

        return *this;
    }

    // Replaces the contents with count copies of value [value]
    void assign(size_type count, const T& value){
        destroy_elements_();
        if (count > capacity_){
            if (capacity_ == 0 || capacity_ * 2 < count){
                reserve(count);
            } else {
                reserve(capacity_ * 2);
            }
        }

        size_ = count;
        for (size_type i = 0; i < size_; i++){
            allocator_.construct(data_ + i, value);
        }
    }
    // Replaces the contents with copies of those in the range [first, last)
    template <typename InputIt>
    void assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::val, InputIt>::type* = NULL){
        size_type dist = std::distance(first, last);
        
        destroy_elements_();
        if (dist > capacity_){
            if (capacity_ == 0 || capacity_ * 2 < dist){
                reserve(dist);
            } else {
                reserve(capacity_ * 2);
            }
        }

        size_ = dist;
        InputIt it;
        size_type i;
        for (it = first, i = 0; it != last; it++, i++){
            allocator_.construct(data_ + i, *it);
        }
    }

    // Returns the allocator associated with the container
    Allocator get_allocator() const {
        return allocator_;
    }

    // Returns a reference to the element at specified location pos, with bounds checking.
    // If pos is not within the range of the container, an exception of type std::out_of_range is thrown
    T& at(size_type pos){
        if (pos >= size_)
            throw OutOfRangeException("Bad position");
        return *(data_ + pos);
    }
    const T& at(size_type pos) const{
        if (pos >= size_)
            throw OutOfRangeException("Bad position");
        return *(data_ + pos);
    }

    // Returns a reference to the element at specified location pos. No bounds checking is performed
    T& operator[](size_type pos){
        return *(data_ + pos);
    }
    const T& operator[](size_type pos) const{
        return *(data_ + pos);
    }

    // Returns a reference to the first element in the container.
    // Calling front on an empty container is undefined
    T& front(){
        return *data_;
    }
    const T& front() const{
        return *data_;
    }

    // Returns a reference to the last element in the container.
    // Calling back on an empty container causes undefined behavior
    T& back(){
        if (size_ == 0){
            return *data_;
        }
        return *(data_ + size_ - 1);
    }
    const T& back() const{
        if (size_ == 0){
            return *data_;
        }
        return *(data_ + size_ - 1);
    }

    // Returns Pointer to the underlying array serving as element storage.
    // The Pointer is such that range [data(); data() + size()) is always a valid range,
    // even if the container is empty (data() is not dereferenceable in that case).
    T* data(){
        return data_;
    }
    const T* data() const{
        return data_;
    }

    // Returns an iterator to the first element of the vector.
    // If the vector is empty, the returned iterator will be equal to end().
    iterator begin() {
        return iterator(data_);
    }
    const_iterator begin() const{
        return const_iterator(data_);
    }

    // Returns an iterator to the element following the last element of the vector.
    // This element acts as a placeholder; attempting to access it results in undefined behavior.
    iterator end(){
        return iterator(data_ + size_);
    }
    const_iterator end() const{
        return const_iterator(data_ + size_);
    }

    // Returns a reverse iterator to the first element of the reversed vector.
    // It corresponds to the last element of the non-reversed vector.
    // If the vector is empty, the returned iterator is equal to rend().
    reverse_iterator rbegin(){
        if (size_ == 0){
            return rend();
        }
        return reverse_iterator(iterator(end() - 1));
    }
    const_reverse_iterator rbegin() const{
        if (size_ == 0){
            return rend();
        }
        return const_reverse_iterator(iterator(end() - 1));
    }

    // Returns a reverse iterator to the element following the last element of the reversed vector.
    // It corresponds to the element preceding the first element of the non-reversed vector.
    // This element acts as a placeholder, attempting to access it results in undefined behavior.
    reverse_iterator rend(){
        return reverse_iterator(iterator(begin() - 1));
    }
    const_reverse_iterator rend() const{
        return const_reverse_iterator(iterator(begin() - 1));
    }

    // Checks if the container has no elements, i.e. whether begin() == end()
    bool empty() const{
        return size_ == 0;
    }

    //Returns the number of elements in the container, i.e. std::distance(begin(), end())
    size_type size() const{
        return size_;
    }

    // Returns the maximum number of elements the container is able to hold due to system or library implementation limitations,
    // i.e. std::distance(begin(), end()) for the largest container.
    size_type max_size() const{
        return allocator_.max_size();
    }

    // Increase the capacity of the vector to a value that's greater or equal to new_cap.
    // If new_cap is greater than the current capacity(), new storage is allocated, otherwise the function does nothing.
    void reserve(size_type new_cap){
        if (new_cap <= capacity_){
            return;
        }
        
        size_type new_size = size_;
        T* new_data = allocator_.allocate(new_cap);
        for (size_type i = 0; i < size_; i++){
            allocator_.construct(new_data + i, *(data_ + i));
        }

        destroy_data_();
        data_ = new_data;
        size_ = new_size;
        capacity_ = new_cap;
    }

    // Returns the number of elements that the container has currently allocated space for.
    size_type capacity() const{
        return capacity_;
    }

    // Erases all elements from the container. After this call, size() returns zero.
    void clear(){
        destroy_elements_();
    }

    // Inserts value before pos
    iterator insert(iterator iter_pos, const T& value){
        size_type numeric_pos = std::distance(begin(), iter_pos);

        size_type count = 1;
        if (size_ + count > capacity_){
            if (capacity_ == 0 || capacity_ * 2 < count){
                reserve(count);
            } else {
                reserve(capacity_ * 2);
            }
        }
        iter_pos = begin() + numeric_pos;
        move_backward_(iter_pos, count);
        iter_pos = begin() + numeric_pos;

        allocator_.construct(iter_pos.base(), value);
        size_ += count;
        return iter_pos;
    }
    // Inserts count copies of the value before pos
    iterator insert(iterator iter_pos, size_type count, const T& value){
        if (!validate_iterator_values_(value, count)){
            throw std::exception();
        }

        size_type numeric_pos = std::distance(begin(), iter_pos);

        if (size_ + count > capacity_){
            if (capacity_ == 0 || capacity_ * 2 < size_ + count){
                reserve(size_ + count);
            } else {
                reserve(capacity_ * 2);
            }
        }
        iter_pos = begin() + numeric_pos;
        move_backward_(iter_pos, count);
        for (size_type i = 0; i < count; ++i){
            allocator_.construct(iter_pos.base() + i, value);
        }
        size_ += count;

        return iter_pos;
    }
    // Inserts elements from range [first, last) before pos
    template<typename InputIt>
    iterator insert(iterator iter_pos, InputIt first, InputIt last,
                        typename ft::enable_if<!ft::is_integral<InputIt>::val, InputIt>::type* = NULL){
        if (!validate_iterator_values_(first, last)){
            throw std::exception();
        }
        
        size_type numeric_pos = std::distance(begin(), iter_pos);

        size_type count = std::distance(first, last);
        if (size_ + count > capacity_){
            if (capacity_ == 0 || capacity_ * 2 < count){
                reserve(count);
            } else {
                reserve(capacity_ * 2);
            }
        }
        iter_pos = begin() + numeric_pos;
        move_backward_(iter_pos, count);

        size_type i;
        InputIt it;
        for (it = first, i = 0; it != last; ++it, ++i){
            allocator_.construct(iter_pos.base() + i, *it);
        }
        size_ += count;

        return iter_pos;
    }

    // Removes the element at pos
    iterator erase(iterator iter_pos){
        size_type d = static_cast<size_type>(std::distance(begin(), iter_pos));

        for (size_type i = d; i < size_ - 1; ++i){
            allocator_.destroy(data_ + i);
            allocator_.construct(data_ + i, *(data_ + i + 1));
        }
        size_--;
        allocator_.destroy(data_ + size_ - 1);

        return iterator(data_ + d);
    }
    // Removes the elements in the range [first, last)
    iterator erase(iterator first, iterator last){
        difference_type start = std::distance(begin(), first);
        difference_type elems_to_copy = std::distance(last, end());
        bool is_last_end = last == end();

        while (first != last){
            allocator_.destroy(first.base());
            first++;
        }

        size_type i = start;
        while (last != end()){
            allocator_.destroy(data_ + i);
            allocator_.construct(data_ + i, *last);
            i++;
            last++;
        }
        for (size_type i = start + elems_to_copy; i < size_; i++)
            allocator_.destroy(data_ + i);
        size_ = start + elems_to_copy;
        
        return is_last_end ? end() : iterator(data_ + start);
    }

    // The new element is initialized as a copy of value
    void push_back(const T& value){
        insert(end(), value);
    }

    // Removes the last element of the container
    void pop_back(){
        if (size_ != 0){
            erase(end() - 1);
        }
    }

    // Additional copies of value are appended
    void resize(size_type count, T value = T()){
        if (count == size_){
            return;
        } else if (count > size_){
            if (capacity_ < count){
                if (capacity_ == 0 || capacity_ * 2 < count){
                    reserve(count);
                } else {
                    reserve(capacity_ * 2);
                }
            }
            for (size_type i = size_; i < count; i++){
                allocator_.construct(data_ + i, value);
            }
        } else {
            for (size_type i = count; i < size_; i++){
                allocator_.destroy(data_ + i);
            }
        }
        size_ = count;
    }

    // Exchanges the contents of the container with those of other. 
    // Does not invoke any move, copy, or swap operations on individual elements.
    // All iterators and references remain valid. The past-the-end iterator is invalidated.
    void swap(vector& other){
        T* tmp_data = data_;
        size_type tmp_size = size_;
        size_type tmp_capacity = capacity_;
        Allocator tmp_allocator = allocator_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        allocator_ = other.allocator_;

        other.data_ = tmp_data;
        other.size_ = tmp_size;
        other.capacity_ = tmp_capacity;
        other.allocator_ = tmp_allocator;
    }

private:
    size_type capacity_;
    size_type size_;
    T* data_;
    Allocator allocator_;

    class OutOfRangeException : public std::out_of_range {
    public:
        OutOfRangeException(const std::string& str)
            : std::out_of_range(str) {

        }

        virtual const char* what() const throw() {
            return "Out of bounds exception!";
        }
    };

    // Move elements backward from position [pos] [count] times
    void move_backward_(iterator pos, size_type count){
        if (pos == end()){
            return;
        }

        iterator it = end() - 1;
        while (1){
            allocator_.construct(it.base() + count, *it);
            allocator_.destroy(it.base());
            if (it == pos){
                break;
            }
            it--;
        }
    }

    // Move elements forward form position [pos] [count] times
    void move_forward_(iterator pos, size_type count){
        if (pos == end()){
            return;
        }

        for (iterator it = pos; it != end(); ++it){
            allocator_.construct(it.base() - count, *it);
            allocator_.destroy(it.base());
        }
    }

    // Destroy all elements and set size_ to 0
    void destroy_elements_(){
        if (data_ == NULL){
            return;
        }

        for (size_type i = 0; i < size_; i++){
            allocator_.destroy(data_ + i);
        }
                
        size_ = 0;
    }

    // Destroy all elements and delete [data_].
    // Set size_, capacity_ and data_ to zero
    void destroy_data_(){
        if (data_ == NULL){
            return;
        }

        destroy_elements_();
        allocator_.deallocate(data_, 0);

        capacity_ = 0;
        data_ = NULL;
    }

    template <typename Iterator>
    bool validate_iterator_values_(Iterator first, Iterator last){
        bool return_value = true;
        pointer buffer = allocator_.allocate(std::distance(first, last));

        int i;
        Iterator iter;
        try {
            for (iter = first, i = 0; iter != last; iter++, i++){
                allocator_.construct(buffer + i, *iter);
            }
        } catch (...) {
            return_value = false;
        }
        
        i--;
        while (i >= 0){
            allocator_.destroy(buffer + i--);
        }
        allocator_.deallocate(buffer, 0);
        return return_value;
    }

    bool validate_iterator_values_(const T& value, size_type count){
        bool return_value = true;
        pointer buffer = allocator_.allocate(count);

        size_type i;
        try {
            for (i = 0; i < count; i++){
                allocator_.construct(buffer + i, value);
            }
        } catch (...) {
            return_value = false;
        }
        
        if (i != 0){
            i--;
            while (true){
                allocator_.destroy(buffer + i);
                if (i == 0){
                    break;
                }
                i--;
            }
        }
        allocator_.deallocate(buffer, 0);
        return return_value;
    }
};

template <class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs){
    if (lhs.size() != rhs.size()){
        return false;
    }

    for (size_t i = 0; i < lhs.size(); i++){
        if (lhs[i] != rhs[i]){
            return false;
        }
    }

    return true;
}

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs){
    return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs){
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs){
    return lhs < rhs || !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs){
    return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs){
    return rhs < lhs || !(lhs < rhs);
}

template< class T, class Alloc >
void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs){
    lhs.swap(rhs);
}

} // namespace ft

#endif
