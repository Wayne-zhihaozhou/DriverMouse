//IbSendMouse.cpp
#include"pch.h"
#include <Logitech.hpp>
#include <SendInputHook.hpp>


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


bool send_mouse_input_bulk(const MOUSEINPUT* inputs, uint32_t count) {
	auto logitech = std::make_unique<Send::Internal::Logitech>();
	//logitech->create_base(&SendInputHook::GetAsyncKeyState_real);
	logitech->create();
	for (uint32_t i = 0; i < count; ++i) {
		if (!logitech->send_mouse_report(inputs[i])) return false;
	}
	return true;
}

DLLAPI bool WINAPI MouseMoveRelative(int32_t dx, int32_t dy) {
	const int32_t MAX_DELTA = 128;

	int32_t steps = max(
		(std::abs(dx) + MAX_DELTA - 1) / MAX_DELTA,
		(std::abs(dy) + MAX_DELTA - 1) / MAX_DELTA
	);
	if (steps == 0) steps = 1;

	std::vector<MOUSEINPUT> moves;
	moves.reserve(steps);

	float step_x = static_cast<float>(dx) / steps;
	float step_y = static_cast<float>(dy) / steps;
	float prev_x = 0, prev_y = 0;

	for (int32_t i = 1; i <= steps; ++i) {
		float curr_x = step_x * i;
		float curr_y = step_y * i;

		MOUSEINPUT mi{};
		mi.dx = static_cast<int32_t>(curr_x - prev_x + 0.5f);
		mi.dy = static_cast<int32_t>(curr_y - prev_y + 0.5f);
		mi.dwFlags = MOUSEEVENTF_MOVE;

		moves.push_back(mi);
		prev_x = curr_x;
		prev_y = curr_y;
	}

	return send_mouse_input_bulk(moves.data(), static_cast<uint32_t>(moves.size()));
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
//DLLAPI bool WINAPI MouseMoveRelative(int32_t dx, int32_t dy) {
//	const int32_t MAX_DELTA = 128;  // HID ���浥�������������
//
//	// ʹ����������ȡ�������⸡�� ceil
//	int32_t steps = max(
//		(std::abs(dx) + MAX_DELTA - 1) / MAX_DELTA,
//		(std::abs(dy) + MAX_DELTA - 1) / MAX_DELTA
//	);
//	if (steps == 0) steps = 1;
//
//	// Ԥ�����ڴ棬�����ζ�̬����
//	std::vector<INPUT> inputs;
//	inputs.reserve(steps);
//
//	// Ԥ����ÿһ����������������㣩��ѭ���н��ӷ�
//	float step_x = static_cast<float>(dx) / steps;
//	float step_y = static_cast<float>(dy) / steps;
//
//	float prev_x = 0.0f;
//	float prev_y = 0.0f;
//
//	for (int32_t i = 1; i <= steps; ++i) {
//		float curr_x = step_x * i;
//		float curr_y = step_y * i;
//
//		int32_t move_x = static_cast<int32_t>(std::round(curr_x - prev_x));
//		int32_t move_y = static_cast<int32_t>(std::round(curr_y - prev_y));
//
//		prev_x = curr_x;
//		prev_y = curr_y;
//
//		INPUT input{};
//		input.type = INPUT_MOUSE;
//		input.mi.dx = move_x;
//		input.mi.dy = move_y;
//		input.mi.mouseData = 0;
//		input.mi.dwFlags = MOUSEEVENTF_MOVE;  // ����ƶ�
//		input.mi.time = 0;
//		input.mi.dwExtraInfo = 0;
//
//		inputs.push_back(input);
//	}
//
//	// һ���Է������зֶ��¼�
//	return IbSendInput(static_cast<UINT>(inputs.size()), inputs.data(), sizeof(INPUT)) != 0;
//}



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

