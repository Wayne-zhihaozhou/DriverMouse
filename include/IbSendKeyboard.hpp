//IbSendKeyboard.hpp
#pragma once
#include <Windows.h>
#include "dll_export.hpp"
#include "SendTypes.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    // �ͼ������¼�
    DLLAPI VOID WINAPI IbSend_keybd_event(
        _In_ BYTE bVk,
        _In_ BYTE bScan,
        _In_ DWORD dwFlags,
        _In_ ULONG_PTR dwExtraInfo
    );

#ifdef __cplusplus
}
#endif

// �߼���װ���̲���
#ifdef __cplusplus
namespace Send {

    // ����ָ����
    DLLAPI bool __stdcall IbSendKeybdDown(uint16_t vk);

    // �ͷ�ָ����
    DLLAPI bool __stdcall IbSendKeybdUp(uint16_t vk);

    // ���²��ͷ�ָ�������ɸ������μ�
    DLLAPI bool __stdcall IbSendKeybdDownUp(uint16_t vk, KeyboardModifiers modifiers);

}  // namespace Send
#endif
