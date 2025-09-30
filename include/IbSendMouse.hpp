#pragma once
#include <Windows.h>
#include "dll_export.hpp"
#include "SendTypes.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    // �ͼ�����¼�
    DLLAPI VOID WINAPI IbSend_mouse_event(
        _In_ DWORD dwFlags,
        _In_ DWORD dx,
        _In_ DWORD dy,
        _In_ DWORD dwData,
        _In_ ULONG_PTR dwExtraInfo
    );

#ifdef __cplusplus
}
#endif

// �߼���װ������
#ifdef __cplusplus
namespace Send {

    // �ƶ����
    DLLAPI bool __stdcall IbSendMouseMove(uint32_t x, uint32_t y, MoveMode mode);

    // �����
    DLLAPI bool __stdcall IbSendMouseClick(MouseButton button);

    // ������
    DLLAPI bool __stdcall IbSendMouseWheel(int32_t movement);

}  // namespace Send
#endif
