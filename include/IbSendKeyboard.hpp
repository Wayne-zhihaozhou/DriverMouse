//IbSendKeyboard.hpp
#pragma once
#include "SendTypes.hpp"

#ifdef __cplusplus
extern "C" {
#endif

	// �ͼ������¼�
	VOID WINAPI IbSend_keybd_event(
		_In_ BYTE bVk,
		_In_ BYTE bScan,
		_In_ DWORD dwFlags,
		_In_ ULONG_PTR dwExtraInfo
	);

	// ����ָ����
	bool WINAPI IbSendKeybdDown(uint16_t vk);

	// �ͷ�ָ����
	bool WINAPI IbSendKeybdUp(uint16_t vk);

	// ���²��ͷ�ָ�������ɸ������μ�
	bool WINAPI IbSendKeybdDownUp(uint16_t vk, Send::KeyboardModifiers modifiers);


#ifdef __cplusplus
}
#endif


