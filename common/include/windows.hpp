#pragma once

#include <windows.h>

namespace windows {

void Init();

HANDLE GetOutputHandle();

CONSOLE_SCREEN_BUFFER_INFO GetConsoleScreenBufferInfo(HANDLE output_handle);

WORD GetColorMask();

}  // namespace windows
