#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <memory>
#include <utility>
#include <iostream>

#include "pair.hpp"
#include "iterator.hpp"

namespace ft{

namespace { // NODE

enum Color{
    RED,
    BLACK
};

template<typename T>
struct Node{
    Node() : value(T()), color(RED), left(NULL), right(NULL), parent(NULL) {

    }
    Node(const T& value) : value(value), color(RED),
                            left(NULL), right(NULL), parent(NULL) {

    }
    Node(const Node& another) 
        : value(another.value), color(another.color),
            left(another.left), right(another.right), parent(another.parent) {
        
    }
    Node(Node* left, Node* right, Node* parent, const T& value, Color color)
        : left(left), right(right), parent(parent), value(value), color(color) {
        
    }
    ~Node(){

    }

    Node& operator=(const Node& another){
        value = another.value;
        color = another.color;
        left = another.left;
        right = another.right;
        parent = another.parent;

        return *this;
    }

    T value;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
};

} // NODE

template< typename T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
class RedBlackTree;

namespace { // rbtree_iterator

template <typename T>
class rbtree_iterator{
public:
    typedef T                                                   value_type;
    typedef Node<value_type>                                    node_type;
    typedef size_t                                              difference_type;
    typedef value_type&                                         reference;
    typedef value_type*                                         pointer;
    typedef typename std::bidirectional_iterator_tag            iterator_category;

    rbtree_iterator(){
        root_ = NULL;
        base_ = NULL;
    }
    rbtree_iterator(const rbtree_iterator& another){
        root_ = another.root_;
        base_ = another.base_;
    }
    rbtree_iterator(node_type* base, node_type* root){
        root_ = root;
        base_ = base;
    }
    ~rbtree_iterator(){

    }

    rbtree_iterator& operator=(const rbtree_iterator& another){
        root_ = another.root_;
        base_ = another.base_;

        return *this;
    }
    bool operator==(const rbtree_iterator& another){
        return base_ == another.base_;
    }
    bool operator!=(const rbtree_iterator& another){
        return !(*this == another);
    }

    node_type* base() const {
        return base_;
    }

    reference operator*() const {
        if (base_ == NULL){
            return max_()->value;
        }

        return base_->value;
    }
    pointer operator->() const {
        if (base_ == NULL){
            return &max_()->value;
        }

        return &base_->value;
    }
    
    rbtree_iterator& operator++(){
        if (!base_) return *this;

        if (base_->right){
            base_ = base_->right;
            while (base_->left) base_ = base_->left;
            return *this;
        }
        while (base_->parent && base_ == base_->parent->right) base_ = base_->parent;
        base_ = base_->parent;

        return *this;
    }
    rbtree_iterator& operator--(){
        if (!base_){
            base_ = max_();
            return *this;
        }

        if (base_->left){
            base_ = base_->left;
            while (base_->right) base_ = base_->right;
            return *this;
        }
        while (base_->parent && base_ == base_->parent->left) base_ = base_->parent;
        base_ = base_->parent;

        return *this;
    }
    rbtree_iterator operator++(int){
        rbtree_iterator tmp = *this;
        if (!base_) return tmp;
        
        if (base_->right){
            base_ = base_->right;
            while (base_->left) base_ = base_->left;
            return tmp;
        }
        while (base_->parent && base_ == base_->parent->right) base_ = base_->parent;
        base_ = base_->parent;

        return tmp;
    }
    rbtree_iterator operator--(int){
        rbtree_iterator tmp = *this;
        if (!base_){
            base_ = max_();
            return tmp;
        }
        
        if (base_->left){
            base_ = base_->left;
            while (base_->right) base_ = base_->right;
            return tmp;
        }
        while (base_->parent && base_ == base_->parent->left) base_ = base_->parent;
        base_ = base_->parent;

        return tmp;
    }

private:
    node_type* root_;
    node_type* base_;

    node_type* max_() const {
        if (root_ == NULL) return NULL;

        node_type* ptr = root_;
        while (ptr->right){
            ptr = ptr->right;
        }

        return ptr;
    }

};

} // rbtree_iterator

namespace { // rbtree_reverse_iterator

template <typename T>
class rbtree_reverse_iterator{
public:
    typedef T                                                   value_type;
    typedef Node<value_type>                                    node_type;
    typedef size_t                                              difference_type;
    typedef value_type&                                         reference;
    typedef value_type*                                         pointer;
    typedef typename std::bidirectional_iterator_tag            iterator_category;

    rbtree_reverse_iterator(){
        root_ = NULL;
        base_ = NULL;
    }
    rbtree_reverse_iterator(const rbtree_reverse_iterator& another){
        root_ = another.root_;
        base_ = another.base_;
    }
    rbtree_reverse_iterator(node_type* base, node_type* root){
        root_ = root;
        base_ = base;
    }
    ~rbtree_reverse_iterator(){

    }

