//
// Created by yulong on 3/31/17.
//

#ifndef BYL_TEMPLATE_LIBRARY_BYL_KMP_H
#define BYL_TEMPLATE_LIBRARY_BYL_KMP_H
#include <string>
namespace byl {
extern const char *kmp_match(const char *s, const char *p);
std::string mini_expr(std::string s);
char *mini_expr2(const char* s, char *out, int N);
unsigned hash(const char *str);
}

#endif //BYL_TEMPLATE_LIBRARY_BYL_KMP_H
