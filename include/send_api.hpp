DLLAPI void __stdcall IbSendSyncKeyStates() {
    main::send->sync_key_states(); // ͬ������״̬
}

DLLAPI UINT WINAPI IbSendInput(
    _In_ UINT cInputs,
    _In_reads_(cInputs) LPINPUT pInputs,
    _In_ int cbSize
) {
    return main::send->send_input(pInputs, cInputs); // ���÷��ͺ���
}
