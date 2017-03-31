/*****************************************************************
 * bst.h
 * pokerface
 *
 *  Created on		: May 21, 2016 
 *  Author			: yulongb
 *	Email			: yulongb@stud.ntnu.no
 *  Description		:
 *****************************************************************/

#ifndef BST_H_
#define BST_H_
#include "byl_util.hpp"
#include <cassert>

namespace byl {
template<typename T, template <typename> class U> struct bst;

template<typename T>
struct node {
	typedef node *node_ptr;
	friend struct bst<T, node>;
	node_ptr left, right, parent;
	T m_data;
	node(const T& d = T()) : left(NULL), right(NULL)
						  , parent(NULL)
						  , m_data(d) {}
protected:
//	node(node_ptr *l, node_ptr *r, node *p = NULL, const T& d = T()) :
//		left(l), right(r), parent(p), m_data(d) {}
};

template<typename T, template <typename> class U>
struct bst {

	typedef U<T> node_type;
	typedef node_type * node_pointer;
	typedef node_type * node_iterator;
	typedef const node_type * const_node_iterator;
	typedef T value_type;
	typedef size_t size_type;
	node_type m_dummy_super_root;// seems too wasted for large element
	size_t m_size;
	node_pointer m_cur_traverse_idx;

	bst():  m_dummy_super_root(), m_size(0)
			, m_cur_traverse_idx(&m_dummy_super_root) {}


	inline node_pointer root() {
		return m_dummy_super_root.left;
	}

	node_pointer begin() {
		return leftmost_child(&m_dummy_super_root);
	}

	node_pointer end() {
		return &m_dummy_super_root;
	}

	size_type size() const {
		return m_size;
	}
	node_pointer *insert(const value_type& v) {
		node_pointer *i, p;
		i = search(v, &p);
		if(!*i) {
			*i = new node_type(v);
			(*i)->parent = p;
			m_size++;
		} else {
			// already exists, just update value
			(*i)->m_data = v;
		}
		return i;
	}
	node_pointer *search(const value_type& v) {
		node_pointer p;
		return search(v, &p);
	}
	// return the position to access, and its parent.
	inline node_pointer *search(const value_type& v, node_pointer *const parent) {
		*parent = &m_dummy_super_root;
		node_pointer *hot = &(m_dummy_super_root.left);
		while(*hot) {
			if ((*hot)->m_data == v) {
				return hot;
			}
			*parent = *hot;
			if ((*hot)->m_data < v) {
				hot = &(*hot)->right;
			} else {
				hot = &(*hot)->left;
			}
		}
		return hot;
	}

	inline static node_pointer leftmost_child(node_pointer root) {
		assert(root);
		while(root->left) {
			root = root->left;
		}
		return root;
	}

	inline static node_pointer rightmost_child(node_pointer root) {
		assert(root);
		while(root->right) {
			root = root->right;
		}
		return root;
	}

	inline static node_pointer next_back_from_left(node_pointer root) {
		assert(root && root->parent);
		if(!root->right) {
			return root->parent;
		}
		return leftmost_child(root->right);
	}

	inline static node_pointer next_back_from_right(node_pointer root) {
		assert(root && root->parent);
		return root->parent;
	}
	bool remove_at(node_pointer *r, node_pointer* parent) {
		if(!*r) return false;
		if(!((*r)->left && (*r)->right)) {
			// has at most one branch
			node_pointer t = *r;
			if((*r)->left) {
				*r = (*r)->left;
			} else {
				*r = (*r)->right;
			}
			if (*r) {
				(*r)->parent = t->parent;
			}
			*parent = t->parent;
			delete t;
			m_size--;
			return true;
		}
		// has two branches
		// find my successor
		node_pointer *s = &(*r)->right;
		while((*s)->left) s = &(*s)->left;
		byl::g_swap((*s)->m_data, (*r)->m_data);
		node_pointer t = *s;
		*s = (*s)->right;
		if(*s) {
			(*s)->parent = t->parent;
		}
		*parent = t->parent;
		delete t;
		m_size--;
		return true;
	}
	bool remove(const value_type& val) {
		node_pointer *r, p;
		r = search(val, &p);
		return remove_at(r, &p);
	}


//protected:
	static inline bool is_rchild(const node_pointer cur) {
		return (cur->parent->right == cur);
	}
	static inline bool is_lchild(const node_pointer cur) {
		return (cur->parent->left == cur);
	}
	static inline node_pointer next(node_pointer cur) {
		// case 1: has right subtree
		if (cur->right) {
			return leftmost_child(cur->right);
		}
		// case 2: has no right subtree
		// the successor is the nearest ancestor
		// for which current node would be in left subtree
		while(is_rchild(cur)) {
			cur = cur->parent;
		}
		return cur->parent;
	}

	inline node_pointer next_cyclic(node_pointer cur) {
		if (cur == &m_dummy_super_root) {
			return leftmost_child(cur);
		}
		return next(cur);
	}

	inline static node_pointer prev(node_pointer cur) {
		if (cur->left) {
			return rightmost_child(cur->left);
		}
		while(is_lchild(cur)) {
			cur = cur->parent;
		}
		return cur->parent;
	}
	inline node_pointer prev_cyclic(node_pointer cur) {
		if (cur == &m_dummy_super_root) {
			if(cur->left) return rightmost_child(cur->left);
			return cur;
		}
		if (cur == begin()) {
			return &m_dummy_super_root;
		}

		return prev(cur);
	}

	bool zig(node_pointer *pp) {
		if(!*pp || !(*pp)->left) return false;
		node_pointer t = (*pp)->left;
		(*pp)->left = t->right; //y
		if(t->right) {
			// important!
			// there are 6 links need to be handled!!
			t->right->parent = *pp;
		}
		t->right = *pp;
		t->parent = (*pp)->parent;
		(*pp)->parent = t;
		*pp = t;
		return true;
	}

	bool zag(node_pointer *pp) {
		if(!*pp || !(*pp)->right) return false;
		node_pointer t = (*pp)->right;
		(*pp)->right = t->left; //y
		if(t->left) {
			// important!
			// there are 6 links need to be handled!!
			t->left->parent = *pp;
		}
		t->left = *pp;
		t->parent = (*pp)->parent;
		(*pp)->parent = t;
		*pp = t;
		return true;
	}
};

}// namespace btl
#endif /* BST_H_ */
