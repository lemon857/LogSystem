#pragma once

#include <string>
#include <vector>
#include <fstream>

// Enable debugging in console
// #define __LOG_CONSOLE__
// Enable debugging in file
// #define __LOG_FILE__
// Enable debugging with date and time
// #define __LOG_DATETIME__

// In format string {0} {1} ... was a random object, which can use in std::to_string
// 0, 1 ... sign index in arguments list after format string

class LogSystem {
  static void FastPrintDate();
  
  static std::string relativePathToDirectory_;
  static std::string path_;
  
public:
  struct hex {
    hex(long long number, bool sugar = true) : m_number(number), m_sugar(sugar) {}

    hex() = delete;

    long long m_number;
    bool m_sugar;
  };

  enum class ELogLevel {
    kNull,
    kDebug,
    kInfo,
    kWarn,
    kError,
    kCritical
  };

  LogSystem() = delete;
  LogSystem(LogSystem&&) = delete;
  LogSystem operator=(LogSystem&) = delete;
  LogSystem operator=(LogSystem&&) = delete;

  static bool Init();

  static bool InitFilestream(std::string relativePathToDirectory);
  static void UninitFilestream();

  static void FastLog(std::string&& string);
  static void FastLog(std::string& string);
  static void FastLogChar(char ch);

  static void Logf(ELogLevel level, std::string&& fstring);

  template<typename... _Args>
	static void Logf(ELogLevel level, std::string&& fstring, _Args &&...args);
};

namespace std {

string to_string(LogSystem::hex number);
string to_string(string str);

}

template<typename... _Args>
void LogSystem::Logf(ELogLevel level, std::string&& fstring, _Args &&...args)	{
std::vector<std::string> strs;

(strs.push_back(std::to_string(args)), ...);

#ifdef __LOG_DATETIME__
FastPrintDate();
#endif

switch (level) {
  case ELogLevel::kInfo:
  FastLog("[\033[32minfo\033[39m] ");
  break;
case ELogLevel::kDebug:
  FastLog("[\033[34mdebug\033[39m] ");
  break;
case ELogLevel::kWarn:
  FastLog("[\033[33mwarn\033[39m] ");
  break;
case ELogLevel::kError:
  FastLog("[\033[31merror\033[39m] ");
  break;
case ELogLevel::kCritical:
  FastLog("[\033[37m\033[41mcritial\033[39m\033[49m] ");
  break;
  }

  size_t start = -1;
  size_t size = fstring.size();
  for (size_t i = 0; i < size; ++i) {
    if (fstring[i] == '\\' && (i + 1) < size && fstring[i + 1] == '{') {
      ++i;
    } else {
      if (fstring[i] == '{') {
        ++i;
        start = i;
        while (fstring[i] != '}' && i < size) {
          ++i;
        }
        int j = std::stoi(fstring.substr(start, i));
        FastLog(strs[j]);
        continue;
      }
    }
    FastLogChar(fstring[i]);
  }
  FastLogChar('\n');
}