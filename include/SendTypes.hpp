// SendTypes.hpp
#pragma once
#include <WinUser.h>
#include <cstdint>

//-------------------- ����DLL������ ----------
#ifdef DLL1_EXPORTS
#define DLLAPI  extern "C" __declspec(dllexport)//C�������ӷ�ʽ;����������DLL��
#else
#define DLLAPI  extern "C" __declspec(dllimport)//C�������ӷ�ʽ;�������뵽DLL��
#endif




