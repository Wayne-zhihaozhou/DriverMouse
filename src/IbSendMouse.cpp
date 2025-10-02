//IbSendMouse.cpp
#include"pch.h"


	// ����һ������������¼����൱��ԭ�� mouse_event��
DLLAPI VOID WINAPI IbSend_mouse_event(
	_In_ DWORD dwFlags,
	_In_ DWORD dx,
	_In_ DWORD dy,
	_In_ DWORD dwData,
	_In_ ULONG_PTR dwExtraInfo
) {
	// �����������ṹ
	INPUT input{
		.type = INPUT_MOUSE,
		.mi {
			.dx = std::bit_cast<LONG>(dx),
			.dy = std::bit_cast<LONG>(dy),
			.mouseData = dwData,
			.dwFlags = dwFlags,
			.time = 0,
			.dwExtraInfo = dwExtraInfo
		}
	};
	// ���÷��ͺ���
	IbSendInput(1, &input, sizeof(INPUT));
}

// ģ���������ƶ�
DLLAPI bool WINAPI MouseMoveAbsolute(uint32_t x, uint32_t y) {
	INPUT input{
		.type = INPUT_MOUSE,
		.mi = {
			.dx = std::bit_cast<LONG>(x),
			.dy = std::bit_cast<LONG>(y),
			.mouseData = 0,
			.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK,
			.time = 0,
			.dwExtraInfo = 0
		}
	};
	return IbSendInput(1, &input, sizeof(INPUT));
}

// ģ���������ƶ�
DLLAPI bool WINAPI MouseMoveRelative(int32_t dx, int32_t dy) {
	INPUT input{
		.type = INPUT_MOUSE,
		.mi = {
			.dx = std::bit_cast<LONG>(dx),
			.dy = std::bit_cast<LONG>(dy),
			.mouseData = 0,
			.dwFlags = MOUSEEVENTF_MOVE,
			.time = 0,
			.dwExtraInfo = 0
		}
	};
	return IbSendInput(1, &input, sizeof(INPUT));
}

DLLAPI bool WINAPI MouseMoveRelativeBatch(int32_t dx, int32_t dy) {
	const int32_t MAX_DELTA = 128;  // ÿ���¼�����ƶ�����
	std::vector<INPUT> inputs;

	int32_t steps = max(std::ceil(std::abs(dx) / (float)MAX_DELTA),
		std::ceil(std::abs(dy) / (float)MAX_DELTA));

	if (steps == 0) steps = 1;

	for (int32_t i = 1; i <= steps; ++i) {
		// �ֶ�����ƶ���
		int32_t move_x = dx * i / steps - dx * (i - 1) / steps;
		int32_t move_y = dy * i / steps - dy * (i - 1) / steps;

		INPUT input{};
		input.type = INPUT_MOUSE;
		input.mi.dx = std::bit_cast<LONG>(move_x);
		input.mi.dy = std::bit_cast<LONG>(move_y);
		input.mi.mouseData = 0;
		input.mi.dwFlags = MOUSEEVENTF_MOVE;  // ����ƶ�
		input.mi.time = 0;
		input.mi.dwExtraInfo = 0;

		inputs.push_back(input);
	}

	// һ���������������зֶ��¼�
	return IbSendInput(static_cast<UINT>(inputs.size()), inputs.data(), sizeof(INPUT)) != 0;
}

// ģ��һ������������� + ̧��
DLLAPI bool WINAPI MouseClick(Send::MouseButton button) {
	// ��ʼ�����º�̧���¼�
	INPUT inputs[2];
	inputs[0] = inputs[1] = {
		.type = INPUT_MOUSE,
		.mi {
			.dx = 0,
			.dy = 0,
			.mouseData = 0,
			.time = 0,
			.dwExtraInfo = 0
		}
	};

	// ���ݰ������������¼���־
	switch (button) {
	case Send::MouseButton::Left:
		inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
		return IbSendInput(2, inputs, sizeof(INPUT)) == 2;
	case Send::MouseButton::Right:
		inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		return IbSendInput(2, inputs, sizeof(INPUT)) == 2;
	case Send::MouseButton::Middle:
		inputs[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
		inputs[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
		return IbSendInput(2, inputs, sizeof(INPUT)) == 2;
	case Send::MouseButton::XButton1:
		inputs[0].mi.dwFlags = MOUSEEVENTF_XDOWN;
		inputs[1].mi.dwFlags = MOUSEEVENTF_XUP;
		inputs[0].mi.mouseData = inputs[1].mi.mouseData = XBUTTON1;
		return IbSendInput(2, inputs, sizeof(INPUT)) == 2;
	case Send::MouseButton::XButton2:
		inputs[0].mi.dwFlags = MOUSEEVENTF_XDOWN;
		inputs[1].mi.dwFlags = MOUSEEVENTF_XUP;
		inputs[0].mi.mouseData = inputs[1].mi.mouseData = XBUTTON2;
		return IbSendInput(2, inputs, sizeof(INPUT)) == 2;
	default:
		// Ĭ�ϴ����Զ����־
		inputs[0].mi.dwFlags = static_cast<DWORD>(button);
		return IbSendInput(1, inputs, sizeof(INPUT));
	}
}

// ģ�������ֹ���
DLLAPI bool WINAPI MouseWheel(int32_t movement) {
	// ��������¼�
	INPUT input{
		.type = INPUT_MOUSE,
		.mi {
			.dx = 0,
			.dy = 0,
			.mouseData = std::bit_cast<DWORD>(movement),
			.dwFlags = MOUSEEVENTF_WHEEL,
			.time = 0,
			.dwExtraInfo = 0
		}
	};
	// �����¼�
	return IbSendInput(1, &input, sizeof(INPUT));
}

