/* windows includes */
#include <Windows.h>
#include <iostream>

/* dependency includes */
#include <cpr/cpr.h>

/* windows libraries */
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")

/* dependency libraries */
#ifdef _DEBUG
#pragma comment(lib, "cpr-d.lib")
#pragma comment(lib, "libcurl-d.lib")
#pragma comment(lib, "zlib-d.lib")
#else
#pragma comment(lib, "cpr.lib")
#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "zlib.lib")
#endif

int main(void)
{
    cpr::Response r = cpr::Get(cpr::Url{ "https://gandaalv.codes/" });

	std::cout << r.text << std::endl;
	std::cin.get();
}