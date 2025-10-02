//DriveMouse.hpp
#pragma once
#include <SendTypes.hpp>



//--------------------����DLL������----------
#ifdef DLL1_EXPORTS
#define DLLAPI extern "C" __declspec(dllexport)//C�������ӷ�ʽ;����������DLL��
#else
#define DLLAPI extern "C" __declspec(dllimport)//C�������ӷ�ʽ;�������뵽DLL��
#endif


//--------------------ö��--------------------

#ifdef __cplusplus
extern "C" {
#endif

// -------------------- ��ʼ��/���� --------------------

// ��ʼ��ģ�飨���������ȣ�
// ���� true ��ʾ�ɹ�
DLLAPI bool InitializeDriverMouse();

// ж��ģ��
DLLAPI void ShutdownDriverMouse();

// -------------------- ������ --------------------

// ����ƶ���� dx/dy ��λΪ����
DLLAPI void MoveMouseRelative(int dx, int dy);

// �����ƶ���굽��Ļ���� x/y
DLLAPI void MoveMouseAbsolute(int x, int y);

// �����������ƶ��ӳ�ϵ��
DLLAPI void SetMouseSensitivity(float factor);

// -------------------- ���̿��� --------------------

// ����ĳ���������
DLLAPI void KeyDown(int vKey);

// �ɿ�ĳ���������
DLLAPI void KeyUp(int vKey);

// ������ϰ��������� Ctrl + C��
// vKeys ������������飬count Ϊ���鳤��
DLLAPI void SendKeyCombination(const int* vKeys, int count);

#ifdef __cplusplus
}
#endif





