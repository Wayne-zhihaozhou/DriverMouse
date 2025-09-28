#pragma once
#include <cstdint>

namespace Send::Type::Internal::Usb {

	/**
	 * @brief ���������ӳ��Ϊ USB Usage
	 * @param vk �������
	 * @return uint8_t USB usage
	 */
	uint8_t keyboard_vk_to_usage(uint8_t vk);

	/**
	 * @brief �ж��Ƿ��� modifier ����Ctrl/Shift/Alt/Win��
	 * @param vk �������
	 * @return true �� modifier
	 */
	bool is_modifier(uint8_t vk);

}  // namespace Send::Type::Internal::Usb
