//============================================================================
// Name        : container.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "byl_vector.hpp"
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include "sample_obj_under_test.hpp"

using namespace std;
struct b {
	b() {
		cout << "b::b()" << endl;
	}
	virtual void v() {
		cout << "b::v()" << endl;
	}
	void nv() {
		cout << "b::nv()" << endl;
	}

	virtual ~b() {
		cout << "b::~b()" << endl;
	}
};

// hide vs. override. and how to explicitly call base's member func using scope resolution
struct a : public b {
	a() {
		cout << "a:: a()" << endl;
	}

	~a() {
		cout << "a:: ~a()" << endl;
	}

	void v() {
		cout << "a::v()" << endl;
	}

	void nv() {
		cout << "a::nv()" << endl;
	}
};
void test_ab() {
	a aa;
	aa.nv();
	aa.b::nv();
}

void test_container_element_release() {

//	try {
//		hello a;
//		byl::vector<hello> b(10);
//		byl::vector<hello> c(10, a);
//	}
//	catch (...) {
//		cout << "catched" << endl;
//	}
//	vector<hello> a(size_t(5));
//	vector<hello> c(-10000000000000);
	byl::vector<hello> c;
	hello d;
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);
	c.push_back(d);

	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	c.pop_back();
	cout << "copy start" << endl;
	byl::vector<hello> e(c);
}

void test_vector_of_vectors() {
	using namespace byl;
//	hello o;
	std::vector<hello> c(1, hello());
//	cout << "multiple c" << endl;
//	vector<vector<hello> > mc(5, c);
//	cout << "multiple rvalue init" << endl;
//	vector<vector<hello> > mr(5, vector<hello>(2, o));
	byl::vector<std::vector<hello> > ml(4, c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.push_back(c);
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();
	ml.pop_back();

}
template <typename T>
void print_vector(const byl::vector<T>& v) {
	for(byl::vector<int>::const_iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << ", ";
	}
	cout << endl;
}

template <typename T>
struct Tfunc {
	typedef void (*func_type)(const T&);
//	void print_vector(const byl::vector<T>& v) {
//		for(byl::vector<int>::const_iterator it = v.begin(); it != v.end(); it++) {
//			cout << *it << ", ";
//		}
//		cout << endl;
//	}
//	func_type
};

//template <typename T, typename U>
//void map_vector(byl::vector<T>& v, Tfunc<U>::func_type func) {
//	for(byl::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
//		func(*it);
//	}
//}

void test_vector_of_vectors2() {
	byl::vector<byl::vector<int> > a;
	for (size_t i = 1; i <= 2; i++) {
		a.push_back(byl::vector<int>(i,(int)i));
	}
	for (size_t i = 3; i ; i--) {
		a.push_back(byl::vector<int>(i,(int)i));
	}
	for(byl::vector<byl::vector<int> >::const_iterator it = a.begin(); it != a.end(); it++) {
		print_vector(*it);
	}
	for(byl::vector<byl::vector<int> >::size_type i = 0; i < a.size(); i++) {
		print_vector(a[i]);
	}
	for(size_t i = 0; i < a.size(); i++) {
		print_vector(a.at(i));
	}
	std::sort(a.begin(), a.end());
	cout << "after sorting\n";
	for(size_t i = 0; i < a.size(); i++) {
		print_vector(a.at(i));
	}
	while(!a.empty()){
		a.pop_back();
	}
	byl::vector<int> b;
	for( int i = 100; i >0; i--) {
		b.push_back(i);
	}
	byl::vector<int> c(b);

	std::sort(b.begin(), b.end());
//	swap(c, b);
//	c.swap(b);
	print_vector(b);

}
void vector_grow_shrink_comarison() {
	std::vector<int> a;
	byl::vector<int> b;
//	a.reserve(128);
//	b.reserve(128);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.push_back(1);
	b.push_back(1);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;


	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.pop_back();
	b.pop_back();
//	b.reserve(20);
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;	a.pop_back();
	b.pop_back();
	cout << a.size()<<", "<<b.size()<< ",  " << a.capacity() << ", " << b.capacity() << endl;
}

typedef typename byl::vector<int>::iterator iterator;
void print_vec(byl::vector<int> &v) {
	for(iterator it = v.begin(); it != v.end(); it++) {
		printf("%d ", *it);
	}
	puts("");
}
int main7(int argc, char **argv) {
	byl::vector<int> a((size_t)16, 5);
	print_vec(a);
	printf("size: %ld, cap: %ld\n", a.size(), a.capacity());
	iterator it = a.insert_for_pod(a.begin(), 111);
	printf("size: %ld, cap: %ld\n", a.size(), a.capacity());
	print_vec(a);
	printf("old it: %d\n", *it);

	byl::vector<int> b((size_t)10, 5);
	print_vec(b);
	b.reserve(20);
	b.insert_for_pod(b.begin(), 111);
	b.insert_for_pod(b.end(), 222);
	printf("size: %ld, cap: %ld\n", b.size(), b.capacity());
	print_vec(b);
	b.remove_for_pod(b.end()-1);
	printf("size: %ld, cap: %ld\n", b.size(), b.capacity());
	print_vec(b);
	b.remove_for_pod(b.begin());
	printf("size: %ld, cap: %ld\n", b.size(), b.capacity());
	print_vec(b);
	return 0;
}
// class template specialization
int main5() {

//	test_vector_of_vectors2();
	hello g("g");
	hello f("f");
	g = f;
	hello a = hello("b");
	byl::vector<int> bb(size_t(3), 5);
	byl::vector<hello> cc(10, g);
	cc.clear();
	cout << cc.size() << ", " << cc.capacity() << endl;
//	byl::vector<hello> a(5, d);
//	byl::vector<hello> b(2, d);
//	byl::vector<hello> c(4, hello());
	test_container_element_release();
	return 0;
}
