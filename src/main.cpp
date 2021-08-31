/* windows includes */
#include <Windows.h>
#include <iostream>

/* windows libraries */
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")

/* dependency libraries */
#ifdef _DEBUG
	#pragma comment(lib, "cpr.lib")
	#pragma comment(lib, "zlibd.lib")
	#pragma comment(lib, "libcurl-d.lib")
#else
	#pragma comment(lib, "cpr.lib")
	#pragma comment(lib, "zlib.lib")
	#pragma comment(lib, "libcurl.lib")
#endif

/* includes */
#include "XenForo/XenForo.hpp"

/* user input */
std::string szLogin;
std::string szPassword;

int main(void)
{
	std::cout << "Enter your forum username or e-mail:";
	std::cin >> szLogin;
	std::cout << "Enter your forum password:";
	std::cin >> szPassword;

	if (!g_XenForo.Endpoint.Auth.setup("https://3a7388f88a2382ef.demo-xenforo.com/226p2/index.php/api/auth", "-PymLn2SfxFbKrdgJSIu0ur1qwwHopFE"))
	{
		std::cout << "[CAuth] Failed to setup." << std::endl;
	}

	if (!g_XenForo.Endpoint.Auth.request(szLogin, szPassword))
	{
		std::cout << "[CAuth] Failed to send request." << std::endl;
	}
	

	system("pause");
}