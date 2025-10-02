//IbSendBase.hpp
#pragma once
#include "SendTypes.hpp"

#ifdef __cplusplus
extern "C" {
#endif

	// ��ʼ������ģ��
	Send::Error WINAPI IbSendInit(Send::SendType type, Send::InitFlags flags, void* argument);

	// ���ٷ���ģ��
	void WINAPI IbSendDestroy();

	// ͬ������״̬
	void WINAPI IbSendSyncKeyStates();

#ifdef __cplusplus
}
#endif
