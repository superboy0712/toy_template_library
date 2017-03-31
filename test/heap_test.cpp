/*****************************************************************
 * heap_test.cpp
 * byl_template_library
 *
 *  Created on		: Jun 2, 2016 
 *  Author			: yulongb
 *	Email			: yulongb@stud.ntnu.no
 *  Description		:
 *****************************************************************/

#include "byl_heap.hpp"
#include "byl_vector.hpp"
#include "byl_util.h"
#include <cstdio>
#define SZ ((1<<26))
#define SZ2 ((1<<17))
int inputbin[SZ2];   // 此处仅为示意，若直接开这么大的数组会超过内存限制
int main9(int argc, char **argv) {
	setvbuf(stdout, NULL,_IOFBF, SZ);
	int n, k;
	fread(&n, sizeof(int), 1, stdin);
	fread(&k, sizeof(int), 1, stdin);
	int len = fread(inputbin, sizeof(int), SZ2, stdin);


//	int len = 6;
//	n = 6;
//	k = 3;
	byl::heap<int> hh(k);
//	inputbin[0] = 1;
//	inputbin[1] = 4;
//	inputbin[2] = -5;
//	inputbin[3] = 1;
//	inputbin[4] = 4;
//	inputbin[5] = -2;
//	int i = 0;
//	for (; i < k; i++) {
//		hh.insert(inputbin[i]);
//	}
//	for (; i < n; i++) {
//		if (inputbin[i] < hh.get_max()){
//			byl::g_swap(hh[0], inputbin[i]);
//			hh.percolate_down(k, 0);
//		}
//	}

	for (int i = 0, j = 0; i < n; i++, j++) {
		if(j >= len) {
			j = 0;
			len = fread(inputbin, sizeof(int), SZ2, stdin);
		}
		if (hh.size() < (size_t)k) {
			hh.insert(inputbin[j]);
		} else 	if (inputbin[j] < hh.get_max()){
			byl::g_swap(hh[0], inputbin[j]);
			hh.percolate_down(k, 0);
		}
	}

//	for (int i = 0; i < k; i++) {
//		printf("%d\n", hh.delet_max());
//	}
//	hh.sort();
	char *outptr = (char *)inputbin;
	char *outhead = (char *)inputbin;
	for (int i = k-1; i >= 0; i--) {
		outptr += sprintf(outptr, "%d\n", hh.delet_max());
		if ( outptr - outhead >= (int)sizeof(int)*SZ2-64) {
			*(outptr+1) = '\0';
			printf("%s", (outhead));
			outptr = outhead;
		}
	}
	if (outptr - outhead) {
		*(outptr+1) = '\0';
		printf("%s", (outhead));
		outptr = outhead;
	}
	return 0;
}


