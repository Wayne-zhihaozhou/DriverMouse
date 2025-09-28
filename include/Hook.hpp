#pragma once
#include "dll_export.hpp"
#include <SendTypes.hpp>
#include "SendInputHook.hpp"
using namespace Send;

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
