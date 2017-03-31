//
// Created by yulong on 3/31/17.
//
#include <cstdio>
#include <cstddef>
#include <string>
#include <cstring>
#include "../src/byl_kmp.h"
using namespace byl;
#define SZ (1 << 17)
namespace kmp {
//	char input[SZ];
char output[SZ];
char *outptr = output;
}
int table[5039];
int main2(int argc, char **argv) {
    using namespace kmp;
    setvbuf(stdout, NULL,_IOFBF, SZ);
//	int len = fread(input, 1, (SZ), stdin);
//	input[len] = '\0';
    memset(table, -1, 5039*sizeof(int));
    char *endptr;
    int M, N;
    scanf("%d %d\n", &M, &N);
//	int M = strtol(input, &endptr, 10);
//	int N = strtol(endptr+1, &endptr, 10);
    char *input = (char *)malloc(M*(N+1)+128);
    int len = fread(input, 1, M*(N+1)+128, stdin);
    input[len] = '\0';
    for(int i = N; i < len; i+=N+1) {
        input[i] = '\0';
    }
    endptr = input;
//	char str[N+1];
//	str[N] = '\0';
    std::string s1, s2;
    for (int i = 0; i < M; i++) {
//		sscanf(endptr, "%s", str);
        s1 = mini_expr(endptr);
        unsigned h = hash(s1.c_str());
loop:
        if(table[h] == -1) {
            outptr += sprintf(outptr, "%d\n", i);
            table[h] = i;
//			continue;
//			printf("---empty slot h: %d fillin %d\n", h, i);
        }
        else {
            s2 = mini_expr(&input[table[h]*(N+1)]);
            if(s1 != s2) {
//				h++;
//				printf("------\n%s\n%s\n-------", s1.c_str(), s2.c_str());
//				printf("conflict h: %d vs %d\n", h, hash(s2.c_str()));

                h++;
                goto loop;
            }
//			printf("%s , %s \n", s1.c_str(), s2.c_str());
//			printf("---same struct slot h: %d recalling %d at %d\n", h, table[h], i);
            outptr += sprintf(outptr, "%d\n", table[h]);
        }
        endptr+=N+1;
    }
    puts(output);
    free(input);
    return 0;
}

int main(int argc, char **argv) {
    using namespace kmp;
    setvbuf(stdout, NULL,_IOFBF, SZ);
    memset(table, -1, 5039*sizeof(int));
    char *endptr;
    int M, N;
    scanf("%d %d\n", &M, &N);
    char *input = (char *)malloc(M*(N+1)+128);
    int len = fread(input, 1, M*(N+1)+128, stdin);
    input[len] = '\0';
    for(int i = N; i < len; i+=N+1) {
        input[i] = '\0';
    }
    endptr = input;
    char  *s1, *s2;
    for (int i = 0; i < M; i++) {
//		printf("origin: %s vs ", endptr);
        s1 = mini_expr2(endptr, endptr, N);
//		printf("minified %s\n", s1);
        unsigned h = hash(s1);
loop:
        if(table[h] == -1) {
            outptr += sprintf(outptr, "%d\n", i);
            table[h] = i;
//			printf("%s\n", s1);
//			printf("---empty slot h: %d fillin %d\n", h, i);
        }
        else {
            s2 = &input[table[h]*(N+1)];
            if(memcmp(s1, s2, N) != 0) {
//				printf("---conflict h: %d vs %d at idx %d\n", h, hash(s2), i);
//				printf("%s vs %s\n", s1, s2);
                h++;
                goto loop;
            }
//			printf("%s , %s \n", s1, s2);
//			printf("---same struct slot h: %d recalling %d at %d\n", h, table[h], i);
            outptr += sprintf(outptr, "%d\n", table[h]);
        }
        endptr+=N+1;
    }
    puts(output);
    free(input);
    return 0;
}

