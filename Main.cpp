#include <Windows.h>
#include <stdio.h>
extern int Main();

//tls callback is called each time a new thread is created
void NTAPI tls_callback(PVOID DllHandle, DWORD dwReason, PVOID)
{
	if (dwReason == DLL_THREAD_ATTACH)
	{
		printf("DLL Thread attached!\n");
	}
	else if (dwReason == DLL_PROCESS_ATTACH)
	{
		printf("Process attached!\n");
	}
}

#pragma comment (linker, "/INCLUDE:_tls_used") 
#pragma comment (linker, "/INCLUDE:tls_callback_func")
#pragma const_seg(".CRT$XLF")
EXTERN_C const PIMAGE_TLS_CALLBACK tls_callback_func = tls_callback;
#pragma const_seg()

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	AllocConsole(); //for printf help messages during development. 
	freopen("CON", "w", stdout);
	freopen("CON", "r", stdin);


	Main();
	return 0;
}