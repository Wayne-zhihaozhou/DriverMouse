//IbSendMouse.hpp
#pragma once
#include "SendTypes.hpp"

#ifdef __cplusplus
extern "C" {
#endif

	// �ͼ�����¼�
	VOID WINAPI IbSend_mouse_event(
		_In_ DWORD dwFlags,
		_In_ DWORD dx,
		_In_ DWORD dy,
		_In_ DWORD dwData,
		_In_ ULONG_PTR dwExtraInfo
	);

	// �ƶ����
	bool WINAPI IbSendMouseMove(uint32_t x, uint32_t y, Send::MoveMode mode);

	// �����
	bool WINAPI IbSendMouseClick(Send::MouseButton button);

	// ������
	bool WINAPI IbSendMouseWheel(int32_t movement);

#ifdef __cplusplus
}
#endif
