//
// Created by yulong on 3/31/17.
//

#ifndef BYL_TEMPLATE_LIBRARY_AVL_TREE_H
#define BYL_TEMPLATE_LIBRARY_AVL_TREE_H
#include "byl_bst.hpp"
#include <cstddef>
namespace byl {
template<typename T> struct avl_tree;

template<typename T>
struct avl_node {
    typedef T value_type;
    typedef size_t size_type;;
    friend struct avl_tree<T>;
    typedef avl_node * node_ptr;
    node_ptr left, right, parent;
    T m_data;
    int height;
    size_type n_size;
    avl_node(const value_type& v = value_type(), int h = 0)
            : left(NULL), right(NULL), parent(NULL)
            , m_data(v), height(h), n_size(1) {}
};


template<typename T>
struct avl_tree : public bst<T, avl_node> {
    typedef T value_type;
    typedef bst<T, avl_node> base_tree;
    typedef avl_node<T> node_type;
    typedef avl_node<T> *node_pointer;
    typedef typename bst<T, avl_node>::size_type size_type;

    inline int max(int a, int b) {
        return (a > b) ? a : b;
    }
    inline int height(node_pointer p) {
        return p? p->height : (-1);
    }
    inline void update_height(node_pointer p) {
        p->height = 1 + max(height(p->left), height(p->right));
    }
    void update_height_above(node_pointer p) {
        if(!p) return;
        while(p->parent) {
            update_height(p->parent);
            p = p->parent;
        }
    }

    inline int bal_fac(const node_pointer p) {
        return (height(p->left) - height(p->right));
    }

    inline bool is_balenced(const node_pointer p) {
        int fac = bal_fac(p);
        return (-2 < fac && fac < 2);
    }

    inline node_pointer connect34(
            node_pointer a, node_pointer b, node_pointer c,
            node_pointer t0, node_pointer t1, node_pointer t2, node_pointer t3) {
        a->left = t0; if(t0) t0->parent = a;
        a->right = t1; if(t1) t1->parent = a; update_height(a); update_size(a);

        c->left = t2; if(t2) t2->parent = c;
        c->right = t3; if(t3) t3->parent = c; update_height(c); update_size(c);

        b->left = a; a->parent = b;
        b->right = c; c->parent = b; update_height(b); update_size(b);

        return b;
    }
    inline bool is_lchild(node_pointer p) {
        return (p->parent->left == p);
    }
    inline bool is_rchild(node_pointer p) {
        return (p->parent->right == p);
    }
    inline node_pointer rebalenced_at(node_pointer g, node_pointer p, node_pointer v) {
//		assert(v);
        if (is_lchild(p)) {
            if(is_lchild(v)) {
                p->parent = g->parent;
                return connect34(v, p, g, v->left, v->right, p->right, g->right);
            } else {
                v->parent = g->parent;
                return connect34(p, v, g, p->left, v->left, v->right, g->right);
            }
        } else {
            if(is_rchild(v)) {
                p->parent = g->parent;
                return connect34(g, p, v, g->left, p->left, v->left, v->right);
            } else {
                v->parent = g->parent;
                return connect34(g, v, p, g->left, v->left, v->right, p->right);
            }
        }

    }
    inline node_pointer *from_parent_to(node_pointer p) {
        return &((p == this->root()) ? this->m_dummy_super_root.left
                                     : ( (is_lchild(p)) ? p->parent->left : p->parent->right) );
    }
    inline size_type size_of_node(node_pointer p) {
        return p ? p->n_size : 0;
    }
    inline void update_size(node_pointer p) {
        if(!p) return;
        p->n_size = size_of_node(p->left) + size_of_node(p->right) + 1;
    }
    inline void update_size_above(node_pointer p) {
        while (p->parent) {
            update_size(p->parent);
            p = p->parent;
        }
    }
    node_pointer insert(const value_type& val) {
        node_pointer *t, p;
        t = this->search(val, &p);
        if(*t) {
            (*t)->m_data = val;
            return *t;
        }
        *t = new node_type(val); (*t)->parent = p; this->m_size++;
        update_height(p);
        update_size(p);
        update_size_above(p);
        node_pointer v = *t;
        for (node_pointer g = p->parent; g && g!=&(this->m_dummy_super_root); v = p, p = g, g = g->parent) {
            if (!is_balenced(g)) {
                *from_parent_to(g) = rebalenced_at(g, p, v);
                break;
            } else {
                update_height(g);
            }
        }
        return *t;
    }

    inline node_pointer taller_child(node_pointer p) {
        return (
                (height(p->left) > height(p->right)) ?
                p->left : (
                        (height(p->left) < height(p->right)) ? p->right :
                        (is_lchild(p) ? p->left : p->right)));
    }
    bool remove(const value_type& val) {
        node_pointer *r, g;
        r = this->search(val, &g);
        if(!*r) return false;
        this->remove_at(r, &g);
        update_size(g);
        update_size_above(g);
        while (g && g!=&(this->m_dummy_super_root)) {
            update_height(g);
            if (!is_balenced(g)) {
                node_pointer p = taller_child(g);
                node_pointer v = taller_child(p);
                *from_parent_to(g) = rebalenced_at(g, p, v);
            }
            g = g->parent;
        }
        return true;
    }

    bool remove_by_rank(size_type rank) {
        node_pointer *r, g;
        r = this->select(rank, &g);
        if(!r || !*r) return false;
        this->remove_at(r, &g);
        update_size(g);
        update_size_above(g);
        while (g && g!=&(this->m_dummy_super_root)) {
            update_height(g);
            if (!is_balenced(g)) {
                node_pointer p = taller_child(g);
                node_pointer v = taller_child(p);
                *from_parent_to(g) = rebalenced_at(g, p, v);
            }
            g = g->parent;
        }
        return true;
    }

    inline node_pointer *select(size_type rank, node_pointer *parent) {
        if(rank >= this->m_size) return NULL;
        *parent = &(this->m_dummy_super_root);
        node_pointer* ret = &(this->m_dummy_super_root.left);
        size_t r = size_of_node((*ret)->left);
        while(r != rank) {
            if (rank < r) {
                *parent = *ret;
                ret = &(*ret)->left;
                r = r - size_of_node((*ret)->right) - 1;
            } else if (rank > r) {
                *parent = *ret;
                ret = &(*ret)->right;
                r = r + size_of_node((*ret)->left) + 1;
            }
        }
        return ret;
    }

    size_type rank(value_type &val) {
        node_pointer p = this->root();
        size_t r = size_of_node(p->left);
        while(p) {
            if (p->m_data > val) {
                p = p->left;
                r = r - size_of_node(p? p->right : NULL) - 1;
            } else if (p->m_data < val) {
                p = p->right;
                r = r + size_of_node(p? p->left : NULL) + 1;
            } else {
                return r;
            }
        }
        return r; // if r = -1 or size, then seach failed
    }

    const value_type& operator [](size_type rank) {
        node_pointer *q, p;
        q = select(rank, &p);
        return (*q)->m_data;
    }

};

}//namespace btl
#endif //BYL_TEMPLATE_LIBRARY_AVL_TREE_H
