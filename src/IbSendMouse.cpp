#include <bit>
#include <cassert>
#include <IbSendInput.hpp>
#include "IbSendMouse.hpp"

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

// ģ������ƶ���֧�־��Ժ����ģʽ��
DLLAPI bool __stdcall Send::IbSendMouseMove(uint32_t x, uint32_t y, Send::MoveMode mode) {
    // ��������ƶ��¼�
    INPUT input{
        .type = INPUT_MOUSE,
        .mi {
            .dx = std::bit_cast<LONG>(x),
            .dy = std::bit_cast<LONG>(y),
            .mouseData = 0,
            .dwFlags = [mode]() -> DWORD {
                switch (mode) {
                    case MoveMode::Absolute: return MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK;
                    case MoveMode::Relative: return MOUSEEVENTF_MOVE;
                    default: assert(false);
                }
            }(),
            .time = 0,
            .dwExtraInfo = 0
        }
    };
    // �����¼�
    return IbSendInput(1, &input, sizeof(INPUT));
}

// ģ��һ������������� + ̧��
DLLAPI bool __stdcall Send::IbSendMouseClick(Send::MouseButton button) {
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
    case MouseButton::Left:
        inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        return IbSendInput(2, inputs, sizeof(INPUT)) == 2;
    case MouseButton::Right:
        inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
        inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
        return IbSendInput(2, inputs, sizeof(INPUT)) == 2;
    case MouseButton::Middle:
        inputs[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
        inputs[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
        return IbSendInput(2, inputs, sizeof(INPUT)) == 2;
    case MouseButton::XButton1:
        inputs[0].mi.dwFlags = MOUSEEVENTF_XDOWN;
        inputs[1].mi.dwFlags = MOUSEEVENTF_XUP;
        inputs[0].mi.mouseData = inputs[1].mi.mouseData = XBUTTON1;
        return IbSendInput(2, inputs, sizeof(INPUT)) == 2;
    case MouseButton::XButton2:
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
DLLAPI bool __stdcall Send::IbSendMouseWheel(int32_t movement) {
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

