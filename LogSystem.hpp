#pragma once

#include <string>
#include <vector>

// Enable debugging in console
// #define __LOG_CONSOLE__
// Enable debugging in file
// #define __LOG_FILE__
// Enable debugging with date and time
// #define __LOG_DATETIME__
// #define __LOG_DATETIME_FORMAT__ "%Y-%m-%d %H:%M:%S"

// In format string {0} {1} ... was a random object, which can use in std::to_string
// 0, 1 ... sign index in arguments list after format string

struct HexFormatLogging {
  HexFormatLogging(long long number, bool sugar = true) : m_number(number), m_sugar(sugar) {}

  HexFormatLogging() = delete;

  long long m_number;
  bool m_sugar;
};

namespace std {

string to_string(HexFormatLogging number);
string to_string(string str);

}

class LogSystem
{	
public:
	~LogSystem() = delete;
	LogSystem() = delete;

	LogSystem(const LogSystem&) = delete;
	LogSystem(const LogSystem&&) = delete;
	LogSystem& operator=(const LogSystem&) = delete;
	LogSystem& operator=(const LogSystem&&) = delete;
	
	static void init_file_log(std::string relative_path_to_directory);
	static void uninit_file_log();

	static void log_info(std::string msg);
	static void log_warn(std::string msg);
	static void log_error(std::string msg);
	static void log_crit(std::string msg);

	template<typename... _Args>
	static void info(std::string text, _Args &&...args)	{
    std::vector<std::string> strs;

    (strs.push_back(std::to_string(args)), ...);

    std::string temp;
    size_t start = -1;
    size_t size = text.size();
    for (size_t i = 0; i < size; ++i) {
      if (text[i] == '\\' && (i + 1) < size && text[i + 1] == '{') {
        ++i;
      } else {
        if (text[i] == '{') {
          ++i;
          start = i;
          while (text[i] != '}' && i < text.size()) {
            ++i;
          }
          int j = std::stoi(text.substr(start, i));
          temp += strs[j];
          continue;
        }
      }
      temp += text[i];
    }
    
    log_info(temp);
	}

	template<typename... _Args>
	static void warn(std::string text, _Args &&...args)	{
		std::vector<std::string> strs;

		(strs.push_back(std::to_string(args)), ...);

		std::string temp;
    size_t start = -1;
    size_t size = text.size();
    for (size_t i = 0; i < size; ++i) {
      if (text[i] == '\\' && (i + 1) < size && text[i + 1] == '{') {
        ++i;
      } else {
        if (text[i] == '{') {
          ++i;
          start = i;
          while (text[i] != '}' && i < text.size()) {
            ++i;
          }
          int j = std::stoi(text.substr(start, i));
          temp += strs[j];
          continue;
        }
      }
      temp += text[i];
    }

		log_warn(temp);
	}

	template<typename... _Args>
	static void error(std::string text, _Args &&...args) {
		std::vector<std::string> strs;

		(strs.push_back(std::to_string(args)), ...);

		std::string temp;
    size_t start = -1;
    size_t size = text.size();
    for (size_t i = 0; i < size; ++i) {
      if (text[i] == '\\' && (i + 1) < size && text[i + 1] == '{') {
        ++i;
      } else {
        if (text[i] == '{') {
          ++i;
          start = i;
          while (text[i] != '}' && i < text.size()) {
            ++i;
          }
          int j = std::stoi(text.substr(start, i));
          temp += strs[j];
          continue;
        }
      }
      temp += text[i];
    }

		log_error(temp);
	}

	template<typename... _Args>
	static void critical(std::string text, _Args &&...args)	{
		std::vector<std::string> strs;

		(strs.push_back(std::to_string(args)), ...);

		std::string temp;
    size_t start = -1;
    size_t size = text.size();
    for (size_t i = 0; i < size; ++i) {
      if (text[i] == '\\' && (i + 1) < size && text[i + 1] == '{') {
        ++i;
      } else {
        if (text[i] == '{') {
          ++i;
          start = i;
          while (text[i] != '}' && i < text.size()) {
            ++i;
          }
          int j = std::stoi(text.substr(start, i));
          temp += strs[j];
          continue;
        }
      }
      temp += text[i];
    }

		log_crit(temp);
	}
private:
	static std::string m_path;
	static std::string m_path_directory;
};