#include <platform.hpp>

#ifdef _WIN32
#include <windows.hpp>
#else
#include <iostream>
#include <unix.hpp>
#endif

namespace platform {

void Init() {
#ifdef _WIN32
    windows::Init();
#else
    unix::Init();
#endif
}

ConsoleColor GetConsoleColor() {
#ifdef _WIN32
    const auto output_handle = windows::GetOutputHandle();
    const auto buffer_info = windows::GetConsoleScreenBufferInfo(output_handle);
    return buffer_info.wAttributes & windows::GetColorMask();
#else
    return kDefaultColor;
#endif
}

void SetConsoleColor(const ConsoleColor& console_color) {
#ifdef _WIN32
    const auto output_handle = windows::GetOutputHandle();
    const auto buffer_info = windows::GetConsoleScreenBufferInfo(output_handle);
    // Save background and other attributes, set only foreground color
    SetConsoleTextAttribute(
        output_handle,
        buffer_info.wAttributes & ~windows::GetColorMask() | console_color);
#else
    std::wcout << console_color;
#endif
}

}  // namespace platform
