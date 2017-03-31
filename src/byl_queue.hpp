/*****************************************************************
 * byl_queue.hpp
 * byl_template_library
 *
 *  Created on		: Jun 2, 2016 
 *  Author			: yulongb
 *	Email			: yulongb@stud.ntnu.no
 *  Description		:
 *****************************************************************/

#ifndef BYL_QUEUE_HPP_
#define BYL_QUEUE_HPP_

#include "byl_vector.hpp"
namespace byl {

template <typename T>
class queue : byl::vector<T> {
public:
	typedef typename byl::vector<T>::size_type size_type;
	queue(size_type n) : front_idx(0) {
		this->reserve(n);
	}

	const T& front () const {
		return this->at(front_idx);
	}

	T& front () {
		return this->at(front_idx);
	}

	inline void push(const T& v) {
		this->push_back(v);
	}

	inline void pop() {
		front_idx++;
	}

	inline bool empty() {
		return (front_idx >= this->size());
	}
private:
	size_type front_idx;

};

}


#endif /* BYL_QUEUE_HPP_ */
