/*****************************************************************
 * byl_vector.hpp
 * tsp_02
 *
 *  Created on		: May 13, 2016 
 *  Author			: yulongb
 *	Email			: yulongb@stud.ntnu.no
 *  Description		:
 *****************************************************************/

#ifndef BYL_VECTOR_HPP_
#define BYL_VECTOR_HPP_
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <stdexcept>
#include <cstring>
#include "byl_util.hpp"
namespace byl {

	static const size_t m_init_capacity = 16;
//	static const float _shrink_triger_ratio = 1 - 0.618;

	template < typename T >
	class vector {
	public:
		friend class RandomIter<vector<T> >;
//		friend class ConstRandomIter<T>;
		typedef size_t size_type;
		typedef T value_type;
		typedef T * pointer;
		typedef T & reference;
		typedef const T & const_reference;
		typedef T * iterator;
		typedef const T * const_iterator;
//		typedef RandomIter<vector<T> > iterator;
//		typedef const iterator const_iterator;
		explicit vector();// default
		explicit vector (size_type n);
		explicit vector (size_type n, const_reference val);// fill
		vector (const vector& other);// copy. never mark it as explicit!
		template <typename InputIterator>
		explicit vector (InputIterator first, InputIterator last);// range
		virtual ~vector();
		vector& operator= (vector x) {
			// attention, unified swap!
			this->swap(x);
			return *this;
		}
		bool operator <(const vector& rhs) const {
			return this->size() < rhs.size();
		}
		//
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		size_type size() const;
		size_type capacity() const;
		bool empty() const {
			return !m_size;
		}
		reference front() {
			if(!m_size)	perror("byl::vector::front(): empty vector");
			return m_buffer[0];
		}
		const_reference front() const {
			if(!m_size)	perror("byl::vector::front(): empty vector");
			return m_buffer[0];
		}
		reference back() {
			if(!m_size)	perror("byl::vector::back(): empty vector");
			return m_buffer[m_size-1];
		}
		const_reference back() const {
			if(!m_size)	perror("byl::vector::back(): empty vector");
			return m_buffer[m_size-1];
		}
		//
		reference operator[] (size_type n) {
			return m_buffer[n];
		}
		const_reference operator[] (size_type n) const {
			return m_buffer[n];
		}
		reference at (size_type n) {
			if(n >= m_size) throw std::out_of_range("byl::vector::at()");
			return m_buffer[n];
		}
		const_reference at (size_type n) const {
			if(n >= m_size) throw std::out_of_range("byl::vector::at()");
			return m_buffer[n];
		}

		void push_back(const_reference val) {
			grow();
//			printf("size: %ld, cap: %ld\n", m_size, m_capacity);
			new(&m_buffer[m_size++]) value_type(val);
			n_constructed++;
		}
		void pop_back() {
			if(m_size <= 0) {
				// avoid undefined behavior, not abort but print message!
				perror("byl::vector::pop_back() : pop empty vector!");
				return;
			}
			m_buffer[--m_size].~value_type();
			--n_constructed;
			shrink();
//			printf("size: %ld, cap: %ld\n", m_size, m_capacity);
		}
		void reserve (size_type n) {
			if (m_capacity < n) {
				re_alloc(n);
			}
			m_reserved = n;
		}
		iterator insert_for_pod (iterator position, const value_type& val) {
			size_type ip = position - begin();
			size_type sz = end()-position;
			if(m_size+1 > m_capacity) {
				if(!m_capacity) m_capacity = 1;
				re_alloc(m_capacity << 1);
			}
			memmove(begin()+ip+1, begin()+ip, sz*sizeof(value_type));
			m_buffer[ip] = val;
			n_constructed++;
			m_size++;
			return begin()+ip;
		}

		iterator remove_for_pod (iterator position) {
			size_type ip = position - begin();
			size_type sz = end()-position-1;
			n_constructed--;
			m_size--;
			shrink();
			memmove(begin()+ip, begin()+ip+1, sz*sizeof(value_type));
			// pod no need for destruction
			return begin()+ip;
		}


//		iterator erase();
		template<typename D>
		friend void byl::g_swap (D& x, D& y);

		void swap (vector& other) {
			byl::g_swap(this->m_size, other.m_size);
			byl::g_swap(this->n_constructed, other.n_constructed);
			byl::g_swap(this->m_reserved, other.m_reserved);
			byl::g_swap(this->m_capacity, other.m_capacity);
			byl::g_swap(this->m_buffer, other.m_buffer);
		}
		template <typename U>
		friend void swap (vector<U>& x, vector<U>& y);
		void clear() {
			reset();
		}

