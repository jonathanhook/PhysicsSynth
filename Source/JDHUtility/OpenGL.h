#pragma once
#if defined _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <glut.h>
#include <GL/glu.h>
#define GLUT_WINDOWING
#elif defined __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#define IOS_WINDOWING
#elif TARGET_OS_MAC
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#define GLUT_WINDOWING
#else
#endif
#endif
