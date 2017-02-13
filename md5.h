#include <vector>
#include <string.h>
#include <iomanip>
#include <climits>
#include <sstream>
#include <iostream>

using namespace std;

#define BYTE unsigned char
#define WORD unsigned int

#define MAKE_WORD(b1, b2, b3, b4) (((WORD)b1) | (((WORD)b2) << 8) |\
  (((WORD)b3) << 16) | (((WORD)b4) << 24))
#define ROTATE_LEFT(x, n) ((x << n) | (x >> (32 - n)))

string md5(const char* str, string& abcd_trace);
string printword(WORD*, int);
void md5_padding(vector<BYTE>&);
void md5_append(vector<BYTE>&, unsigned long);
