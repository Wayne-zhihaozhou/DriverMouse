//DriveMouse.hpp
#pragma once
#include <SendTypes.hpp>


//-------------------- ����DLL������ ----------
#ifdef DLL1_EXPORTS
#define DLLAPI extern "C" __declspec(dllexport)//C�������ӷ�ʽ;����������DLL��
#else
#define DLLAPI extern "C" __declspec(dllimport)//C�������ӷ�ʽ;�������뵽DLL��
#endif


//ʹ��C���
#ifdef __cplusplus
extern "C" {
#endif

	// -------------------- ��ʼ��/���� --------------------
	
	// ��ʼ������ģ��
	DLLAPI Send::Error WINAPI IbSendInit(Send::SendType type, Send::InitFlags flags, void* argument);

	// ���ٷ���ģ��
	DLLAPI void WINAPI IbSendDestroy();

	// ͬ������״̬
	DLLAPI void WINAPI IbSendSyncKeyStates();

	// -------------------- ������ --------------------

	// �ƶ����
	DLLAPI bool WINAPI IbSendMouseMove(uint32_t x, uint32_t y, Send::MoveMode mode);

	// �����
	DLLAPI bool WINAPI IbSendMouseClick(Send::MouseButton button);

	// ������
	DLLAPI bool WINAPI IbSendMouseWheel(int32_t movement);

	// -------------------- ���̿��� --------------------
	struct KeyboardModifiers;

	// ����ָ����
	DLLAPI bool WINAPI IbSendKeybdDown(uint16_t vk);

	// �ͷ�ָ����
	DLLAPI bool WINAPI IbSendKeybdUp(uint16_t vk);

	// ���²��ͷ�ָ�������ɸ������μ�
	DLLAPI bool WINAPI IbSendKeybdDownUp(uint16_t vk, KeyboardModifiers modifiers);




#ifdef __cplusplus
}
#endif





