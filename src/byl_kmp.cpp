/*****************************************************************
 * byl_kmp.cpp
 * byl_template_library
 *
 *  Created on		: Jun 5, 2016 
 *  Author			: yulongb
 *	Email			: yulongb@stud.ntnu.no
 *  Description		:
 *****************************************************************/

#include <cstring>
#include <cstdlib>
#include <string>
namespace byl {
int *build_next(const char *pattern) {
	int m = (int)strlen(pattern);
	if( m <= 0) return NULL;
	int *ret = (int *)malloc(m*sizeof(int));
	ret[0] = -1;
	int j = 0, t = -1;
	while(j < m-1) {
		if( t < 0 || pattern[j] == pattern[t]) {
			ret[j+1] = t+1;
			j++; t++;
		} else {
			t = ret[t];
		}
	}
	// why not ret[m-1]?
	return ret;
}

const char *kmp_match(const char *s, const char *p) {
	int n = strlen(s);
	int m = strlen(p);
	if(m <= 0) return "";
	int *next = build_next(p);
	int i = 0, j = 0;
	while ( i < n && j < m) {
		if ( j < 0 || s[i] == p[j]) {
			i++; j++;
		} else {
			j = next[j];
		}
	}
	free(next);
	if(j == m) return &s[i-m];
	else return "";
}

char *min_rll_str(const char *s) {
	int m = strlen(s);
	char *ss = (char *)malloc((m*2+1)*sizeof(char));
	ss[2*m] = '\0';
	strncpy(ss, s, m);
	strncpy(ss+m, s, m);
	return ss;
}

std::string mini_expr(std::string s) {
   s = s + s;
   int len = s.size(), i = 0, j = 1, k = 0;
   while(i + k < len && j + k < len) {
      if(s[i+k] == s[j+k]) k++;
      else if(s[i+k] > s[j+k]) { i = i+k+1; if(i <= j) i = j+1; k = 0; }
      else { j = j+k+1; if(j <= i) j = i+1; k = 0; }
   }
   int n = (i < j) ? i : j;
   return std::string(s.begin()+n, s.begin()+n+len/2);
}
char temp[2*10000 + 1];
char *mini_expr2(const char* s, char *out, int N) {
	memcpy(temp, s, N);
	memcpy(temp+N, s, N);
	temp[2*N] = '\0';
	int len = 2*N - N/2, i = 0, j = 1, k = 0;
	while(i + k < len && j + k < len) {
	  if(temp[i+k] == temp[j+k]) k++;
	  else if(temp[i+k] > temp[j+k]) { i = i+k+1; if(i <= j) i = j+1; k = 0; }
	  else { j = j+k+1; if(j <= i) j = i+1; k = 0; }
	}
	int n = (i < j) ? i : j;
	memcpy(out, temp+n, N);
//	out[N] = '\0';
	return out;
}

unsigned
hash(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash%5039;
}

}