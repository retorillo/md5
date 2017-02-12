#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <string.h>
#include <iomanip>
#include <climits>

using namespace std;

string md5(char* str);
string md5_encode(unsigned int*, int);
void md5_append(vector<unsigned char>&, unsigned long);
void md5_padding(vector<unsigned char>&);

TEST_CASE("MD5 test suit") {
  SECTION("MD5 (\"\") = d41d8cd98f00b204e9800998ecf8427e") {
    REQUIRE(md5("") == "d41d8cd98f00b204e9800998ecf8427e");
  }
  SECTION("MD5 (\"a\") = 0cc175b9c0f1b6a831c399e269772661") {
    REQUIRE(md5("a") == "0cc175b9c0f1b6a831c399e269772661");
  }
  SECTION("MD5 (\"abc\") = 900150983cd24fb0d6963f7d28e17f72") {
    REQUIRE(md5("abc") == "900150983cd24fb0d6963f7d28e17f72");
  }
//  SECTION("MD5 (\"message digest\") = f96b697d7cb7938d525a2f31aaf161d0") {
//    REQUIRE(md5("message digest") == "f96b697d7cb7938d525a2f31aaf161d0");
//  }
//  SECTION("MD5 (\"abcdefghijklmnopqrstuvwxyz\") = c3fcd3d76192e4007dfb496cca67e13b") {
//    REQUIRE(md5("abcdefghijklmnopqrstuvwxyz") == "c3fcd3d76192e4007dfb496cca67e13b");
//  }
//  SECTION("MD5 (\"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\") = d174ab98d277d9f5a5611c2c9f419d9f") {
//    REQUIRE(md5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") == "d174ab98d277d9f5a5611c2c9f419d9f");
//  }
//  SECTION("MD5 (\"12345678901234567890123456789012345678901234567890123456789012345678901234567890\") = 57edf4a22be3c955ac49da2e2107b67a") {
//    REQUIRE(md5("12345678901234567890123456789012345678901234567890123456789012345678901234567890") == "57edf4a22be3c955ac49da2e2107b67a");
//  }
}
unsigned int makeword(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4) {
  return ((unsigned int)b1) | (((unsigned int)b2) << 8) |
    (((unsigned int)b3) << 16) | (((unsigned int)b4) << 24);
}
unsigned int leftrotate(unsigned int v, unsigned int amount) {
  return (v << amount) | (v >> (32 - amount));
}

