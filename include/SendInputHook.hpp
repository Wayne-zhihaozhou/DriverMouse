class SendInputHook {
public:
    static inline decltype(SendInput)* SendInput_real = SendInput; // ԭʼ SendInput
    static UINT WINAPI SendInput_detour(UINT cInputs, LPINPUT pInputs, int cbSize) {
        if (!hook)
            return SendInput_real(cInputs, pInputs, cbSize);
        return main::send->send_input(pInputs, cInputs); // �ض�������
    }

    static inline decltype(GetAsyncKeyState)* GetAsyncKeyState_real = GetAsyncKeyState; // ԭʼ GetAsyncKeyState
    static SHORT WINAPI GetAsyncKeyState_detour(int vKey) {
        if (!hook)
            return GetAsyncKeyState_real(vKey);
        return main::send->get_key_state(vKey); // ��ȡ����״̬
    }

public:
    static inline bool hook;

    SendInputHook() {
        hook = false;
        IbDetourAttach(&GetAsyncKeyState_real, GetAsyncKeyState_detour); // ��װ����
        IbDetourAttach(&SendInput_real, SendInput_detour);
    }

    ~SendInputHook() {
        IbDetourDetach(&SendInput_real, SendInput_detour); // ж�ع���
        IbDetourDetach(&GetAsyncKeyState_real, GetAsyncKeyState_detour);
    }
};
ib::HolderB<SendInputHook> sendinput_hook; // ���ӹ���
