//IbSendInput.hpp
#pragma once
#include "SendTypes.hpp"

#ifdef __cplusplus
extern "C" {
#endif

	// ���������¼�
	UINT WINAPI IbSendInput(
		_In_ UINT cInputs,
		_In_reads_(cInputs) LPINPUT pInputs,
		_In_ int cbSize
	);

	// ��װ�򴥷����빳��
	void WINAPI IbSendInputHook(Send::HookCode code);

#ifdef __cplusplus
}
#endif




