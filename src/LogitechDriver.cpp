// LogitechDriver.cpp
#include"pch.h"
#include"LogitechDriver.hpp"
#include "Logitech.hpp"



namespace Send::Internal {

	// ����ƥ��� Logitech �豸·��
	std::wstring LogitechDriver::find_device() {
		// �����豸����������豸����
		return Internal::find_device([](std::wstring_view sv) {
			using namespace std::literals;
			return (sv.starts_with(L"ROOT#SYSTEM#"sv) || sv.starts_with(L"Root#SYSTEM#"sv)) &&
				(sv.ends_with(L"#{1abc05c0-c378-41b9-9cef-df1aba82b015}"sv) ||
					sv.ends_with(L"#{df31f106-d870-453d-8fa1-ec8ab43fa1d2}"sv) ||
					sv.ends_with(L"#{dfbedcdb-2148-416d-9e4d-cecc2424128c}"sv) ||
					sv.ends_with(L"#{5bada891-842b-4296-a496-68ae931aa16c}"sv));
		});
	}

	// ���� Logitech �����豸����
	Send::Error LogitechDriver::create() {
		// ����ƥ����豸·��
		std::wstring device_name = find_device();
		if (device_name.empty()) return Error::DeviceNotFound;

		// ���豸���
		device = CreateFileW(
			device_name.c_str(),
			GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, 0, NULL
		);

		// ���ش򿪽��
		return (device == INVALID_HANDLE_VALUE) ? Error::DeviceOpenFailed : Error::Success;
	}

	// ���� Logitech �����豸����
	void LogitechDriver::destroy() {
		// �ر��豸���
		if (device != INVALID_HANDLE_VALUE) {
			CloseHandle(device);
			device = INVALID_HANDLE_VALUE;
		}
	}

	// ���豸������걨������
	bool LogitechDriver::report_mouse(const MouseReport& report) const {
		constexpr DWORD IOCTL_BUSENUM_PLAY_MOUSEMOVE = 0x2A2010;
		DWORD bytes_returned;

		return DeviceIoControl(
			device,
			IOCTL_BUSENUM_PLAY_MOUSEMOVE,
			const_cast<MouseReport*>(&report), 
			sizeof(MouseReport),
			nullptr,
			0,
			&bytes_returned,
			nullptr
		);
	}


	// ���豸���ͼ��̱�������
	bool LogitechDriver::report_keyboard(const KeyboardReport& report) const {
		DWORD bytes_returned;
		// ͨ�� IOCTL ���������ͼ�������
		return DeviceIoControl(
			device,
			0x2A200C,
			const_cast<KeyboardReport*>(&report), 
			sizeof(KeyboardReport),
			nullptr,
			0,
			&bytes_returned,
			nullptr
		);
	}

}
