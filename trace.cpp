#include "trace.h"

string padding(const char* msg) {
  vector<BYTE> bytes;
  for(int c = 0; c < strlen(msg); c++)
    bytes.push_back((BYTE)msg[c]);
  md5_padding(bytes);
  ostringstream buf;
  for(int c = 0; c < bytes.size(); c++)
    buf << setfill('0') << setw(2) << hex << (int)bytes[c];
  return buf.str();
}
int main(int argc, const char** argv) {
  const char* samples[] = {
    "", "a", "abc", "message digest", "abcdefghijklmnopqrstuvwxyz",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
    "12345678901234567890123456789012345678901234567890123456789012345678901234567890"
  };
  for(int c = 0; c < 7; c++) {
    cout << samples[c] << endl;
    string abcd_trace;
    cout << "md5 hash:" << md5(samples[c], abcd_trace) << endl;
    cout << "ABCD traces:" << endl << abcd_trace;
    cout << "padded bytes: " << padding(samples[c]) << endl;
  }
}
