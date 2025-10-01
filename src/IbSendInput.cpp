#include "dll_export.hpp"
#include "base.hpp"
#include <SendTypes.hpp>
#include <SendInputHook.hpp>


// ����һ��ģ�������¼�������/��꣩
DLLAPI UINT WINAPI IbSendInput(
	_In_ UINT cInputs,
	_In_reads_(cInputs) LPINPUT pInputs,
	_In_ int cbSize
) {
	// ���õײ㷢�Ͷ�������뺯��
	return Send::g_send->send_input(pInputs, cInputs);
}


// �������빳�ӵ��������ں�����״̬
DLLAPI void __stdcall IbSendInputHook(Send::HookCode code) {
	switch (code) {
	case Send::HookCode::InitOnly:
		// �������δ�������ʼ��
		if (!g_sendInputHook)
			g_sendInputHook = std::make_unique<SendInputHook>();
		break;

	case Send::HookCode::Destroy:
		// ���ٹ��Ӷ���
		g_sendInputHook.reset();
		break;

	case Send::HookCode::On:
		// ��ʼ������δ�����������ù���
		if (!g_sendInputHook)
			g_sendInputHook = std::make_unique<SendInputHook>();
		SendInputHook::hook = true;
		break;

	case Send::HookCode::Off:
		// ���ù���
		SendInputHook::hook = false;
		break;
	}
}
