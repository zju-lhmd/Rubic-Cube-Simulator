// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#ifdef _WIN32
#include "targetver.h"
#endif

#ifdef linux
#endif

#ifdef _UNIX
#endif

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
using namespace std;

#include "Config.h"

#ifdef USE_GL

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#endif

#include "types.h"
#include "utilities.h"
