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
DLLAPI bool WINAPI MouseMoveRelative(int32_t dx, int32_t dy);
DLLAPI bool WINAPI MouseMoveAbsolute(uint32_t x, uint32_t y);
DLLAPI bool WINAPI MouseClick(Send::MouseButton button);
DLLAPI bool WINAPI MouseWheel(int32_t movement);

// -------------------- ���̿��� IbSendKeyboard.hpp --------------------
DLLAPI bool WINAPI KeyDown(uint16_t vk);
DLLAPI bool WINAPI KeyUp(uint16_t vk);
DLLAPI bool WINAPI KeyPress(uint16_t vk);
DLLAPI bool WINAPI KeyCombo(uint16_t vk, Send::KeyboardModifiers modifiers);







