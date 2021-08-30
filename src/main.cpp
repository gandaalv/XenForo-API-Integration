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

	g_XenForo.initialize("https://3a7388f88a2382ef.demo-xenforo.com/226p2/index.php/api", "-PymLn2SfxFbKrdgJSIu0ur1qwwHopFE");

	g_XenForo.authenticate(szLogin, szPassword);

	std::cin.get();
}