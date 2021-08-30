/* includes */
#include "XenForo.hpp"

#define PRINT(Name, Var) std::cout << Name << ":" << Var << std::endl;

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

/* just for debugging porpuses */
void CXenForo::printUserData()
{
	PRINT("szUsername", UserData.szUsername);
	PRINT("szEmail", UserData.szEmail);
	PRINT("szAvatarUrl", UserData.szAvatarUrl);
	PRINT("szProfileUrl", UserData.szProfileUrl);
	PRINT("iUserId", UserData.iUserId);
	PRINT("iPrimaryUserGroup", UserData.iPrimaryUserGroup);
	PRINT("iWarningPoints", UserData.iWarningPoints);
	for (auto& secGroup : UserData.vecSecondaryUserGroups)
	{
		PRINT("vecSecondaryUserGroups", secGroup);
	}
	PRINT("bIsAdmin", UserData.bIsAdmin);
	PRINT("bIsSuperAdmin", UserData.bIsSuperAdmin);
	PRINT("bIsModerator", UserData.bIsModerator);
	PRINT("bisBanned", UserData.bisBanned);
}

bool CXenForo::sendRequest(std::string_view szLogin, std::string_view szPassword)
{

	auto cprRequest = cpr::Post(cpr::Url{ fmt::format("{}{}", m_szApiUrl, "/auth/") }, cpr::Body{ fmt::format("login={}&password={}&api_bypass_permissions=1", szLogin, szPassword) }, m_cprHeader);

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

	/* user field is missing, should not be triggered since we search for the error message first */
	if (!parsedResponse.contains("user")) 
	{
		std::cout << "[forum] User field is missing." << std::endl;
		return false;
	}

	auto parsedUser = parsedResponse["user"];

	/* storing response variables into the UserData struct */
	UserData.szUsername = parsedUser["username"];
	UserData.szEmail = parsedUser["email"];
	UserData.szProfileUrl = parsedUser["view_url"];
	UserData.iUserId = parsedUser["user_id"];
	UserData.iPrimaryUserGroup = parsedUser["user_group_id"];
	UserData.iWarningPoints = parsedUser["warning_points"];
	UserData.vecSecondaryUserGroups = parsedUser["secondary_group_ids"].get<std::vector<int>>(); /* parse the array into a vector */
	UserData.bIsAdmin = parsedUser["is_admin"];
	UserData.bIsSuperAdmin = parsedUser["is_super_admin"];
	UserData.bIsModerator = parsedUser["is_moderator"];
	UserData.bisBanned = parsedUser["is_banned"];

	if (parsedUser["avatar_urls"]["o"].is_null()) /* can be null if no set avatar ! */
	{
		UserData.szAvatarUrl = "not set"; /* replace it with some generic avatar link */
	}
	else
	{
		UserData.szAvatarUrl = parsedUser["avatar_urls"]["o"];
	}

	/* finished storing the variables */

	return true;
}

/* basic authentication checking if user is banned etc */
bool CXenForo::authenticate()
{
	/* checking if banned */
	if (UserData.bisBanned)
	{
		std::cout << "[forum] User is banned." << std::endl;
		return false;
	}

	/* checking if a staff member */
	if (UserData.bIsAdmin || UserData.bIsSuperAdmin || UserData.bIsModerator)
	{
		std::cout << "[forum] Authenticated staff member." << std::endl;
		return true;
	}

	/* checking if parsed secondary usergroups matches with the allowed usergroup */
	if (std::find(UserData.vecSecondaryUserGroups.begin(), UserData.vecSecondaryUserGroups.end(), 3 /* allowed usergroup */) != UserData.vecSecondaryUserGroups.end())
	{
		std::cout << "[forum] Authenticated user." << std::endl;
		return true;
	}

	/* todo: hwid check? */

	/* none of the requirements are met */
	std::cout << "[forum] Authentication unsuccessful." << std::endl;
	return false;
}

CXenForo g_XenForo;