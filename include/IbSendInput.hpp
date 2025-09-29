#pragma once
#include <Windows.h>
#include "dll_export.hpp"
#include "SendTypes.hpp"
#include "SendInputHook.hpp"

//using namespace Send;


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


//��д
DLLAPI void __stdcall IbSendInputHook(Send::HookCode code) {
    switch (code) {
    case Send::HookCode::InitOnly:
        if (!g_sendInputHook)
            g_sendInputHook = std::make_unique<SendInputHook>();
        break;

    case Send::HookCode::Destroy:
        g_sendInputHook.reset();  // �Զ����� SendInputHook
        break;

    case Send::HookCode::On:
        if (!g_sendInputHook)
            g_sendInputHook = std::make_unique<SendInputHook>();
        SendInputHook::hook = true; // ���ù���
        break;

    case Send::HookCode::Off:
        SendInputHook::hook = false; // ���ù���
        break;
    }
}


//DLLAPI void __stdcall IbSendInputHook(Send::HookCode code) {
//    switch (code) {
//    case Send::HookCode::InitOnly:
//        sendinput_hook.create(); // ��ʼ������
//        break;
//    case Send::HookCode::Destroy:
//        sendinput_hook.destroy(); // ж�ع���
//        break;
//    case Send::HookCode::On:
//        if (!sendinput_hook.created())
//            sendinput_hook.create();
//        sendinput_hook->hook = true; // ���ù���
//        break;
//    case Send::HookCode::Off:
//        sendinput_hook->hook = false; // ���ù���
//        break;
//    }
//}

