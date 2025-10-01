#include <IbSendBase.hpp>
#include <Logitech.hpp>
#include <IbSendInput.hpp>

// ��ʼ������ģ�飨��֧�� Logitech��������������ȫ�ַ��Ͷ���
DLLAPI Send::Error __stdcall IbSendInit(Send::SendType type, Send::InitFlags flags, void* argument) {
    if (type != Send::SendType::Logitech) {
        return Send::Error::InvalidArgument;  // ֻ֧�� Logitech
    }

    auto logitech = std::make_unique<Send::Type::Internal::Logitech>();
    logitech->create_base(&SendInputHook::GetAsyncKeyState_real);
    Send::Error error = logitech->create();
    if (error != Send::Error::Success)
        return error;

    Send::g_send = std::move(logitech); 
    return Send::Error::Success;
}


// ���ٷ���ģ�飬�ͷ�ȫ�ַ��Ͷ���
DLLAPI void __stdcall IbSendDestroy() {
    IbSendInputHook(Send::HookCode::Destroy);

    if (!Send::g_send)
        return;
    Send::g_send->destroy();
    Send::g_send.reset();
}

// ͬ������״̬������ģ��
DLLAPI void __stdcall IbSendSyncKeyStates() {
    Send::g_send->sync_key_states(); 
}