/* header guard */
#pragma once

/* windows includes */
#include <string>
#include <iostream>
#include <vector>

/* dependency includes */
#include <cpr/cpr.h>
#include <fmt/core.h>

/* includes */
#include "../Json/Json.hpp"

/* saving some values of the response from the auth.php endpoint into a struct */
struct UserData_t
{
	std::string szUsername;
	std::string szEmail;
	std::string szAvatarUrl;
	std::string szProfileUrl;
	int iUserId;
	int iPrimaryUserGroup;
	int iWarningPoints;
	std::vector<int> vecSecondaryUserGroups;
	bool bIsAdmin;
	bool bIsSuperAdmin;
	bool bIsModerator;
	bool bisBanned;
};

class CXenForo
{
public:
	UserData_t UserData;

	void initialize(std::string_view szApiUrl, std::string_view szApiKey); /* saving api url and api key into private member variables */
	void printUserData();
	bool sendRequest(std::string_view szLogin, std::string_view szPassword); /* post request to the /auth/ endpoint */
	bool authenticate();

private:
	std::string m_szApiUrl;
	std::string m_szApiKey;
	cpr::Header m_cprHeader;
};

extern CXenForo g_XenForo;