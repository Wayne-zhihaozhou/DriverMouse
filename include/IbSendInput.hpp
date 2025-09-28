#pragma once
#include <Windows.h>
#include "dll_export.hpp"
#include "SendTypes.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    // ���������¼�
    DLLAPI UINT WINAPI IbSendInput(
        _In_ UINT cInputs,
        _In_reads_(cInputs) LPINPUT pInputs,
        _In_ int cbSize
    );

    // ��װ�򴥷����빳��
    DLLAPI void __stdcall IbSendInputHook(Send::Error code);

#ifdef __cplusplus
}
#endif
