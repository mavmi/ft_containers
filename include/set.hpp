#ifndef SET_HPP
#define SET_HPP

#include <memory>
#include <functional>

#include "red_black_tree.hpp"
#include "lexicographical_compare.hpp"

namespace ft {

template<
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
> 
class set{
public:
    typedef Key                                                     key_type;
    typedef Key                                                     value_type;
    typedef size_t                                                  size_type;
    typedef ptrdiff_t                                               difference_type;
    typedef Compare                                                 key_compare;
    typedef Compare                                                 value_compare;
    typedef Allocator                                               allocator_type;
    typedef value_type&                                             reference;
    typedef const value_type&                                       const_reference;
    typedef typename Allocator::pointer                             pointer;
    typedef typename Allocator::const_pointer                       const_pointer;
    typedef ft::RedBlackTree<value_type, value_compare, Allocator>  tree_type;
    typedef typename tree_type::iterator                            iterator;
    typedef typename tree_type::const_iterator                      const_iterator;
    typedef typename tree_type::reverse_iterator                    reverse_iterator;
    typedef typename tree_type::const_reverse_iterator              const_reverse_iterator;

    set(){}
    explicit set(const Compare& comp, const Allocator& alloc = Allocator()){
        (void)comp; (void)alloc;
    }
    template< class InputIt >
    set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
        : tree_(first, last) {
        (void)comp; (void)alloc;
    }
    set(const set& other){
        tree_ = other.tree_;
    }
    ~set(){}

    set& operator=(const set& another){
        clear();
        tree_ = another.tree_;

        return *this;
    }

    // Returns the allocator associated with the container.
    allocator_type get_allocator() const{
        return tree_.get_allocator();
    }

    // Returns an iterator to the first element of the set.
    // If the set is empty, the returned iterator will be equal to end().
    iterator begin(){
        return tree_.begin();
    }
    const_iterator begin() const{
        return tree_.begin();
    }

    // Returns an iterator to the element following the last element of the set.
    // This element acts as a placeholder; attempting to access it results in undefined behavior.
    iterator end(){
        return tree_.end();
    }
    const_iterator end() const{
        return tree_.end();
    }

    // Returns a reverse iterator to the first element of the reversed set. 
    // It corresponds to the last element of the non-reversed set.
    // If the set is empty, the returned iterator is equal to rend().
    reverse_iterator rbegin(){
        return tree_.rbegin();
    }
    const_reverse_iterator rbegin() const{
        return tree_.rbegin();
    }

    // Returns a reverse iterator to the element following the last element of the reversed set. 
    // It corresponds to the element preceding the first element of the non-reversed set. 
    // This element acts as a placeholder, attempting to access it results in undefined behavior.
    reverse_iterator rend(){
        return tree_.rend();
    }
    const_reverse_iterator rend() const{
        return tree_.rend();
    }

    // Checks if the container has no elements, i.e. whether begin() == end().
    bool empty() const{
        return tree_.empty();
    }
    // Returns the number of elements in the container, i.e. std::distance(begin(), end()).
    size_type size() const{
        return tree_.size();
    }
    // Returns the maximum number of elements the container is able to hold due to system or
    // library implementation limitations, i.e. std::distance(begin(), end()) for the largest container.
    size_type max_size() const{
        return tree_.max_size();
    }

    // Erases all elements from the container. After this call, size() returns zero.
    // Invalidates any references, pointers, or iterators referring to contained elements. 
    // Any past-the-end iterator remains valid.
    void clear(){
        tree_.clear();
    }

    // Inserts value.
    // Returns a pair consisting of an iterator to the inserted element (or to the element that prevented the insertion) 
    // and a bool value set to true if the insertion took place.
    ft::pair<iterator,bool> insert(const value_type& value){
        return tree_.insert(value);
    }
    // Inserts value in the position as close as possible to hint.
    // Returns an iterator to the inserted element, or to the element that prevented the insertion.
    iterator insert(iterator hint, const value_type& value){
        return tree_.insert(hint, value);
    }
    // Inserts elements from range [first, last). 
    // If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted
    template<class InputIt>
    void insert(InputIt first, InputIt last){
        tree_.insert(first, last);
    }

