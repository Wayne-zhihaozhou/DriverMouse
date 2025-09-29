// SendInputHook.cpp
#include "SendInputHook.hpp"

// ��ʼ��ȫ������ָ��
std::unique_ptr<SendInputHook> g_sendInputHook = nullptr;

// ��ʼ����̬��Ա
//decltype(SendInputHook::SendInput_real) SendInputHook::SendInput_real = SendInput;
//decltype(SendInputHook::GetAsyncKeyState_real) SendInputHook::GetAsyncKeyState_real = GetAsyncKeyState;
//bool SendInputHook::hook = false;


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
    return main::send->get_key_state(vKey);
}

// ���� SendInput
UINT WINAPI SendInputHook::SendInput_detour(UINT cInputs, LPINPUT pInputs, int cbSize) {
    if (!hook)
        return SendInput_real(cInputs, pInputs, cbSize);
    return main::send->send_input(pInputs, cInputs);
}