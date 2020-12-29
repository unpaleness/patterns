#pragma once

#ifdef _WIN32
#include <windows.hpp>
#else
#include <string>
#include <unix.hpp>
#endif

namespace platform {

#ifdef _WIN32
typedef WORD ConsoleColor;
static const ConsoleColor kDefaultColor = static_cast<WORD>(
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
static const ConsoleColor kRedColor =
    static_cast<WORD>(FOREGROUND_RED | FOREGROUND_INTENSITY);
static const ConsoleColor kGreenColor =
    static_cast<WORD>(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#else
typedef std::wstring ConsoleColor;
static const ConsoleColor kDefaultColor = L"\033[0m";
static const ConsoleColor kRedColor = L"\033[31m";
static const ConsoleColor kGreenColor = L"\033[32m";
#endif

void Init();

ConsoleColor GetConsoleColor();

void SetConsoleColor(const ConsoleColor& console_color);

}  // namespace platform
