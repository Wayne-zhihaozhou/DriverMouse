//#pragma once
//#include "detours.h"
//#include <Windows.h>

//#include "InputSimulator.hpp"
//#include <IbWinCpp/WinCpp.hpp>


//using ib::Byte;
//
//constexpr int debug = ib::debug_runtime;
//
//// Debug �����������ʵ�ַŵ� common.cpp��
//ib::DebugOStream<> DebugOStream();


//ģ��

//template<typename T>
//LONG IbDetourAttach(_Inout_ T* ppPointer, _In_ T pDetour) {
//    DetourTransactionBegin();
//    DetourUpdateThread(GetCurrentThread());
//    DetourAttach((void**)ppPointer, pDetour);
//    return DetourTransactionCommit();
//}
//
//template<typename T>
//LONG IbDetourDetach(_Inout_ T* ppPointer, _In_ T pDetour) {
//    DetourTransactionBegin();
//    DetourUpdateThread(GetCurrentThread());
//    DetourDetach((void**)ppPointer, pDetour);
//    return DetourTransactionCommit();
//}
