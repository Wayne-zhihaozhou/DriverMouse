#pragma once
#include <Windows.h>
#include <stdint.h>
#include "SendTypes.hpp"
#include "dll_export.hpp"

//// ��ʼ������ģ��
//DLLAPI Send::Error __stdcall IbSendInit(Send::SendType type, Send::InitFlags flags, void* argument);
//
//// ���ٷ���ģ��
//DLLAPI void __stdcall IbSendDestroy();
//
//// ͬ������״̬
//DLLAPI void __stdcall IbSendSyncKeyStates();

#pragma region API 1

//// ���������¼�
//DLLAPI UINT WINAPI IbSendInput(
//    _In_ UINT cInputs,                    // number of input in the array
//    _In_reads_(cInputs) LPINPUT pInputs,  // array of inputs
//    _In_ int cbSize                       // sizeof(INPUT)
//);
//
//// ��װ�򴥷����빳��
//DLLAPI void __stdcall IbSendInputHook(Send::HookCode code);

#pragma endregion

#pragma region API 2

//// ģ������¼�
//DLLAPI VOID WINAPI IbSend_mouse_event(
//    _In_ DWORD dwFlags,         //MOUSEEVENTF_
//    _In_ DWORD dx,
//    _In_ DWORD dy,
//    _In_ DWORD dwData,
//    _In_ ULONG_PTR dwExtraInfo
//);

//// ģ������¼�
//DLLAPI VOID WINAPI IbSend_keybd_event(
//    _In_ BYTE bVk,
//    _In_ BYTE bScan,
//    _In_ DWORD dwFlags,         //KEYEVENTF_
//    _In_ ULONG_PTR dwExtraInfo
//);

#pragma endregion

#pragma region API 3

//// �ƶ���굽ָ��λ��
//DLLAPI bool __stdcall IbSendMouseMove(uint32_t x, uint32_t y, Send::MoveMode mode);
//
//// �����ָ������
//DLLAPI bool __stdcall IbSendMouseClick(Send::MouseButton button);
//
//// ģ�������ֹ���
//DLLAPI bool __stdcall IbSendMouseWheel(int32_t movement);

//// ����ָ�����̰���
//DLLAPI bool __stdcall IbSendKeybdDown(uint16_t vk);
//
//// �ͷ�ָ�����̰���
//DLLAPI bool __stdcall IbSendKeybdUp(uint16_t vk);
//
//// ���²��ͷ�ָ��������ͬʱ�ɸ������μ�
//DLLAPI bool __stdcall IbSendKeybdDownUp(uint16_t vk, Send::KeyboardModifiers modifiers);

#pragma endregion
