#include <InputSimulator.hpp>
#include <SendInputHook.hpp>
#include <IbSendInput.hpp>
#include <Logitech.hpp>



using namespace Send;

DLLAPI Send::Error __stdcall IbSendInit(SendType type, InitFlags flags, void* argument) {
    if (type != SendType::Logitech) {
        return Error::InvalidArgument;  // ֻ֧�� Logitech
    }

    auto logitech = std::make_unique<Type::Internal::Logitech>();
    logitech->create_base(&SendInputHook::GetAsyncKeyState_real);
    Error error = logitech->create();
    if (error != Error::Success)
        return error;

    main::send = std::move(logitech); // ����ȫ�ֶ���
    return Error::Success;
}

DLLAPI void __stdcall IbSendDestroy() {
    IbSendInputHook(HookCode::Destroy);

    if (!main::send)
        return;
    main::send->destroy(); // ����ȫ�ֶ���
    main::send.reset();
}


DLLAPI void __stdcall IbSendSyncKeyStates() {
    main::send->sync_key_states(); // ͬ������״̬
}