    rbtree_reverse_iterator& operator=(const rbtree_reverse_iterator& another){
        root_ = another.root_;
        base_ = another.base_;

        return *this;
    }
    bool operator==(const rbtree_reverse_iterator& another){
        return base_ == another.base_;
    }
    bool operator!=(const rbtree_reverse_iterator& another){
        return !(*this == another);
    }

    node_type* base() const {
        return base_;
    }

    reference operator*() const {
        if (base_ == NULL){
            return min_()->value;
        }

        return base_->value;
    }
    pointer operator->() const {
        if (base_ == NULL){
            return &min_()->value;
        }

        return &base_->value;
    }

    rbtree_reverse_iterator& operator--(){
        if (!base_){
            base_ = min_();
            return *this;
        }

        if (base_->right){
            base_ = base_->right;
            while (base_->left) base_ = base_->left;
            return *this;
        }
        while (base_->parent && base_ == base_->parent->right) base_ = base_->parent;
        base_ = base_->parent;

        return *this;
    }
    rbtree_reverse_iterator& operator++(){
        if (!base_) return *this;

        if (base_->left){
            base_ = base_->left;
            while (base_->right) base_ = base_->right;
            return *this;
        }
        while (base_->parent && base_ == base_->parent->left) base_ = base_->parent;
        base_ = base_->parent;

        return *this;
    }
    rbtree_reverse_iterator operator--(int){
        rbtree_reverse_iterator tmp = *this;
        if (!base_){
            base_ = min_();
            return tmp;
        }

        if (base_->right){
            base_ = base_->right;
            while (base_->left) base_ = base_->left;
            return tmp;
        }
        while (base_->parent && base_ == base_->parent->right) base_ = base_->parent;
        base_ = base_->parent;

        return tmp;
    }
    rbtree_reverse_iterator operator++(int){
        rbtree_reverse_iterator tmp = *this;
        if (!base_) return tmp;
        
        if (base_->left){
            base_ = base_->left;
            while (base_->right) base_ = base_->right;
            return tmp;
        }
        while (base_->parent && base_ == base_->parent->left) base_ = base_->parent;
        base_ = base_->parent;

        return tmp;
    }

private:
    node_type* root_;
    node_type* base_;

    node_type* min_() const {
        if (!root_ ) return NULL;

        node_type* ptr = root_;
        while (ptr->left){
            ptr = ptr->left;
        }
        
        return ptr;
    }

};

} // rbtree_reverse_iterator

template<typename T, class Compare, class Allocator>
class RedBlackTree{
public:
    typedef size_t                                                  size_type;
    typedef T                                                       value_type;
    typedef Node<T>                                                 node_type;
    typedef node_type*                                              node_ptr;
    typedef Allocator                                               elem_alloc_type;
    typedef rbtree_iterator<value_type>                             iterator;
    typedef rbtree_iterator<value_type>                             const_iterator;
    typedef rbtree_reverse_iterator<value_type>                     reverse_iterator;
    typedef rbtree_reverse_iterator<value_type>                     const_reverse_iterator;
    typedef typename Allocator::template rebind<node_type>::other   node_alloc_type;

    RedBlackTree(const elem_alloc_type& allocator = elem_alloc_type()) : allocator_(allocator) {
        root_ = NULL;
        size_ = 0;
    }
    RedBlackTree(const RedBlackTree& another) {
        root_ = copy_node_(another.root_);
        size_ = another.size_;
        allocator_ = another.allocator_;
    }
    template<class InputIt>
    RedBlackTree(InputIt first, InputIt last){
        root_ = NULL;
        size_ = 0;
        insert(first, last);
    }
    ~RedBlackTree(){
        delete_tree_(root_);
    }

    RedBlackTree& operator=(const RedBlackTree& another){
        root_ = copy_node_(another.root_);
        size_ = another.size_;
        allocator_ = another.allocator_;

        return *this;
    }

    node_alloc_type get_allocator() const {
        return allocator_;
    }

    iterator begin(){
        return iterator(min(root_), root_);
    }
    const_iterator begin() const{
        return const_iterator(min(root_), root_);
    }

    iterator end(){
        return iterator(NULL, root_);
    }
    const_iterator end() const{
        return const_iterator(NULL, root_);
    }

    reverse_iterator rbegin(){
        return reverse_iterator(max(root_), root_);
    }
    const_reverse_iterator rbegin() const{
        return const_reverse_iterator(max(root_), root_);
    }

    reverse_iterator rend(){
        return reverse_iterator(NULL, root_);
    }
    const_reverse_iterator rend() const{
        return reverse_iterator(NULL, root_);
    }

    bool empty() const {
        return size_ == 0;
    }
    size_type size() const {
        return size_;
    }
    size_type max_size() const {
        return allocator_.max_size();
    }

