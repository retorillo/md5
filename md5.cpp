#include "md5.h"

string md5(const char* msg) {
  vector<BYTE> bytes;
  const WORD s[] = {
     7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
     5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
     4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
     6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,
    };
  const WORD K[] = {
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
  for(int c = 0; c < strlen(msg); c++)
    bytes.push_back((BYTE)msg[c]);

  WORD a0 = 0x67452301U;
  WORD b0 = 0xefcdab89U;
  WORD c0 = 0x98badcfeU;
  WORD d0 = 0x10325476U;

  md5_padding(bytes);

  for (int c = 0; c < bytes.size(); c += 64) {
    WORD M[] = {
      MAKE_WORD(bytes[c+ 0], bytes[c+ 1], bytes[c+ 2], bytes[c+ 3]),
      MAKE_WORD(bytes[c+ 4], bytes[c+ 5], bytes[c+ 6], bytes[c+ 7]),
      MAKE_WORD(bytes[c+ 8], bytes[c+ 9], bytes[c+10], bytes[c+11]),
      MAKE_WORD(bytes[c+12], bytes[c+13], bytes[c+14], bytes[c+15]),
      MAKE_WORD(bytes[c+16], bytes[c+17], bytes[c+18], bytes[c+19]),
      MAKE_WORD(bytes[c+20], bytes[c+21], bytes[c+22], bytes[c+23]),
      MAKE_WORD(bytes[c+24], bytes[c+25], bytes[c+26], bytes[c+27]),
      MAKE_WORD(bytes[c+28], bytes[c+29], bytes[c+30], bytes[c+31]),
      MAKE_WORD(bytes[c+32], bytes[c+33], bytes[c+34], bytes[c+35]),
      MAKE_WORD(bytes[c+36], bytes[c+37], bytes[c+38], bytes[c+39]),
      MAKE_WORD(bytes[c+40], bytes[c+41], bytes[c+42], bytes[c+43]),
      MAKE_WORD(bytes[c+44], bytes[c+45], bytes[c+46], bytes[c+47]),
      MAKE_WORD(bytes[c+48], bytes[c+49], bytes[c+50], bytes[c+51]),
      MAKE_WORD(bytes[c+52], bytes[c+53], bytes[c+54], bytes[c+55]),
      MAKE_WORD(bytes[c+56], bytes[c+57], bytes[c+58], bytes[c+59]),
      MAKE_WORD(bytes[c+60], bytes[c+61], bytes[c+62], bytes[c+63]),
    };
    WORD A = a0;
    WORD B = b0;
    WORD C = c0;
    WORD D = d0;
    WORD F, g, tempD;
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
      B += ROTATE_LEFT((A + F + K[i] + M[g]), s[i]);
      A = tempD;
    }
    a0 += A;
    b0 += B;
    c0 += C;
    d0 += D;
  }
  WORD hash[] = { a0, b0, c0, d0 };
  return printword(hash, 4);
}
string printword(WORD* data, int len) {
  ostringstream buf;
  for (int c = 0; c < len; c++) {
    WORD b4 = data[c] >> 24 & 0xff;
    WORD b3 = data[c] >> 16 & 0xff;
    WORD b2 = data[c] >> 8  & 0xff;
    WORD b1 = data[c]       & 0xff;
    buf << setfill('0') << setw(2) << hex << b1;
    buf << setfill('0') << setw(2) << hex << b2;
    buf << setfill('0') << setw(2) << hex << b3;
    buf << setfill('0') << setw(2) << hex << b4;
  }
  return buf.str();
}
void md5_padding(vector<BYTE>& msg){
  unsigned long count = msg.size();
  const unsigned long ibits = count * 8;
  WORD bits = count * 8;
  msg.push_back(0x80);
  bits += 8;
  // RFC1321 3.1: Padding is always performed, even if the length of the
  // message is already congruent to 448, modulo 512.
  while (bits % 512 != 448) {
    msg.push_back(0);
    bits += 8;
  }
  // RFC1321 3.2: These bits are appended as two 32-bit words and appended
  // low-order word first in accordance with the previous conventions.
  BYTE h4 = (BYTE)((ibits >> 56) & 0xff);
  BYTE h3 = (BYTE)((ibits >> 48) & 0xff);
  BYTE h2 = (BYTE)((ibits >> 40) & 0xff);
  BYTE h1 = (BYTE)((ibits >> 32) & 0xff);
  BYTE l4 = (BYTE)((ibits >> 24) & 0xff);
  BYTE l3 = (BYTE)((ibits >> 16) & 0xff);
  BYTE l2 = (BYTE)((ibits >> 8 ) & 0xff);
  BYTE l1 = (BYTE)((ibits      ) & 0xff);
  msg.push_back(l1);
  msg.push_back(l2);
  msg.push_back(l3);
  msg.push_back(l4);
  msg.push_back(h1);
  msg.push_back(h2);
  msg.push_back(h3);
  msg.push_back(h4);
}
