#pragma once

#if defined _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <gl/GL.h>
#elif defined __APPLE__
#include <OpenGL/GL.h>
#endif 
