#include <napi.h>
#include <dwmapi.h>

#pragma comment(lib, "D:\\Windows Kits\\10\\Lib\\10.0.17763.0\\um\\x64\\dwmapi.lib")

using namespace Napi;

String Hello(const CallbackInfo& info) {
	return String::New(info.Env(), "world");
}

String CheckAeroStr(const CallbackInfo& info) {
	BOOL IsAero = FALSE;

	HRESULT res = DwmIsCompositionEnabled(&IsAero);

	if (res == S_OK && IsAero == TRUE) {
		return String::New(info.Env(), "system theme aero on.");
	}

	return String::New(info.Env(), "system theme aero off.");
}

Napi::Boolean CheckAero(const CallbackInfo& info) {
	BOOL IsAero = FALSE;

	HRESULT res = DwmIsCompositionEnabled(&IsAero);
	
	if (res == S_OK) {
		return Boolean::New(info.Env(), (bool)IsAero);
	}

	return Boolean::New(info.Env(), false);
}

Napi::Object  Init(Env env, Object exports) {
	exports.Set("hello", Function::New(env, Hello));
	exports.Set("CheckAeroString", Function::New(env, CheckAeroStr));
	exports.Set("CheckAero", Function::New(env, CheckAero));
	return exports;
}
NODE_API_MODULE(addon, Init)