	protected:
		size_type m_size, n_constructed, m_reserved;
		size_type m_capacity;
		pointer m_buffer;

	protected:
		inline void alloc(size_type capacity) {
			m_buffer = (pointer)malloc((capacity + 1)*sizeof(value_type));
			if(!m_buffer) throw std::bad_alloc();
			m_capacity = capacity;
		}
		inline void re_alloc(size_type new_capacity) {
			pointer tmp = (pointer)realloc(m_buffer, (new_capacity + 1)*sizeof(value_type));
			if(!tmp) throw std::bad_alloc();
			m_buffer = tmp;
			m_capacity = new_capacity;
		}

		inline void reset() {
			if(m_buffer) {
				// assuming destructor exception free
				for (size_type i = 0; i < n_constructed; i++) {
					m_buffer[i].~value_type();
				}
				m_size = 0;
				n_constructed = 0;
			}
		}
		inline void grow() {
			if(m_size >= m_capacity) {
				if(!m_capacity) m_capacity = 1;
				re_alloc(m_capacity << 1);
			}
		}
		inline void shrink() {
			if(m_size < (m_capacity >> 2)
					&&
					m_capacity >= (m_reserved << 1)
				) {
				re_alloc(m_capacity >> 1);
			}
		}
	};

	template <typename T>
	byl::vector<T>::vector() :
	m_size(0), n_constructed(0), m_reserved(m_init_capacity), m_capacity(0), m_buffer(NULL) {
		alloc(0);
	}
	template <typename T>
	byl::vector<T>::~vector() {
		if(m_buffer) {
			for (size_type i = 0; i < n_constructed; i++) {
				m_buffer[i].~value_type();
			}
			m_size = 0;
			n_constructed = 0;
			free(m_buffer);
			m_buffer = NULL;
		}
	}
	template <typename T>
	byl::vector<T>::vector (const vector& other) :
	m_size(other.m_size), n_constructed(0),	m_reserved(other.m_reserved), m_capacity(other.m_capacity), m_buffer(NULL) {
		try {
			alloc(m_capacity);
			for (size_type i = 0; i < m_size; i++, n_constructed++) {
				new(&m_buffer[i]) value_type(other.m_buffer[i]);
			}
		} catch (...) {
			this->~vector();
			throw std::bad_alloc();
		}
	}
	template <typename T>
	byl::vector<T>::vector (size_type n, const_reference val) :
	m_size(n), n_constructed(0), m_reserved(m_init_capacity), m_capacity(m_reserved > m_size ? m_reserved : m_size), m_buffer(NULL) {
		assert((ssize_t)n >= 0);
		try {
			alloc(m_capacity);
			for (size_type i = 0; i < m_size; i++, n_constructed++) {
				new(&m_buffer[i]) value_type(val);
			}
		} catch (...) {
			this->~vector();
			throw std::bad_alloc();
		}
	}
	template <typename T>
	byl::vector<T>::vector(size_type n) :
	m_size(n), n_constructed(0), m_reserved(m_init_capacity), m_capacity(m_reserved > m_size ? m_reserved : m_size), m_buffer(NULL) {
		assert((ssize_t)n >= 0);
		try {
			alloc(m_capacity);
			for (size_type i = 0; i < m_size; i++, n_constructed++) {
				new(&m_buffer[i]) value_type;
			}
		} catch (...) {
			this->~vector();
			throw std::bad_alloc();
		}
	}
	template <typename T>
	inline typename byl::vector<T>::size_type byl::vector<T>::size() const {
		return m_size;
	}
	template <typename T>
	inline typename byl::vector<T>::size_type byl::vector<T>::capacity() const {
		return m_capacity;
	}
	template <typename T>
	inline typename vector<T>::iterator vector<T>::begin() {
		return &m_buffer[0];
	}
	template <typename T>
	inline typename byl::vector<T>::iterator byl::vector<T>::end() {
		// to using dummy byte to avoid implicit member construction. explicit force type cast
		return &m_buffer[m_size];
	}
	template <typename T>
	inline typename vector<T>::const_iterator vector<T>::begin() const {
		return &m_buffer[0];
	}
	template <typename T>
	inline typename byl::vector<T>::const_iterator byl::vector<T>::end() const {
		// to using dummy byte to avoid implicit member construction. explicit force type cast
		return &m_buffer[m_size];
	}
	// For compatible to std::swap algorithm
	template <typename U>
	void swap (vector<U>& x, vector<U>& y) {
		x.swap(y);
	}
}// namespace byl

#endif /* BYL_VECTOR_HPP_ */
