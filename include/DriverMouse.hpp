//DriveMouse.hpp
#pragma once
//#include "SendTypes.hpp"
//#include "IbSendBase.hpp"
//#include "IbSendMouse.hpp"
//#include "IbSendInput.hpp"
//#include "IbSendKeyboard.hpp"




// IbSendMouseCAPI.hpp
#pragma once
#include "dll_export.hpp"
#include <SendTypes.hpp>


// ----------------------------
// DLL ����/�����궨��
// ----------------------------
#ifdef DLL1_EXPORTS
// ���� DLL ʱ���� DLL1_EXPORTS����������
#define DLLAPI extern "C" __declspec(dllexport)
#else
// �ͻ���ʹ�� DLL ʱ�����뺯��
#define DLLAPI extern "C" __declspec(dllimport)
#endif

// ----------------------------
// ����Լ���꣨��ѡ��
// ----------------------------
#ifndef WINAPI
#define WINAPI WINAPI  // Windows Ĭ�ϵ���Լ��
#endif

// ----------------------------
// ö��ʾ��
// ----------------------------
typedef enum {
    MOVE_ABSOLUTE = 0,
    MOVE_RELATIVE = 1
} MoveMode;

#ifdef __cplusplus
extern "C" {
#endif

    // ----------------------------
    // DLL ������������ʾ��
    // ----------------------------

    // ����ƶ�
    DLLAPI bool WINAPI IbSendMouse_Move(int x, int y, MoveMode mode);

    // �����
    DLLAPI bool WINAPI IbSendMouse_Click(int button);

    // ������
    DLLAPI bool WINAPI IbSendMouse_Wheel(int movement);

#ifdef __cplusplus
}
#endif


/*

// DriverMouseAPI.hpp
#pragma once

#ifdef DRIVER_MOUSE_EXPORTS
#define DLLAPI extern "C" __declspec(dllexport)
#else
#define DLLAPI extern "C" __declspec(dllimport)
#endif

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



*/

