#pragma once


#ifdef DLL1_EXPORTS
#define DLLAPI extern "C" __declspec(dllexport)//���������� DLL
#else
#define DLLAPI extern "C" __declspec(dllimport)//�� DLL ���뺯��
#endif


