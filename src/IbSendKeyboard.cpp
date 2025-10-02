//ibsendkeyboard.cpp
#include"pch.h"
#include <bit>
#include <cassert>
#include <IbSendInput.hpp>
#include "IbSendKeyboard.hpp"

namespace Send {

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
	DLLAPI bool WINAPI IbSendKeybdDown(uint16_t vk) {
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
	DLLAPI bool WINAPI IbSendKeybdUp(uint16_t vk) {
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

	// ģ�ⰴ�²��ͷ�һ��������ѡ�����μ���Ctrl/Shift/Alt/Win��
	DLLAPI bool WINAPI IbSendKeybdDownUp(uint16_t vk, Send::KeyboardModifiers modifiers) {
		// ��ʼ���յ�����ṹ
		constexpr INPUT blank_input = INPUT{ .type = INPUT_KEYBOARD, .ki { 0, 0, 0, 0, 0 } };

		// Ԥ����������
		INPUT inputs[18];  // ���֧��8�����μ� + ���� + ̧��
		uint32_t i = 0;

		// �Ȱ����������õ����μ�
#define CODE_GENERATE(vk, member)  \
    if (modifiers.member) {  \
        inputs[i] = blank_input;  \
        inputs[i].ki.wVk = vk;  \
        i++;  \
    }

		CODE_GENERATE(VK_LCONTROL, LCtrl)
			CODE_GENERATE(VK_RCONTROL, RCtrl)
			CODE_GENERATE(VK_LSHIFT, LShift)
			CODE_GENERATE(VK_RSHIFT, RShift)
			CODE_GENERATE(VK_LMENU, LAlt)
			CODE_GENERATE(VK_RMENU, RAlt)
			CODE_GENERATE(VK_LWIN, LWin)
			CODE_GENERATE(VK_RWIN, RWin)
#undef CODE_GENERATE

			// ����Ŀ���
			inputs[i] = blank_input;
		inputs[i].ki.wVk = vk;
		i++;

		// �ͷ�Ŀ���
		inputs[i] = inputs[i - 1];
		inputs[i].ki.dwFlags = KEYEVENTF_KEYUP;
		i++;

		// �ͷ��������μ��������ͷţ�
#define CODE_GENERATE(vk, member)  \
    if (modifiers.member) {  \
        inputs[i] = blank_input;  \
        inputs[i].ki.wVk = vk;  \
        inputs[i].ki.dwFlags = KEYEVENTF_KEYUP;  \
        i++;  \
    }

		CODE_GENERATE(VK_RWIN, RWin)
			CODE_GENERATE(VK_LWIN, LWin)
			CODE_GENERATE(VK_RMENU, RAlt)
			CODE_GENERATE(VK_LMENU, LAlt)
			CODE_GENERATE(VK_RSHIFT, RShift)
			CODE_GENERATE(VK_LSHIFT, LShift)
			CODE_GENERATE(VK_RCONTROL, RCtrl)
			CODE_GENERATE(VK_LCONTROL, LCtrl)
#undef CODE_GENERATE

			// һ���Է��������¼�
			return IbSendInput(i, inputs, sizeof(INPUT)) == i;
	}

}
