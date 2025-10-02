//ibsendkeyboard.cpp
#include"pch.h"

	// ����һ�������ļ����¼����൱��ԭ�� keybd_event��
DLLAPI VOID WINAPI IbSend_keybd_event(
	_In_ BYTE bVk,
	_In_ BYTE bScan,
	_In_ DWORD dwFlags,
	_In_ ULONG_PTR dwExtraInfo
) {
	// ����һ����������ṹ
	INPUT input{
		.type = INPUT_KEYBOARD,
		.ki {
			.wVk = bVk,
			.wScan = bScan,
			.dwFlags = dwFlags,
			.time = 0,
			.dwExtraInfo = dwExtraInfo
		}
	};
	// ���÷��ͺ���
	IbSendInput(1, &input, sizeof(INPUT));
}

// ģ�ⰴ��һ����
DLLAPI bool WINAPI KeyDown(uint16_t vk) {
	// ���조���¡��¼�
	INPUT input{
		.type = INPUT_KEYBOARD,
		.ki {
			.wVk = vk,
			.wScan = 0,
			.dwFlags = 0,
			.time = 0,
			.dwExtraInfo = 0
		}
	};
	// �����¼�
	return IbSendInput(1, &input, sizeof(INPUT));
}

// ģ���ͷ�һ����
DLLAPI bool WINAPI KeyUp(uint16_t vk) {
	// ���조�ͷš��¼�
	INPUT input{
		.type = INPUT_KEYBOARD,
		.ki {
			.wVk = vk,
			.wScan = 0,
			.dwFlags = KEYEVENTF_KEYUP,
			.time = 0,
			.dwExtraInfo = 0
		}
	};
	// �����¼�
	return IbSendInput(1, &input, sizeof(INPUT));
}

// ģ�ⰴ��һ���������ͷ���
DLLAPI bool WINAPI KeyPress(uint16_t vk) {
	// �������� INPUT �¼������º��ɿ�
	INPUT inputs[2]{};

	// ���¼�
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = vk;
	// dwFlags Ĭ��Ϊ 0����ʾ����

	// �ɿ���
	inputs[1] = inputs[0];
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	// һ�η��������¼�
	return IbSendInput(2, inputs, sizeof(INPUT)) == 2;
}

// ģ�ⰴ�²��ͷ�һ��������ѡ�����μ���Ctrl/Shift/Alt/Win��
DLLAPI bool WINAPI KeyCombo(uint16_t vk, Send::KeyboardModifiers modifiers) {
	struct Modifier { uint16_t vk; bool active; };
	Modifier mods[] = {
		{ VK_LCONTROL, modifiers.LCtrl },
		{ VK_RCONTROL, modifiers.RCtrl },
		{ VK_LSHIFT, modifiers.LShift },
		{ VK_RSHIFT, modifiers.RShift },
		{ VK_LMENU, modifiers.LAlt },
		{ VK_RMENU, modifiers.RAlt },
		{ VK_LWIN, modifiers.LWin },
		{ VK_RWIN, modifiers.RWin },
	};

	INPUT inputs[18]{};
	int idx = 0;

	// �������μ�
	for (auto& m : mods) {
		if (m.active) {
			inputs[idx].type = INPUT_KEYBOARD;
			inputs[idx].ki.wVk = m.vk;
			idx++;
		}
	}

	// ����Ŀ���
	inputs[idx].type = INPUT_KEYBOARD;
	inputs[idx].ki.wVk = vk;
	idx++;

	// �ɿ�Ŀ���
	inputs[idx] = inputs[idx - 1];
	inputs[idx].ki.dwFlags = KEYEVENTF_KEYUP;
	idx++;

	// �ɿ����μ�������
	for (int i = 7; i >= 0; i--) {
		if (mods[i].active) {
			inputs[idx].type = INPUT_KEYBOARD;
			inputs[idx].ki.wVk = mods[i].vk;
			inputs[idx].ki.dwFlags = KEYEVENTF_KEYUP;
			idx++;
		}
	}

	return IbSendInput(idx, inputs, sizeof(INPUT)) == idx;
}
