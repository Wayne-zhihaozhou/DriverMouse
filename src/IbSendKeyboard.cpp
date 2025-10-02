//ibsendkeyboard.cpp
#include"pch.h"

	// ����һ�������ļ����¼����൱��ԭ�� keybd_event��
VOID WINAPI IbSend_keybd_event(
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

bool WINAPI IbSendKeybdDownUp(uint16_t vk, Send::KeyboardModifiers modifiers) {
	// �������μ�˳��
	struct ModKey { uint16_t vk; bool active; };
	ModKey modKeys[] = {
		{ VK_LCONTROL, modifiers.LCtrl }, { VK_RCONTROL, modifiers.RCtrl },
		{ VK_LSHIFT,   modifiers.LShift }, { VK_RSHIFT,   modifiers.RShift },
		{ VK_LMENU,    modifiers.LAlt },   { VK_RMENU,    modifiers.RAlt },
		{ VK_LWIN,     modifiers.LWin },   { VK_RWIN,     modifiers.RWin }
	};

	// ��������¼��� = ���μ����� + Ŀ������� + Ŀ����ͷ� + ���μ��ͷ�
	INPUT inputs[sizeof(modKeys) / sizeof(ModKey) * 2 + 2] = {};
	uint32_t i = 0;

	// С���������¼�
	auto pressKey = [&](uint16_t key) {
		inputs[i] = {};
		inputs[i].type = INPUT_KEYBOARD;
		inputs[i].ki.wVk = key;
		i++;
		};

	// С�������ͷż�
	auto releaseKey = [&](uint16_t key) {
		inputs[i] = {};
		inputs[i].type = INPUT_KEYBOARD;
		inputs[i].ki.wVk = key;
		inputs[i].ki.dwFlags = KEYEVENTF_KEYUP;
		i++;
		};

	// �Ȱ������μ�
	for (auto& mk : modKeys)
		if (mk.active) pressKey(mk.vk);

	// ����Ŀ���
	pressKey(vk);

	// �ͷ�Ŀ���
	releaseKey(vk);

	// �����ͷ����μ�
	for (int idx = sizeof(modKeys) / sizeof(ModKey) - 1; idx >= 0; idx--)
		if (modKeys[idx].active) releaseKey(modKeys[idx].vk);

	return IbSendInput(i, inputs, sizeof(INPUT)) == i;
}

Send::CharMapping CharToVK(char ch) {
	if (ch >= 'A' && ch <= 'Z') return { static_cast<uint16_t>(ch), true }; // ��д
	if (ch >= 'a' && ch <= 'z') return { static_cast<uint16_t>(toupper(ch)), false };
	if (ch >= '0' && ch <= '9') return { static_cast<uint16_t>(ch), false };

	// ���÷���ӳ�䣨����չ��
	switch (ch) {
	case '!': return { '1', true };
	case '@': return { '2', true };
	case '#': return { '3', true };
	case '$': return { '4', true };
	case '%': return { '5', true };
	case '^': return { '6', true };
	case '&': return { '7', true };
	case '*': return { '8', true };
	case '(': return { '9', true };
	case ')': return { '0', true };
	case '-': return { VK_OEM_MINUS, false };
	case '_': return { VK_OEM_MINUS, true };
	case '=': return { VK_OEM_PLUS, false };
	case '+': return { VK_OEM_PLUS, true };
	case '[': return { VK_OEM_4, false };
	case '{': return { VK_OEM_4, true };
	case ']': return { VK_OEM_6, false };
	case '}': return { VK_OEM_6, true };
	case ';': return { VK_OEM_1, false };
	case ':': return { VK_OEM_1, true };
	case '\'': return { VK_OEM_7, false };
	case '"': return { VK_OEM_7, true };
	case ',': return { VK_OEM_COMMA, false };
	case '<': return { VK_OEM_COMMA, true };
	case '.': return { VK_OEM_PERIOD, false };
	case '>': return { VK_OEM_PERIOD, true };
	case '/': return { VK_OEM_2, false };
	case '?': return { VK_OEM_2, true };
	case '\\': return { VK_OEM_5, false };
	case '|': return { VK_OEM_5, true };
	case '`': return { VK_OEM_3, false };
	case '~': return { VK_OEM_3, true };
	case ' ': return { VK_SPACE, false };
	default: return { 0, false }; // δ֪�ַ�
	}
}

// ������ϰ����ַ��������� "Ctrl+Shift+A"
Send::KeyboardModifiers ParseModifiers(const std::vector<std::string>& parts) {
	Send::KeyboardModifiers mods;
	for (const auto& p : parts) {
		if (p == "Ctrl") { mods.LCtrl = true; }
		else if (p == "Shift") { mods.LShift = true; }
		else if (p == "Alt") { mods.LAlt = true; }
		else if (p == "Win") { mods.LWin = true; }
	}
	return mods;
}

std::vector<std::string> SplitString(const std::string& s, char delim) {
	std::vector<std::string> result;
	std::string tmp;
	for (char c : s) {
		if (c == delim) {
			if (!tmp.empty()) result.push_back(tmp);
			tmp.clear();
		}
		else tmp.push_back(c);
	}
	if (!tmp.empty()) result.push_back(tmp);
	return result;
}

// �û��ӿڣ�������ϰ����ַ���
DLLAPI bool SendHotkey(const std::string& hotkey) {
	auto parts = SplitString(hotkey, '+');
	if (parts.empty()) return false;

	char targetChar = parts.back()[0];
	parts.pop_back();  // ʣ�µĶ������μ�

	Send::KeyboardModifiers mods = ParseModifiers(parts);
	Send::CharMapping mapping = CharToVK(targetChar);

	// ����ַ���Ҫ Shift���Զ����
	if (mapping.shift) mods.LShift = true;

	return IbSendKeybdDownUp(mapping.vk, mods);
}