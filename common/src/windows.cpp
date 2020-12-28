#include <windows.hpp>

#include <iostream>

#include <fcntl.h>
#include <io.h>

namespace windows {

void Init() {
  // Allow output unicode characters
  _setmode(_fileno(stdout), _O_U16TEXT);
}

HANDLE GetOutputHandle() {
  return GetStdHandle(STD_OUTPUT_HANDLE);
}

CONSOLE_SCREEN_BUFFER_INFO GetConsoleScreenBufferInfo(HANDLE output_handle) {
  CONSOLE_SCREEN_BUFFER_INFO info;
  GetConsoleScreenBufferInfo(output_handle, &info);
  return info;
}

WORD GetColorMask() {
  return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
}

}  // namespace windows
