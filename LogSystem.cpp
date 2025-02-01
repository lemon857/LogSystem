#include "LogSystem.hpp"

#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <filesystem>

#if defined(_WIN32)
#include <Windows.h>
#define PATH_PIECE "\\"
#elif defined(__linux__)
#define PATH_PIECE "/"
#endif

std::string LogSystem::m_path;
std::string LogSystem::m_path_directory;

std::string get_current_date_time() {
#ifdef __LOG_DATETIME__
	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);

	auto tim = std::chrono::high_resolution_clock::now();

	auto sec = std::chrono::duration_cast<std::chrono::milliseconds>(tim.time_since_epoch()).count();

	std::string tmp = std::to_string(sec);

	char buffer[128];
	strftime(buffer, sizeof(buffer), __LOG_DATETIME_FORMAT__, now);
	return std::string(buffer) + "." + tmp.substr(tmp.size() - 3);
#elif
  return "";
#endif
}

void LogSystem::init_file_log(std::string relative_path_to_directory) {
  m_path_directory = relative_path_to_directory;
#ifdef __LOG_FILE__
	m_path = relative_path_to_directory + PATH_PIECE + "lastest.log";
	std::ofstream stream(m_path, std::ios::out);
	if (stream.is_open())	{
		stream << "";
		stream.close();
	}
#endif
}

void LogSystem::uninit_file_log() {
#ifdef __LOG_FILE__
  std::filesystem::create_directory(m_path_directory);
	if (!std::filesystem::exists(m_path_directory + PATH_PIECE + "lastest.log")) return;
  std::time_t t = std::time(nullptr);
  std::tm* now = std::localtime(&t);
  char buffer[128];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", now);

  std::filesystem::copy_file(m_path_directory + PATH_PIECE + "lastest.log", 
    m_path_directory + PATH_PIECE + std::string(buffer) + ".log");
#endif
}

void LogSystem::log_info(std::string msg) {
#if defined(__LOG_CONSOLE__) && defined(_WIN32)
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);

#ifdef __LOG_DATETIME__
	std::cout << "[" << get_current_date_time() << "] ";
#endif

	SetConsoleTextAttribute(h, (((0 << 4) | 2)));
	std::cout << "[info";
	SetConsoleTextAttribute(h, (((0 << 4) | 7)));
	std::cout << "] " << msg << "\n";
#elif defined(__LOG_CONSOLE__) && defined(__linux__)

#ifdef __LOG_DATETIME__
std::cout << "[\033[36m" << get_current_date_time() << "\033[39m] ";
#endif

	std::cout << "[\033[32minfo\033[39m] " << msg << "\n";
#endif

#ifdef __LOG_FILE__
	std::ofstream stream(m_path, std::ios::app);
	if (stream.is_open()) {
		stream << "[" + get_current_date_time() + "] [info] " + msg + "\n";
		stream.close();
	}
#endif
}

void LogSystem::log_warn(std::string msg) {
#if defined(__LOG_CONSOLE__) && defined(_WIN32)
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);

#ifdef __LOG_DATETIME__
	std::cout << "[" << get_current_date_time() << "] ";
#endif

	SetConsoleTextAttribute(h, (((0 << 4) | 14)));
	std::cout << "[warn";
	SetConsoleTextAttribute(h, (((0 << 4) | 7)));
	std::cout << "] " << msg << "\n";
#elif defined(__LOG_CONSOLE__) && defined(__linux__)

#ifdef __LOG_DATETIME__
std::cout << "[\033[36m" << get_current_date_time() << "\033[39m] ";
#endif

	std::cout << "[\033[33mwarn\033[39m] " << msg << "\n";
#endif

#ifdef __LOG_FILE__
	std::ofstream stream(m_path, std::ios::app);
	if (stream.is_open()) {
		stream << "[" + get_current_date_time() + "] [warn] " + msg + "\n";
		stream.close();
	}
#endif
}

void LogSystem::log_error(std::string msg) {
#if defined(__LOG_CONSOLE__) && defined(_WIN32)
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);

#ifdef __LOG_DATETIME__
	std::cout << "[" << get_current_date_time() << "] ";
#endif

	SetConsoleTextAttribute(h, (((0 << 4) | 4)));
	std::cout << "[error";
	SetConsoleTextAttribute(h, (((0 << 4) | 7)));
	std::cout << "] " << msg << "\n";
#elif defined(__LOG_CONSOLE__) && defined(__linux__)

#ifdef __LOG_DATETIME__
std::cout << "[\033[36m" << get_current_date_time() << "\033[39m] ";
#endif

	std::cout << "[\033[31merror\033[39m] " << msg << "\n";
#endif

#ifdef __LOG_FILE__
	std::ofstream stream(m_path, std::ios::app);
	if (stream.is_open())
	{
		stream << "[" + get_current_date_time() + "] [error] " + msg + "\n";
		stream.close();
	}
#endif
}

void LogSystem::log_crit(std::string msg) {
#if defined(__LOG_CONSOLE__) && defined(_WIN32)
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);

#ifdef __LOG_DATETIME__
	std::cout << "[" << get_current_date_time() << "] ";
#endif

	SetConsoleTextAttribute(h, (((4 << 4) | 15)));
	std::cout << "[critical";
	SetConsoleTextAttribute(h, (((0 << 4) | 7)));
	std::cout << "] " << msg << "\n";
#elif defined(__LOG_CONSOLE__) && defined(__linux__)

#ifdef __LOG_DATETIME__
std::cout << "[\033[36m" << get_current_date_time() << "\033[39m] ";
#endif

	std::cout << "[\033[37m\033[41mcritial\033[39m\033[49m] " << msg << "\n";
#endif

#ifdef __LOG_FILE__
	std::ofstream stream(m_path, std::ios::app);
	if (stream.is_open())
	{
		stream << "[" + get_current_date_time() + "] [critical] " + msg + "\n";
		stream.close();
	}
#endif
}

namespace std {

string to_string(HexFormatLogging number) {
  stringstream ss;
  if (number.m_sugar) ss << "0x";
  ss << std::hex << std::uppercase << number.m_number;
  return ss.str();
}

string to_string(string str) {
	return str;
}

}