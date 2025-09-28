#pragma once
#include <string>
#include <Windows.h>

namespace Send::Type::Internal {

    /**
     * @brief Logitech �豸�ײ�����
     *
     * �ṩ���������ٺͼ��̱��淢�ͽӿڡ�
     */
    class LogitechDriver {
    public:
        /**
         * @brief ���� Logitech �豸
         * @return Error �ɹ����� Error::Success���Ҳ����豸���� Error::DeviceNotFound����ʧ�ܷ��� Error::DeviceOpenFailed
         */
        Error create();

        /**
         * @brief ���� Logitech �豸
         */
        void destroy();

        /**
         * @brief ���ͼ��̱���
         * @param report KeyboardReport ���̱���
         * @return bool ���ͳɹ����� true
         */
        bool report_keyboard(KeyboardReport report) const;

    private:
        HANDLE device{ INVALID_HANDLE_VALUE };

        /**
         * @brief ���� Logitech �豸
         * @return std::wstring �豸·����δ�ҵ����ؿ��ַ���
         */
        std::wstring find_device();
    };

}  // namespace Send::Type::Internal
