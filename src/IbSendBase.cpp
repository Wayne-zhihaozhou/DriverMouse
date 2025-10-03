//ibSendBase.cpp
#include"pch.h"
#include "Logitech.hpp"
#include "SendInputHook.hpp"

// ��ʼ������ģ�飨��֧�� Logitech��������������ȫ�ַ��Ͷ���
DLLAPI bool WINAPI IbSendInit() {

    auto logitech = std::make_unique<Send::Internal::Logitech>();//���޸�,����ȫ�ֱ���
    if (!logitech->create())
        return false;

    Send::g_send = std::move(logitech); 
    return true;
}

// ���ٷ���ģ�飬�ͷ�ȫ�ַ��Ͷ���
DLLAPI void WINAPI IbSendDestroy() {

    if (!Send::g_send)
        return;
    Send::g_send->destroy();
    Send::g_send.reset();
}


