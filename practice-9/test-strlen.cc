#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <cstring>

#include "utils.hh"

extern "C" uint32_t __cdecl MyStrlen(const char* c_str);

int main(int argc, char** argv) {
  FixateCore(1);

  std::cout << "Running " << argv[0] << std::endl;


  const char* args[] = {
    "",
    "h",
    "ha",
    "hah",
    "haha",
    "hahah",
    "hahaha",
    "hahahah",
    "hahahaha",
    "hahahahah",
    "hahahahaha",
    "hahahahahah",
    "hahahahahaha",
    "abcdefghijklm",
    "abcdefghijklmn",
    "abcdefghijklmno",
    "abcdefghijklmnop",
    "abcdefghijklmnopq",
    "abcdefghijklmnopqr",
    "abcdefghijklmnopqrs",
    "abcdefghijklmnopqrst",
    "abcdefghijklmnopqrstu",
    "abcdefghijklmnopqrstuv",
    "abcdefghijklmnopqrstuvw",
    "abcdefghijklmnopqrstuvwx",
    "abcdefghijklmnopqrstuvwxy",
    "abcdefghijklmnopqrstuvwxyz",
  };
  std::cout << "Testing regular args (" << sizeof(args) / sizeof(const char*) << " samples)" << std::endl;

  size_t errors = 0;
  for (auto arg : args) {
    const auto realAnswer = std::strlen(arg);
    const auto myAnswer = MyStrlen(arg);
    errors += myAnswer != realAnswer;
    if (errors > 0) {
      std::cout << "Erroneous string: '" << arg << "'" << std::endl;
      return 1;
    }
  }

  if (errors > 0) {
    std::cerr << "Encountered " << errors << " errors" << std::endl;
    return 1;
  }

  std::string longStrings[] = {
    std::string(1000, 'a'),
    std::string(10000, 'b'),
    std::string(999, 'b'),
    std::string(998, 'b'),
    std::string(99999, 'b'),
    std::string(100001, 'b'),

  };
  std::cout << "Testing long strings (" << sizeof(longStrings) / sizeof(std::string) << " samples)" << std::endl;
  errors = 0;
  for (const auto &arg : longStrings) {
    const auto realAnswer = std::strlen(arg.c_str());
    const auto myAnswer = MyStrlen(arg.c_str());
    errors += myAnswer != realAnswer;
  }

  if (errors > 0) {
    std::cerr << "Encountered " << errors << " errors" << std::endl;
    return 1;
  }

  constexpr int REPETIIONS = 100;
  std::vector<double> measurements{REPETIIONS, 0};

  std::cout << "\n\n\nStarting the measurements (" << REPETIIONS << " repetitions per call)" << std::endl;
  for (uint32_t stringLength = 1; stringLength <= 100'000'000; stringLength *= 10) {
    std::string sample = std::string(stringLength + 1, 'a');

    // touch every char to minimize pagefaults
    bool change = false;
    for (auto& c : sample) {
      c = change ? 'b' : 'a';
      change = !change;
    }

    assert (MyStrlen(sample.c_str()) == std::strlen(sample.c_str()));
    assert(*sample.end() == '\0');
    measurements.assign(REPETIIONS, 0);
    for (auto& m : measurements) {
      m = measure([&] { MyStrlen(sample.c_str()); });
    }
    auto statistics = aggregate(measurements);
    std::cout
      << "    With " << stringLength << " chars: "
      << statistics.ToJson() << std::endl;
  }
}

