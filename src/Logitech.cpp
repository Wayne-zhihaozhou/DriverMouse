//Logitech.cpp
#include"pch.h"
#include "Logitech.hpp"
#include "base.hpp"
#include "SendTypes.hpp"
#include "KeyboardMap.hpp"

#include <algorithm>


namespace Send::Internal {

	// ���캯��
	Logitech::Logitech() = default;

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
		return send_mouse_report(mi);
	}

	// ���ͼ��������¼���֧�����μ�״̬���£�
	bool Logitech::send_keyboard_input(const KEYBDINPUT& ki) {
		std::lock_guard lock(keyboard_mutex);

		bool keydown = !(ki.dwFlags & KEYEVENTF_KEYUP);

		// �������μ�
		switch (ki.wVk) {
		case VK_LCONTROL: keyboard_report.modifiers.LCtrl = keydown; break;
		case VK_RCONTROL: keyboard_report.modifiers.RCtrl = keydown; break;
		case VK_LSHIFT:   keyboard_report.modifiers.LShift = keydown; break;
		case VK_RSHIFT:   keyboard_report.modifiers.RShift = keydown; break;
		case VK_LMENU:    keyboard_report.modifiers.LAlt = keydown; break;
		case VK_RMENU:    keyboard_report.modifiers.RAlt = keydown; break;
		case VK_LWIN:     keyboard_report.modifiers.LGui = keydown; break;
		case VK_RWIN:     keyboard_report.modifiers.RGui = keydown; break;

		default:
			// ��ͨ��������
			uint8_t usage = Usb::keyboard_vk_to_usage((uint8_t)ki.wVk);
			if (keydown) {
				// ���£������λ
				for (int i = 0; i < 6; i++) {
					if (keyboard_report.keys[i] == 0) {
						keyboard_report.keys[i] = usage;
						break;
					}
				}
			}
			else {
				// ̧�������Ӧ����
				for (int i = 0; i < 6; i++) {
					if (keyboard_report.keys[i] == usage) {
						keyboard_report.keys[i] = 0;
						break;
					}
				}
			}
			break;
		}

		// �ύ���̱���
		return driver.report_keyboard(keyboard_report);
	}

	// ������걨�棨֧���ƶ������֡��������¼���//////////////////////////////
	void set_button(LogitechDriver::MouseButton& btn, uint32_t dwFlags, uint32_t downFlag, uint32_t upFlag) {
		if (dwFlags & (downFlag | upFlag))
			btn = static_cast<LogitechDriver::MouseButton>((dwFlags & downFlag) != 0);
	}

	bool Logitech::send_mouse_report(const MOUSEINPUT& mi) {
		std::lock_guard lock(mouse_mutex);

		MouseReport mouse_report{};
		mouse_report.x = 0;
		mouse_report.y = 0;
		mouse_report.wheel = 0;
		mouse_report.button_byte = 0;

		// ��������ƶ�
		if (mi.dwFlags & MOUSEEVENTF_MOVE) {
			POINT move{ mi.dx, mi.dy };

			if (mi.dwFlags & MOUSEEVENTF_ABSOLUTE) {
				if (mi.dwFlags & MOUSEEVENTF_VIRTUALDESK)
					mouse_virtual_desk_absolute_to_screen(move);
				else
					mouse_absolute_to_screen(move);
				mouse_screen_to_relative(move);
			}

			mouse_report.x = move.x;
			mouse_report.y = move.y;
		}

		// �������
		if (mi.dwFlags & MOUSEEVENTF_WHEEL) {
			mouse_report.wheel = (static_cast<int32_t>(mi.mouseData) > 0) ? 1 : -1;
		}

		// ������갴��
		auto set_button = [](LogitechDriver::MouseButton& btn, uint32_t dwFlags, uint32_t downFlag, uint32_t upFlag) {
			if (dwFlags & (downFlag | upFlag))
				btn = static_cast<LogitechDriver::MouseButton>((dwFlags & downFlag) != 0);
			};

		set_button(mouse_report.button, mi.dwFlags, MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP);
		set_button(mouse_report.button, mi.dwFlags, MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP);
		set_button(mouse_report.button, mi.dwFlags, MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP);

		 //X ��ť
		if (mi.dwFlags & (MOUSEEVENTF_XDOWN | MOUSEEVENTF_XUP)) {
			bool down = mi.dwFlags & MOUSEEVENTF_XDOWN;
			if (mi.mouseData == XBUTTON1) mouse_report.button.XButton1 = down;
			if (mi.mouseData == XBUTTON2) mouse_report.button.XButton2 = down;
		}

		return driver.report_mouse(mouse_report);
	}


}
