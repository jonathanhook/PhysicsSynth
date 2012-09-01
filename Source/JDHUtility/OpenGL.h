#pragma once
#if defined _WIN32
#define _CRT_SECURE_NO_WARNINGS
#define GLEW_STATIC 
#include <windows.h>
#include <GL/glew.h>
#include <glut.h>
#elif defined __APPLE__
#include <GL/glew.h>
#include <GLUT/glut.h>
#endif