    // Removes the element at pos
    void erase(iterator pos){
        tree_.erase(pos);
    }
    // Removes the elements in the range [first; last), which must be a valid range in *this.
    void erase(iterator first, iterator last){
        tree_.erase(first, last);
    }
    // Removes the element (if one exists) with the key equivalent to key.
    size_type erase(const Key& key){
        return tree_.erase(key);
    }

    // Exchanges the contents of the container with those of other. 
    // Does not invoke any move, copy, or swap operations on individual elements.
    void swap(set& other){
        tree_type tmp = tree_;
        tree_ = other.tree_;
        other.tree_ = tmp;
    }

    // Returns the number of elements with key that compares equivalent to the specified argument,
    // which is either 1 or 0 since this container does not allow duplicates.
    size_type count(const Key& key) const{
        return tree_.count(key);
    }

    // Finds an element with key equivalent to key.
    iterator find(const Key& key){
        return tree_.find(key);
    }
    const_iterator find(const Key& key) const{
        return tree_.find(key);
    }

    // Compares the keys to key.
    ft::pair<iterator,iterator> equal_range(const Key& key){
        return tree_.equal_range(key);
    }
    ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const{
        return tree_.equal_range(key);
    }

    // Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
    iterator lower_bound(const Key& key){
        return tree_.lower_bound(key);
    }
    const_iterator lower_bound(const Key& key) const{
        return tree_.lower_bound(key);
    }

    // Returns an iterator pointing to the first element that is greater than key.
    iterator upper_bound(const Key& key){
        return tree_.upper_bound(key);
    }
    const_iterator upper_bound(const Key& key) const{
        return tree_.upper_bound(key);
    }

    // Returns the function object that compares the keys, 
    // which is a copy of this container's constructor argument comp. It is the same as value_comp.
    key_compare key_comp() const{
        return Compare();
    }

    // Returns the function object that compares the values. It is the same as key_comp.
    value_compare value_comp() const{
        return value_compare();
    } 

private:
    tree_type tree_;

};

// Checks if the contents of lhs and rhs are equal, that is, 
// they have the same number of elements and 
// each element in lhs compares equal with the element in rhs at the same position.
template<class Key, class Compare, class Alloc>
bool operator==(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs){
    if (lhs.size() != rhs.size()) return false;

    for (typename ft::set<Key,Compare,Alloc>::iterator i1 = lhs.begin(), i2 = rhs.begin();
                i1 != lhs.end() && i2 != rhs.end(); i1++, i2++){
        if (!(*i1 == *i2)) return false;
    }
    return true;
}

template<class Key, class Compare, class Alloc>
bool operator!=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs){
    return !(lhs == rhs);
}

// Compares the contents of lhs and rhs lexicographically. 
// The comparison is performed by a function equivalent to std::lexicographical_compare. 
// This comparison ignores the set's ordering Compare.
template<class Key, class Compare, class Alloc>
bool operator<(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs){
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<class Key, class Compare, class Alloc>
bool operator<=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs){
    return lhs < rhs || lhs == rhs;
}

template<class Key, class Compare, class Alloc>
bool operator>(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs){
    return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template<class Key, class Compare, class Alloc>
bool operator>=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs){
    return rhs < lhs || rhs == lhs;
}

// Specializes the std::swap algorithm for std::set. Swaps the contents of lhs and rhs. Calls lhs.swap(rhs).
template<class Key, class T, class Compare, class Alloc>
void swap(ft::set<Key,Compare,Alloc>& lhs, ft::set<Key,Compare,Alloc>& rhs){
    lhs.swap(rhs);
}

} // namespace ft

#endif
