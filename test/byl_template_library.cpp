//============================================================================
// Name        : byl_template_library.cpp
// Author      : Yulong Bai
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//#include <iostream>
//#include "vector_test.hpp"
//#include <vector>
//#include "byl_bst.hpp"
//#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "bst.h"
// member methods that return reference, iterator, pointer
// need to provide both const and non-const versions for override resolution
typedef long integer;
inline integer cross_product(integer x1, integer y1, integer x2, integer y2) {
	return (x1*y2 - y1*x2);
}

//typedef typename byl::vector<int>::iterator it;
//typedef byl::vector<int> vec;
struct pairs{
	integer x;
	integer y;
};
integer search_region(integer x, integer y, integer lo, integer hi, const pairs *p) {
	if(hi - lo == 0) return hi;
	while(lo < hi) {
		integer mid = (lo + hi) >> 1;
		pairs pp = p[mid];
		integer res = cross_product(-pp.x, pp.y, x - pp.x, y);
		if (res < 0) {
			// on the upright
			lo = mid + 1;
		}
		else if (res > 0){
			// on the bottomleft
			hi = mid;
		}
		else {
			return mid;
		}
	}
	return hi;
}

template <typename value_type>
struct POD_ARRAY {
	typedef size_t size_type;
	typedef value_type * iterator;
	POD_ARRAY(size_type n) : m_size(0), m_cap(n) {
		m_buffer = (value_type *)malloc((m_cap+1)*sizeof(value_type));
	}
	~POD_ARRAY() {
		if(m_buffer) {
			free(m_buffer);
		}
	}
	inline size_t size() const {
		return m_size;
	}
	bool insert(const value_type& val) {
		size_type idx;
		if(!search(val, idx)) {
			insert_by_idx(idx, val);
			return true;
		}
		return false;
	}
	bool remove(const value_type& val) {
		size_type idx;
		if(search(val, idx)) {
			remove_by_idx(idx);
			return true;
		}
		return false;
	}
	bool search(const value_type& val) {
		size_type idx;
		return search(val, idx);
	}
	inline bool search(const value_type& val, size_type& idx) {
		// return the idx of value to insert and if exists
		size_type lo = 0, hi = m_size;
		while (lo < hi) {
			size_type mid = (lo + hi)/2;
			if (m_buffer[mid] < val) {
				lo = mid + 1;
			} else if (m_buffer[mid] > val) {
				hi = mid;
			} else {
				idx = mid;
				return true;
			}
		}
		idx = lo;
		return false;
	}
	iterator insert_by_idx(size_type idx, const value_type& val) {
		memmove(m_buffer+idx+1, m_buffer+idx, (m_size-idx)*sizeof(value_type));
		m_buffer[idx] = val;
		m_size++;
		return &m_buffer[idx];
	}

	void remove_by_idx(size_type idx) {
		memmove(m_buffer+idx, m_buffer+idx+1, (m_size-idx-1)*sizeof(value_type));
		m_size--;
	}

	void print() {
		for(int i = 0; i < m_size; i++) {
			printf("%ld ", m_buffer[i]);
		}
		puts("");
	}
//private:
	value_type *m_buffer;
	size_type m_size, m_cap;
};
int test(int argc, char **argv) {
	POD_ARRAY<long> a(100);
	printf("size: %ld\n", a.size());
	a.insert(1);
	a.print();
	printf("size: %ld\n", a.size());
	a.insert(-1);
	a.print();
	printf("size: %ld\n", a.size());
	a.insert(2);
	a.print();
	printf("size: %ld\n", a.size());
	a.insert(-3);
	a.print();
	printf("size: %ld\n", a.size());
	a.insert(5);
	a.print();
	printf("size: %ld\n", a.size());
	a.remove_by_idx(2);
	a.print();
	printf("size: %ld\n", a.size());
	a.remove_by_idx(1);
	a.print();
	printf("size: %ld\n", a.size());
	a.remove_by_idx(-3);
	a.print();
	printf("size: %ld\n", a.size());
	a.remove_by_idx(-1);
	a.print();
	printf("size: %ld\n", a.size());
	return 0;
}

#define SZ (1<<25)
char input[SZ];
char output[SZ];
static char *outptr = output;
typedef integer (*funptr)(integer x, integer y);
POD_ARRAY<integer> *xx, *yy;
integer search_region2(integer x, integer y, integer lo, integer hi) {
	if(hi - lo == 0) return hi;
	while(lo < hi) {
		integer mid = (lo + hi) >> 1;
		integer res = cross_product(-xx->m_buffer[mid], yy->m_buffer[mid], x - xx->m_buffer[mid], y);
		if (res < 0) {
			// on the upright
			lo = mid + 1;
		}
		else if (res > 0){
			// on the bottomleft
			hi = mid;
		}
		else {
			return mid;
		}
	}
	return hi;
}

