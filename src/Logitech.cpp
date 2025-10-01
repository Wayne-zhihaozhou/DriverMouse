#include "Logitech.hpp" 
#include "KeyboardMap.hpp"
#include <string_view>

namespace Send::Type::Internal {

	// ���캯������ʼ�� VirtualKeyStates ����
	Logitech::Logitech() : VirtualKeyStates(keyboard_report.modifiers, keyboard_mutex) {}

	// ��ʼ�� Logitech ����
	Send::Error Logitech::create() {
		return driver.create();
	}

	// ���� Logitech ����
	void Logitech::destroy() {
		driver.destroy();
	}

	// ����һ����������¼�
	uint32_t Logitech::send_mouse_input(const INPUT inputs[], uint32_t n) {
		uint32_t count = 0;
		for (uint32_t i = 0; i < n; ++i) {
			if (inputs[i].type == INPUT_MOUSE) {
				if (send_mouse_input(inputs[i].mi)) {
					++count;
				}
			}
		}
		return count;
	}

	// ���͵�����������¼�
	bool Logitech::send_mouse_input(const MOUSEINPUT& mi) {
		return send_mouse_report<MouseReport>(mi);
	}

	// ���ͼ��������¼���֧�����μ�״̬���£�
	bool Logitech::send_keyboard_input(const KEYBDINPUT& ki) {
		std::lock_guard lock(keyboard_mutex);

		// �ж��ǰ��»����ͷ�
		bool keydown = !(ki.dwFlags & KEYEVENTF_KEYUP);
		if (is_modifier(ki.wVk)) {
			// ���μ�״̬����
			set_modifier_state(ki.wVk, keydown);
		}
		else {
			// ��ͨ���������������� report��̧�������
			uint8_t usage = Usb::keyboard_vk_to_usage((uint8_t)ki.wVk);
			if (keydown) {
				for (int i = 0; i < 6; i++) {
					if (keyboard_report.keys[i] == 0) {
						keyboard_report.keys[i] = usage;
						break;
					}
				}
				// #TODO: ��������
			}
			else {
				for (int i = 0; i < 6; i++) {
					if (keyboard_report.keys[i] == usage) {
						keyboard_report.keys[i] = 0;
						// #TODO: �Ƿ���Ҫ���Ƽ�λ
						break;
					}
				}
			}
		}

		// �ύ���̱���
		return driver.report_keyboard(keyboard_report);
	}

	// ������걨�棨֧���ƶ������֡��������¼���
	template <class ReportType>
	bool Logitech::send_mouse_report(const MOUSEINPUT& mi) {
		std::lock_guard lock(mouse_mutex);

		ReportType mouse_report{};

		// ��������ƶ�
		if (mi.dwFlags & MOUSEEVENTF_MOVE) {
			POINT move{ mi.dx, mi.dy };
			if (mi.dwFlags & MOUSEEVENTF_ABSOLUTE) {
				// ����ת�������� -> ��Ļ���� -> �������
				if (mi.dwFlags & MOUSEEVENTF_VIRTUALDESK)
					mouse_virtual_desk_absolute_to_screen(move);
				else
					mouse_absolute_to_screen(move);
				mouse_screen_to_relative(move);
			}

			// �ֶδ�����ƶ��������ⳬ���������ͷ�Χ
			static_assert(std::is_same_v<decltype(mouse_report.x), decltype(mouse_report.y)>);
			using CoordinatesType = decltype(mouse_report.x);
			constexpr auto maxValue = max_value<CoordinatesType>();

			while (abs(move.x) > maxValue || abs(move.y) > maxValue) {
				if (abs(move.x) > maxValue) {
					mouse_report.x = move.x > 0 ? maxValue : -maxValue;
					move.x -= mouse_report.x;
				}
				else {
					mouse_report.x = 0;
				}

				if (abs(move.y) > maxValue) {
					mouse_report.y = move.y > 0 ? maxValue : -maxValue;
					move.y -= mouse_report.y;
				}
				else {
					mouse_report.y = 0;
				}

				// �ֶη����ƶ�����
				driver.report_mouse(mouse_report, compensate_switch = -compensate_switch);
			}

			mouse_report.x = (CoordinatesType)move.x;
			mouse_report.y = (CoordinatesType)move.y;
		}
		else {
			mouse_report.x = 0;
			mouse_report.y = 0;
		}

		// ��������¼�
		if (mi.dwFlags & MOUSEEVENTF_WHEEL) {
			mouse_report.wheel = std::bit_cast<int32_t>(mi.mouseData) > 0 ? 1 : -1;
		}

		// ���������а���
#define CODE_GENERATE(down, up, member)  \
            if (mi.dwFlags & down || mi.dwFlags & up)  \
                mouse_report.button.##member = mi.dwFlags & down;

		CODE_GENERATE(MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP, LButton)
			CODE_GENERATE(MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP, RButton)
			CODE_GENERATE(MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP, MButton)
#undef CODE_GENERATE

			// ���� X ��ť
			if (mi.dwFlags & (MOUSEEVENTF_XDOWN | MOUSEEVENTF_XUP)) {
				bool down = mi.dwFlags & MOUSEEVENTF_XDOWN;
				switch (mi.mouseData) {
				case XBUTTON1: mouse_report.button.XButton1 = down; break;
				case XBUTTON2: mouse_report.button.XButton2 = down; break;
				}
			}

		// �ύ��걨��
		return driver.report_mouse(mouse_report, compensate_switch = -compensate_switch);
	}

}