string md5(char* str) {
  vector<unsigned char> msg;
  for(int c = 0; c < strlen(str); c++)
    msg.push_back((unsigned char)str[c]);
  unsigned int s[] = {
     7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
     5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
     4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
     6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,
    };
  unsigned int K[] = {
     0xd76aa478U, 0xe8c7b756U, 0x242070dbU, 0xc1bdceeeU,
     0xf57c0fafU, 0x4787c62aU, 0xa8304613U, 0xfd469501U,
     0x698098d8U, 0x8b44f7afU, 0xffff5bb1U, 0x895cd7beU,
     0x6b901122U, 0xfd987193U, 0xa679438eU, 0x49b40821U,
     0xf61e2562U, 0xc040b340U, 0x265e5a51U, 0xe9b6c7aaU,
     0xd62f105dU, 0x02441453U, 0xd8a1e681U, 0xe7d3fbc8U,
     0x21e1cde6U, 0xc33707d6U, 0xf4d50d87U, 0x455a14edU,
     0xa9e3e905U, 0xfcefa3f8U, 0x676f02d9U, 0x8d2a4c8aU,
     0xfffa3942U, 0x8771f681U, 0x6d9d6122U, 0xfde5380cU,
     0xa4beea44U, 0x4bdecfa9U, 0xf6bb4b60U, 0xbebfbc70U,
     0x289b7ec6U, 0xeaa127faU, 0xd4ef3085U, 0x04881d05U,
     0xd9d4d039U, 0xe6db99e5U, 0x1fa27cf8U, 0xc4ac5665U,
     0xf4292244U, 0x432aff97U, 0xab9423a7U, 0xfc93a039U,
     0x655b59c3U, 0x8f0ccc92U, 0xffeff47dU, 0x85845dd1U,
     0x6fa87e4fU, 0xfe2ce6e0U, 0xa3014314U, 0x4e0811a1U,
     0xf7537e82U, 0xbd3af235U, 0x2ad7d2bbU, 0xeb86d391U,
    };
  unsigned int a0 = 0x67452301U;   //A
  unsigned int b0 = 0xefcdab89U;   //B
  unsigned int c0 = 0x98badcfeU;   //C
  unsigned int d0 = 0x10325476U;   //D
  md5_padding(msg);
  for (int c = 0; c < msg.size(); c += 64) {
    unsigned int M[] = {
      makeword(msg[c+ 0], msg[c+ 1], msg[c+ 2], msg[c+ 3]),
      makeword(msg[c+ 4], msg[c+ 5], msg[c+ 6], msg[c+ 7]),
      makeword(msg[c+ 8], msg[c+ 9], msg[c+10], msg[c+11]),
      makeword(msg[c+12], msg[c+13], msg[c+14], msg[c+15]),
      makeword(msg[c+16], msg[c+17], msg[c+18], msg[c+19]),
      makeword(msg[c+20], msg[c+21], msg[c+22], msg[c+23]),
      makeword(msg[c+24], msg[c+25], msg[c+26], msg[c+27]),
      makeword(msg[c+28], msg[c+29], msg[c+30], msg[c+31]),
      makeword(msg[c+32], msg[c+33], msg[c+34], msg[c+35]),
      makeword(msg[c+36], msg[c+37], msg[c+38], msg[c+39]),
      makeword(msg[c+40], msg[c+41], msg[c+42], msg[c+43]),
      makeword(msg[c+44], msg[c+45], msg[c+46], msg[c+47]),
      makeword(msg[c+48], msg[c+49], msg[c+50], msg[c+51]),
      makeword(msg[c+52], msg[c+53], msg[c+54], msg[c+55]),
      makeword(msg[c+56], msg[c+57], msg[c+58], msg[c+59]),
      makeword(msg[c+60], msg[c+61], msg[c+62], msg[c+63]),
    };
    unsigned int A = a0;
    unsigned int B = b0;
    unsigned int C = c0;
    unsigned int D = d0;
    unsigned int F, g, tempD;
    for (int i = 0; i < 64; i++) {
      if (0 <= i && i <= 15) {
        F = (B & C) | ((~B) & D);
        g = i;
      }
      else if (16 <= i && i <= 31) {
        F = (D & B) | ((~D) & C);
        g = (5 * i + 1) % 16;
      }
      else if (32 <= i && i <= 47) {
        F = B ^ C ^ D;
        g = (3 * i + 5) % 16;
      }
      else if (48 <= i && i <= 63) {
        F = C ^ (B | (~D));
        g = (7 * i) % 16;
      }
      tempD = D;
      D = C;
      C = B;
      B += leftrotate((A + F + K[i] + M[g]), s[i]);
      A = tempD;
    }
    a0 += A;
    b0 += B;
    c0 += C;
    d0 += D;
  }
  unsigned int hash[] = { a0, b0, c0, d0 };
  return md5_encode(hash, 4);
}


string md5_encode(unsigned int* data, int len) {
  ostringstream buf;
  for (int c = 0; c < len; c++) {
    unsigned int b4 = data[c] >> 24 & 0xff;
    unsigned int b3 = data[c] >> 16 & 0xff;
    unsigned int b2 = data[c] >> 8  & 0xff;
    unsigned int b1 = data[c]       & 0xff;
    buf << setfill('0') << setw(2) << hex << b1;
    buf << setfill('0') << setw(2) << hex << b2;
    buf << setfill('0') << setw(2) << hex << b3;
    buf << setfill('0') << setw(2) << hex << b4;
  }
  return buf.str();
}


void md5_append(vector<unsigned char>& msg, unsigned long data){
  unsigned char w1h = (unsigned char)(data >> 24 & 0xff);
  unsigned char w1l = (unsigned char)(data >> 16 & 0xff);
  unsigned char w2h = (unsigned char)(data >> 8  & 0xff);
  unsigned char w2l = (unsigned char)(data       & 0xff);
  msg.push_back(w2l);
  msg.push_back(w2h);
  msg.push_back(w1l);
  msg.push_back(w1h);
}

void md5_padding(vector<unsigned char>& msg){
  unsigned long count = msg.size();
  unsigned int bits = count * 8;
  if (bits > 512 && bits % 512 == 0) return;
  bits += 8;
  msg.push_back((unsigned char)0x80);
  while (bits % 512 != 448) {
    msg.push_back((unsigned char)0x00);
    bits += 8;
  }
  md5_append(msg, count * 8);
}
