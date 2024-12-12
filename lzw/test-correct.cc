#include <iostream>
#include <cmath>
#include <pthread.h>
#include <cassert>
#include <cstring>
#include <fstream>

#include "utils.hh"

#include "lzw-baseline.hh"


int main(int argc, char** argv) {
  FixateCore(0);

  std::cout << "Running " << argv[0] << std::endl;


}

void TestSkkv() {
  auto compressedGold = ReadFileBinary("data/01-skkv.in");
  auto decompressedGold = ReadFileBinary("data/01-skkv.out");
}
