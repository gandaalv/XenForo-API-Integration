/* includes */
#include "XenForo.hpp"

void CXenForo::initialize(std::string_view szApiUrl, std::string_view szApiKey)
{
	m_szApiUrl = szApiUrl;
	m_szApiKey = szApiKey;
	m_cprHeader = cpr::Header
	{
		{"Content-Type", "application/x-www-form-urlencoded"},
		{"XF-Api-Key", m_szApiKey}
	};
}

bool CXenForo::authenticate(std::string_view szLogin, std::string_view szPassword)
{
	std::string szUrl = fmt::format("{}{}", m_szApiUrl, "/auth/");
	std::string szBody = fmt::format("login={}&password={}&api_bypass_permissions=1", szLogin, szPassword);

	auto cprRequest = cpr::Post(cpr::Url{ szUrl }, cpr::Body{ szBody }, cpr::Timeout{ 5000 }, m_cprHeader);

	if (cprRequest.elapsed >= 5)
	{
		std::cout << "[cpr] Connection timeout." << std::endl;
		return false;
	}

	std::string szResponse = cprRequest.text;

	if (!nlohmann::json::accept(szResponse))
	{
		std::cout << "[json] Failed to accept response." << std::endl;
		return false;
	}

	auto parsedResponse = nlohmann::json::parse(szResponse);

	if (parsedResponse.contains("errors")) /* checking if a error occured */
	{
		for (auto& errors : parsedResponse["errors"])
		{
			std::cout << errors["message"] << std::endl; /* display the error message */
		}
		
		return false;
	}

	std::cout << cprRequest.text << std::endl;

	return true;
}

CXenForo g_XenForo;