#include "LogSystem.hpp"

#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <filesystem>

#if defined(_WIN32)
#define PATH_PIECE "\\"
#elif defined(__linux__)
#define PATH_PIECE "/"
#endif

std::string LogSystem::path_;
std::string LogSystem::relativePathToDirectory_;

bool LogSystem::Init() {
  std::cout.sync_with_stdio(false);
  return true;
}

bool LogSystem::InitFilestream(std::string relativePathToDirectory) {
// Not implemented now, maybe later
  return false;
}
void LogSystem::UninitFilestream() {
// Not implemented now, maybe later
}

void LogSystem::FastLog(std::string&& string) {
  size_t size = string.size();
  for (size_t i = 0; i < size; ++i) {
    std::cout << string[i];
  }
}

void LogSystem::FastLog(std::string& string) {
  size_t size = string.size();
  for (size_t i = 0; i < size; ++i) {
    std::cout << string[i];
  }
}

void LogSystem::FastLogChar(char ch) {
  std::cout << ch;
}

void LogSystem::Logf(ELogLevel level, std::string&& fstring) {

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
  size_t size = fstring.size();
  for (size_t i = 0; i < size; ++i) {
    std::cout << fstring[i];
  }
  std::cout << '\n';
}

void LogSystem::FastPrintDate() {
  auto now = std::chrono::high_resolution_clock::now();

  std::time_t now_time = std::chrono::high_resolution_clock::to_time_t(now);

  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

  std::cout << "[\033[36m" << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S")
  << '.' << std::setfill('0') << std::setw(3) << milliseconds.count() << "\033[39m] ";
}

namespace std {

string to_string(LogSystem::hex number) {
  stringstream ss;
  if (number.m_sugar) ss << "0x";
  ss << std::hex << std::uppercase << number.m_number;
  return ss.str();
}

string to_string(string str) {
	return str;
}

}