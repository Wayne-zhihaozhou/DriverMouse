#pragma once
#include "SendTypes.hpp"

#ifdef DLL1_EXPORTS
#define DLLAPI extern "C" __declspec(dllexport)
#else
#define DLLAPI extern "C" __declspec(dllimport)
#endif


// ��ʼ������ģ��
DLLAPI Send::Error __stdcall IbSendInit(Send::SendType type, Send::InitFlags flags, void* argument);

// ���ٷ���ģ��
DLLAPI void __stdcall IbSendDestroy();

// ͬ������״̬
DLLAPI void __stdcall IbSendSyncKeyStates();

// 
DLLAPI VOID WINAPI IbSend_mouse_event(
    _In_ DWORD dwFlags,
    _In_ DWORD dx,
    _In_ DWORD dy,
    _In_ DWORD dwData,
    _In_ ULONG_PTR dwExtraInfo
);

// ======================
// C++ �ӿڷ�װ����
// ======================

namespace Send {

    // �ƶ����
    DLLAPI bool __stdcall IbSendMouseMove(uint32_t x, uint32_t y, Send::MoveMode mode);

    // �����
    DLLAPI bool __stdcall IbSendMouseClick(Send::MouseButton button);

    // ������
    DLLAPI bool __stdcall IbSendMouseWheel(int32_t movement);
}

