/*****************************************************************
 * byl_util.h
 * byl_template_library
 *
 *  Created on		: May 16, 2016 
 *  Author			: yulongb
 *	Email			: yulongb@stud.ntnu.no
 *  Description		:
 *****************************************************************/

#ifndef BYL_UTIL_H_
#define BYL_UTIL_H_
namespace byl {


template <typename T>
class RandomIter {
	typedef T container_type;
	typedef typename T::value_type value_type;
	typedef typename T::size_type size_type;
	typedef RandomIter<T> iterator;
	typedef const iterator const_iterator;
	public:
	explicit RandomIter(const iterator& it) : m_c(it.m_c), m_offset(it.m_offset) {}
	explicit RandomIter(const container_type& c, size_type offset = 0) : m_c(c), m_offset(offset) {}
	iterator & operator [](size_type offset) {
		if( 0 <= m_offset+offset && m_offset+offset < m_c.size()) {
			m_offset+=offset;
			return (*this);
		}
		m_offset  = (size_type)-1;
		return (*this);
	}
	const_iterator& operator [](size_type offset) const {
		return (*this)[offset];
	}

	protected:
	container_type& m_c;
	private:
	RandomIter();
	size_type m_offset;
};

template <typename T>
void g_swap (T& x, T& y) {
	T t(x);
	x = y;
	y = t;
}

template <typename T>
T& g_max (T& x, T& y) {
	return (x > y) ? x : y;
}


}// namespace byl

#endif /* BYL_UTIL_H_ */
