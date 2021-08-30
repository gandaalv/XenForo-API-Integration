#include "Auth.hpp"

bool CAuth::setup(std::string_view szEndpointUrl, std::string_view szApiKey)
{
	if (szEndpointUrl.length() <= 1 || szApiKey.length() <= 1) /* checking input */
	{
		std::cout << "[CAuth::setup] Empty input." << std::endl;
		return false;
	}

	m_szEndpointUrl = szEndpointUrl;
	m_szApiKey = szApiKey;
	m_cprHeader = cpr::Header
	{
		{"Content-Type", "application/x-www-form-urlencoded"},
		{"XF-Api-Key", m_szApiKey},
		{"api_bypass_permissions", "1"}
	};

	return true;
}

bool CAuth::request(std::string_view szLogin, std::string_view szPassword)
{
	auto cprRequest = cpr::Post(cpr::Url{ m_szEndpointUrl }, cpr::Body{ fmt::format("login={}&password={}", szLogin, szPassword) }, m_cprHeader);

	/* checking if the request takes five or more seconds */
	if (cprRequest.elapsed >= 5)
	{
		std::cout << "[cpr] Connection timeout." << std::endl;
		return false;
	}

	std::string szResponse = cprRequest.text;

	/* checking if we got a full json formatted reponse before parsing it */
	if (!nlohmann::json::accept(szResponse))
	{
		std::cout << "[json] Failed to accept response." << std::endl;
		return false;
	}

	auto parsedResponse = nlohmann::json::parse(szResponse);

	/* checking if a error occured */
	if (parsedResponse.contains("errors"))
	{
		for (auto& errors : parsedResponse["errors"])
		{
			std::cout << "[forum] Error message: " << errors["message"] << std::endl; /* display the error message */
		}

		return false;
	}

	if (parsedResponse.contains("success"))
	{
		Vars.success = parsedResponse["success"];
	}
	
	if (!Vars.success)
	{
		std::cout << "[CAuth::request] Vars.success returned false." << std::endl;
		return false;
	}

	/* user field is missing, should not be triggered since we search for the error message first */
	if (!parsedResponse.contains("user"))
	{
		std::cout << "[CAuth::request] User field is missing." << std::endl;
		return false;
	}

	auto parsedUser = parsedResponse["user"];

	/* todo: parse every Auth_t variable. */

	return true;
}