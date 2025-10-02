//IbSendBase.hpp
#pragma once
#include "dll_export.hpp"
#include "SendTypes.hpp"

#ifdef __cplusplus
extern "C" {
#endif

	// ��ʼ������ģ��
	DLLAPI Send::Error WINAPI IbSendInit(Send::SendType type, Send::InitFlags flags, void* argument);

	// ���ٷ���ģ��
	DLLAPI void WINAPI IbSendDestroy();

	// ͬ������״̬
	DLLAPI void WINAPI IbSendSyncKeyStates();

#ifdef __cplusplus
}
#endif