    void clear(){
        delete_tree_(root_);
        root_ = NULL;
        size_ = 0;
    }

    ft::pair<iterator, bool> insert(const value_type& value){
        node_ptr elem = allocator_.allocate(1);
        allocator_.construct(elem, value);
        if (!root_){
            root_ = elem;
            size_++;
            return ft::make_pair(iterator(elem, root_), true);
        }

        node_ptr ptr = root_;
        node_ptr tmp = root_;
        while (tmp){
            ptr = tmp;
            if (!Compare()(elem->value, ptr->value) && !Compare()(ptr->value, elem->value)){
                allocator_.destroy(elem);
                allocator_.deallocate(elem, 0);
                return ft::make_pair(end(), false);
            } else if (Compare()(elem->value, ptr->value)) {
                tmp = ptr->left;
            } else {
                tmp = ptr->right;
            }
        }

        elem->color = RED;
        elem->parent = ptr;
        if (Compare()(elem->value, ptr->value)) ptr->left = elem;
        else ptr->right = elem;

        insert_fixup_(elem);
        size_++;

        return ft::make_pair(iterator(elem, root_), true);
    }
    iterator insert(iterator, const value_type& value){
        return insert(value).first;
    }
    template<class InputIt>
    void insert(InputIt first, InputIt last){
        for (; first != last; first++){
            insert(*first);
        }
    }