integer main_insert(integer x, integer y) {
	xx->insert(x);
	yy->insert(y);
//	printf("install %ld %ld\n", x, y);
	return 0;
}

integer main_remove(integer x, integer y) {
	xx->remove_by_idx(x);
	yy->remove_by_idx(y);
//	printf("remove %ld %ld\n", x, y);
	return 0;
}

integer main_search(integer x, integer y) {
	outptr += sprintf(outptr, "%ld ", search_region2(x, y, 0, xx->size()));
//	printf("searching %d, %d for old\n", x, y);
//	xx->print();
//	yy->print();
	return 0;
}

avl_tree<integer> xxx, yyy;
integer avl_insert(integer x, integer y) {
	xxx.insert(x);
	yyy.insert(y);
//	printf("install %ld %ld\n", x, y);
	return 0;
}

integer avl_remove(integer x, integer y) {
	xxx.remove_by_rank(x);
	yyy.remove_by_rank(y);
//	printf("remove %ld %ld\n", x, y);
	return 0;
}

typedef typename avl_tree<integer>::node_pointer node_pointer;

inline integer size_of_node(node_pointer p) {
	return p ? p->n_size : 0;
}
inline bool is_lchild(node_pointer p) {
	return (p->parent->left == p);
}
inline bool is_rchild(node_pointer p) {
	return (p->parent->right == p);
}
integer search_region3(integer x, integer y) {
	if(xxx.size() == 0) return 0;
	node_pointer xx = (xxx.m_dummy_super_root.left);
	node_pointer yy = (yyy.m_dummy_super_root.left);
	integer rank_of_xx = (xx->left) ? xx->left->n_size : 0;
	integer rank_of_yy = yyy.rank(yy->m_data);
	// synchronize the root
	while (rank_of_xx > rank_of_yy) {
//		printf("sync mismatched rank for xx(%ld) and yy(%ld) when searching (%ld, %ld)     >>> \n",
//				xxx.rank(xx->m_data), yyy.rank(yy->m_data), x, y);
		yy = yyy.next(yy);
		rank_of_yy++;
	}
	while (rank_of_xx < rank_of_yy) {
//		printf("sync mismatched rank for xx(%ld) and yy(%ld) when searching (%ld, %ld)     <<< \n",
//				xxx.rank(xx->m_data), yyy.rank(yy->m_data), x, y);
		yy = yyy.prev(yy);
		rank_of_yy--;
	}
	assert(xxx.rank(xx->m_data) ==  yyy.rank(yy->m_data));
	while(xx && yy) {
//		puts("in while");
//		rank_of_yy = yyy.rank(yy->m_data);
		if (rank_of_xx > rank_of_yy) {
			printf("mismatched rank for xx(%ld) and yy(%ld) when searching (%ld, %ld)     >>> \n",
					xxx.rank(xx->m_data), yyy.rank(yy->m_data), x, y);
		}
		if (rank_of_xx < rank_of_yy) {
			printf("mismatched rank for xx(%ld) and yy(%ld) when searching (%ld, %ld)     <<< \n",
					xxx.rank(xx->m_data), yyy.rank(yy->m_data), x, y);
		}

		integer res = cross_product(-xx->m_data, yy->m_data, x - xx->m_data, y);
		if (res < 0) {
			// on the upright
			integer new_xx_rank = size_of_node((xx->right)?xx->right->left: NULL) + rank_of_xx + 1;
			integer new_yy_rank = size_of_node((yy->right)?yy->right->left: NULL) + rank_of_yy + 1;
			if (new_xx_rank == new_yy_rank) {
				if(yy->right) {
					yy = yy->right;
				} else {
					node_pointer *q, p;
					q = yyy.select(new_yy_rank, &p);
					if(q) {
						yy = *q;
					} else {
						return yyy.size();
					}
				}
				rank_of_yy = new_yy_rank;
			}
			else {
				assert(is_lchild(yy));
				rank_of_yy += 1 + size_of_node(yy->right);
				yy = yy->parent;
			}
			xx = xx->right;
			rank_of_xx = new_xx_rank;
			assert(new_xx_rank == new_yy_rank);

			if(!xx) {
				assert(!yy);
				// end at right;
				new_yy_rank++;
				return new_xx_rank+1;
			}
		}
		else if (res > 0){
			// on the bottomleft
			integer new_xx_rank = (xx->left)? (size_of_node(xx->left->right) + rank_of_xx + 1) : rank_of_xx +1;
			integer new_yy_rank = (yy->left)? (size_of_node(yy->left->right) + rank_of_yy + 1) : rank_of_yy +1;
			if (new_xx_rank == new_yy_rank) {
				if (yy->left) {
					yy = yy->left;
				} else {
					node_pointer *q, p;
					q = yyy.select(new_yy_rank, &p);
					if(q) {
						yy = *q;
					} else {
						return new_yy_rank-1+10000;
					}

				}
				rank_of_yy = new_yy_rank;
			}
			else {
				assert(is_rchild(yy));
				rank_of_yy += 1 + size_of_node(yy->left);
				yy = yy->parent;
			}
			xx = xx->left;
			rank_of_xx = new_xx_rank;
			assert(new_xx_rank == new_yy_rank);

			if(!xx) {
//				assert(!yy);
				// end at left;
				return new_xx_rank;
			}
		}
		else {
			// end right at the line
			return rank_of_xx;
		}
	}
	if(xx || yy) {
		printf("end of no for xx(%ld) and yy(%ld) when searching (%ld, %ld)     <<< \n",
							rank_of_xx, rank_of_yy, x, y);
		printf("yydata: %ld\n", yy->m_data);
	}
	if(xx == xxx.end() || yy == yyy.end()) {
		printf("hiting end\n");
	}
	return -100;
}
integer search_region4(integer x, integer y, integer lo, integer hi) {
	if(hi - lo == 0) return hi;
	while(lo < hi) {
		integer mid = (lo + hi) >> 1;
		integer res = cross_product(-xxx[mid], yyy[mid], x - xxx[mid], y);
		if (res < 0) {
			// on the upright
			lo = mid + 1;
		}
		else if (res > 0){
			// on the bottomleft
			hi = mid;
		}
		else {
			return mid;
		}
	}
	return hi;
}

