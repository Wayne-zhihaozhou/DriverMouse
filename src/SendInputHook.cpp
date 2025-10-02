// SendInputHook.cpp
#include"pch.h"
#include <SendInputHook.hpp>


// ��ʼ��ȫ������ָ��
std::unique_ptr<SendInputHook> g_sendInputHook = nullptr;

// ���캯������װ detour
SendInputHook::SendInputHook() {
    hook = false;
    IbDetourAttach(&GetAsyncKeyState_real, GetAsyncKeyState_detour);
    IbDetourAttach(&SendInput_real, SendInput_detour);
}

// ����������ж�� detour
SendInputHook::~SendInputHook() {
    IbDetourDetach(&SendInput_real, SendInput_detour);
    IbDetourDetach(&GetAsyncKeyState_real, GetAsyncKeyState_detour);
}

// ���� GetAsyncKeyState
SHORT WINAPI SendInputHook::GetAsyncKeyState_detour(int vKey) {
    if (!hook)
        return GetAsyncKeyState_real(vKey);
    return Send::g_send->get_key_state(vKey);
}

// ���� SendInput
UINT WINAPI SendInputHook::SendInput_detour(UINT cInputs, LPINPUT pInputs, int cbSize) {
    if (!hook)
        return SendInput_real(cInputs, pInputs, cbSize);
    return Send::g_send->send_input(pInputs, cInputs);
}