//ibSendBase.cpp
#include"pch.h"
#include "Logitech.hpp"
#include "SendInputHook.hpp"



// ��ʼ������ģ�飨��֧�� Logitech��������������ȫ�ַ��Ͷ���
DLLAPI Send::Error WINAPI IbSendInit(Send::SendType type, Send::InitFlags flags, void* argument) {
    if (type != Send::SendType::Logitech) {
        return Send::Error::InvalidArgument;  // ֻ֧�� Logitech
    }
    auto logitech = std::make_unique<Send::Internal::Logitech>();//���޸�,����ȫ�ֱ���
    Send::Error error = logitech->create();
    if (error != Send::Error::Success)
        return error;

    Send::g_send = std::move(logitech); 
    return Send::Error::Success;
}


// ���ٷ���ģ�飬�ͷ�ȫ�ַ��Ͷ���
DLLAPI void WINAPI IbSendDestroy() {

    if (!Send::g_send)
        return;
    Send::g_send->destroy();
    Send::g_send.reset();
}


