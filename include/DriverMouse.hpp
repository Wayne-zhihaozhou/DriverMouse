//DriveMouse.hpp
#pragma once
#include "SendTypes.hpp"



// -------------------- ��ʼ��/���� IbSendBase.hpp --------------------

// ��ʼ������ģ��
DLLAPI Send::Error WINAPI IbSendInit(Send::SendType type, Send::InitFlags flags, void* argument);

// ���ٷ���ģ��
DLLAPI void WINAPI IbSendDestroy();

// ͬ������״̬
DLLAPI void WINAPI IbSendSyncKeyStates();

// -------------------- ������ IbSendMouse.hpp --------------------

// �ƶ����
DLLAPI bool WINAPI IbSendMouseMove(uint32_t x, uint32_t y, Send::MoveMode mode);

// �����
DLLAPI bool WINAPI IbSendMouseClick(Send::MouseButton button);

// ������
DLLAPI bool WINAPI IbSendMouseWheel(int32_t movement);

// -------------------- ���̿��� IbSendKeyboard.hpp --------------------
// ����
DLLAPI bool SendHotkey(const std::string& hotkey);







