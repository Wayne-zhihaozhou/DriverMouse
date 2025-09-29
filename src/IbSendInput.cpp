#include "dll_export.hpp"
#include "globals.hpp"
#include <SendTypes.hpp>
#include <SendInputHook.hpp>

DLLAPI UINT WINAPI IbSendInput(
    _In_ UINT cInputs,
    _In_reads_(cInputs) LPINPUT pInputs,
    _In_ int cbSize
) {
    return main::send->send_input(pInputs, cInputs); // ���÷��ͺ���
}


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