typedef avl_node<integer> node_type;
integer avl_search(integer x, integer y) {
	outptr += sprintf(outptr, "%ld\n", search_region4(x, y, 0, xxx.size()));
//	outptr += sprintf(outptr, "%ld (%ld, %ld)\n", search_region3(x, y), x, y);
//	printf("%ld\n", search_region4(x, y, 0, xxx.size()));
	return 0;
}

funptr op_table[3] = {
		main_insert, main_search, main_remove
};

funptr op_table2[3] = {
		avl_insert, avl_search, avl_remove
};
int mainnew(int argc, char **argv) {
    setvbuf(stdout, NULL,_IOFBF, SZ);
    int len = fread(input, 1, (SZ), stdin);
    input[len] = '\0';

    char *endptr;
    int N = strtol(input, &endptr, 10);

    for (int i = 0; i < N; i++) {
    	int op = strtol(endptr+1, &endptr, 10);
    	integer x = strtol(endptr+1, &endptr, 10);
    	integer y = strtol(endptr+1, &endptr, 10);
    	op_table2[op](x, y);
    }

    puts(output);
    return 0;
}
int mainold(int argc, char **argv) {
    setvbuf(stdout, NULL,_IOFBF, SZ);
    int len = fread(input, 1, (SZ), stdin);
    input[len] = '\0';

    char *endptr;
    int N = strtol(input, &endptr, 10);

    xx = new POD_ARRAY<integer>(N);
    yy = new POD_ARRAY<integer>(N);
    for (int i = 0; i < N; i++) {
    	int op = strtol(endptr+1, &endptr, 10);
    	integer x = strtol(endptr+1, &endptr, 10);
    	integer y = strtol(endptr+1, &endptr, 10);
    	op_table[op](x, y);
    }

    puts(output);
    delete(xx);
    delete(yy);
    return 0;
}

int maincomp(int argc, char **argv) {
    setvbuf(stdout, NULL,_IOFBF, SZ);
    int len = fread(input, 1, (SZ), stdin);
    input[len] = '\0';

    char *endptr;
    int N = strtol(input, &endptr, 10);

    xx = new POD_ARRAY<integer>(N);
    yy = new POD_ARRAY<integer>(N);
    for (int i = 0; i < N; i++) {
    	int op = strtol(endptr+1, &endptr, 10);
    	integer x = strtol(endptr+1, &endptr, 10);
    	integer y = strtol(endptr+1, &endptr, 10);
    	op_table[op](x, y);
    	op_table2[op](x, y);
    }

    puts(output);
    delete(xx);
    delete(yy);
    return 0;
}