    void erase(iterator iter){
        node_ptr z = iter.base();
        if (!z || !size_) return;

        node_ptr to_delete = z;
        node_ptr x = NULL;
        node_ptr y = z;
        Color y_orig_color = z->color;

        if (z->left == NULL){
            x = z->right;
            transplant_(z, z->right);
        } else if (z->right == NULL) {
            x = z->left;
            transplant_(z, z->left);
        } else {
            y = min(z->right);
            y_orig_color = y->color;
            x = y->right;
            if (y->parent != z){
                transplant_(y, y->right);
                y->right = z->right;
                z->right->parent = y;
            }
            transplant_(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (y_orig_color == BLACK){
            erase_fixup_(x);
        }

        allocator_.destroy(to_delete);
        allocator_.deallocate(to_delete, 0);
        size_--;

        if (size_ == 0) root_ = NULL;
    }
    void erase(iterator first, iterator last){
        for (; first != last; first++){
            erase(first);
        }
    }
    size_type erase(const value_type& value){
        iterator iter = find(value);
        if (iter == end()) return 0;
        erase(iter);
        return 1;
    }

    size_type count(const value_type& value) const{
        return (find(value) == end()) ? 0 : 1;
    }

    iterator find(const value_type& value){
        if (!root_) return end();

        node_type elem(value);
        node_ptr ptr = root_;
        while (ptr){
            if (!Compare()(elem.value, ptr->value) && !Compare()(ptr->value, elem.value)) return iterator(ptr, root_);
            if (Compare()(elem.value, ptr->value)) ptr = ptr->left;
            else ptr = ptr->right;
        }
        
        return (ptr) ? iterator(ptr, root_) : end();
    }
    const_iterator find(const value_type& value) const{
        if (!root_) return end();

        node_type elem(value);
        node_ptr ptr = root_;
        while (ptr){
            if (!Compare()(elem.value, ptr->value) && !Compare()(ptr->value, elem.value)) return const_iterator(ptr, root_);
            if (Compare()(elem.value, ptr->value)) ptr = ptr->left;
            else ptr = ptr->right;
        }
        
        return (ptr) ? const_iterator(ptr, root_) : end();
    }

    ft::pair<iterator, iterator> equal_range(const value_type& value){
        return ft::pair<iterator, iterator>(lower_bound(value), upper_bound(value));
    }
    ft::pair<const_iterator,const_iterator> equal_range(const value_type& value) const{
        return ft::pair<const_iterator, const_iterator>(lower_bound(value), upper_bound(value));
    }

    iterator lower_bound(const value_type& value){
        if (!root_) return end();
        
        for (iterator iter = begin(); iter != end(); iter++){
            if (!Compare()(*iter, value)) return iter;
        }

        return end();
    }
    const_iterator lower_bound(const value_type& value) const{
        if (!root_) return end();
        
        for (const_iterator iter = begin(); iter != end(); iter++){
            if (!Compare()(*iter, value)) return iter;
        }

        return end();
    }

    iterator upper_bound(const value_type& value){
        if (!root_) return end();
        
        for (iterator iter = begin(); iter != end(); iter++){
            if (Compare()(value, *iter) && !(!Compare()(value, *iter) && !Compare()(*iter, value))) return iter;
        }
        
        return end();
    }
    const_iterator upper_bound(const value_type& value) const{
        if (!root_) return end();
        
        for (const_iterator iter = begin(); iter != end(); iter++){
            if (Compare()(value, *iter) && !(!Compare()(value, *iter) && !Compare()(*iter, value))) return iter;
        }
        
        return end();
    }

    void print(){
        tabs_ = 0;
        print_(root_);
        std::cout << "_______________________________" << std::endl;
    }
    node_ptr root() const {
        return root_;
    }
    node_ptr min(node_ptr ptr) const {
        if (!ptr) return NULL;

        while (ptr->left){
            ptr = ptr->left;
        }

        return ptr;
    }
    node_ptr max(node_ptr ptr) const {
        if (!ptr) return NULL;

        while (ptr->right){
            ptr = ptr->right;
        }

        return ptr;
    }

private:
    int tabs_;
    size_type size_;
    node_ptr root_;
    node_alloc_type allocator_;

    node_ptr copy_node_(node_ptr another, node_ptr parent = NULL){
        if (another == NULL) return NULL;
        
        node_ptr new_one = allocator_.allocate(1);
        allocator_.construct(new_one, another->value);

        new_one->parent = parent;
        new_one->color = another->color;
        new_one->left = copy_node_(another->left, new_one);
        new_one->right = copy_node_(another->right, new_one);

        return new_one;
    }

    void transplant_(node_ptr u, node_ptr v){
        if (u->parent == NULL) root_ = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v) v->parent = u->parent;
    }

    void erase_fixup_(node_ptr x){
        if (!x) return;

        while (x != root_ && x->color == BLACK){
            if (x == x->parent->left){
                node_ptr w = x->parent->right;
                if (w->color == RED){
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotate_left_(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK){
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK){
                        w->left->color = BLACK;
                        w->color = RED;
                        rotate_right_(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotate_left_(x->parent);
                    x = root_;
                }
            } else {
                node_ptr w = x->parent->left;
                if (w->color == RED){
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotate_right_(x->parent);
                    w = x->parent->left;
                }
                if (w->left->color == BLACK && w->right->color == BLACK){
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK){
                        w->right->color = BLACK;
                        w->color = RED;
                        rotate_left_(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotate_right_(x->parent);
                    x = root_;
                }
            }
        }
        x->color = BLACK;
    }

    void rotate_left_(node_ptr X){
        if (!X || !X->right) return;

        node_ptr Y = X->right;
        node_ptr* X_from_parent;
        node_ptr parent = X->parent;
        if (!parent) X_from_parent = NULL;
        else X_from_parent = (X == parent->left) ? &parent->left : &parent->right;

        node_ptr a = X->left;
        node_ptr b = Y->left;
        node_ptr c = Y->right;

        if (parent) *X_from_parent = Y;
        else root_ = Y;
        Y->parent = parent;
        X->parent = Y;
        Y->left = X;
        Y->right = c;
        X->left = a;
        X->right = b;
        if (b) b->parent = X;
    }

    void rotate_right_(node_ptr Y){
        if (!Y || !Y->left) return;

        node_ptr X = Y->left;
        node_ptr* Y_from_parent;
        node_ptr parent = Y->parent;
        if (!parent) Y_from_parent = NULL;
        else Y_from_parent = (Y == parent->left) ? &parent->left : &parent->right;

        node_ptr a = X->left;
        node_ptr b = X->right;
        node_ptr c = Y->right;

        if (parent) *Y_from_parent = X;
        else root_ = X;
        X->parent = parent;
        Y->parent = X;
        X->right = Y;
        X->left = a;
        Y->left = b;
        Y->right = c;
        if (b) b->parent = Y;
    }

    void insert_fixup_(node_ptr z){
        if (!z || !z->parent || !z->parent->parent) return;

        while (z != root_ && z->parent->color == RED){
            if (z->parent == z->parent->parent->left){
                node_ptr y = z->parent->parent->right;

                if (y && y->color == RED){
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right){
                        z = z->parent;
                        rotate_left_(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotate_right_(z->parent->parent);
                }
            } else {
                node_ptr y = z->parent->parent->left;

                if (y && y->color == RED){
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left){
                        z = z->parent;
                        rotate_right_(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotate_left_(z->parent->parent);
                }
            }
        }

        root_->color = BLACK;
    }

    void delete_tree_(node_ptr node){
        if (!node) return;
        
        delete_tree_(node->left);
        delete_tree_(node->right);
        
        allocator_.destroy(node);
        allocator_.deallocate(node, 0);
    }
    
    void print_(node_ptr curr){
        if (!curr) return;
        tabs_ += 5;
        print_(curr->left);
        for (int i = 0; i < tabs_; i++) std::cout << " ";
        std::cout << curr->value << '(' <<  ((curr == root_) ? value_type() : curr->parent->value) << ", " << ((curr->color == RED) ? "RED" : "BLACK") << ')';
        std::cout << std::endl;
        print_(curr->right);
        tabs_ -= 5;
    }

};

}

#endif
