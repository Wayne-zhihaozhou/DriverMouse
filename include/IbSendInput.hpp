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
    DLLAPI void __stdcall IbSendInputHook(Send::HookCode code);

#ifdef __cplusplus
}
#endif


DLLAPI void __stdcall IbSendInputHook(HookCode code) {
    switch (code) {
    case HookCode::InitOnly:
        sendinput_hook.create(); // ��ʼ������
        break;
    case HookCode::Destroy:
        sendinput_hook.destroy(); // ж�ع���
        break;
    case HookCode::On:
        if (!sendinput_hook.created())
            sendinput_hook.create();
        sendinput_hook->hook = true; // ���ù���
        break;
    case HookCode::Off:
        sendinput_hook->hook = false; // ���ù���
        break;
    }
}

