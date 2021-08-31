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

#ifdef _DEBUG
	std::cout << szResponse << std::endl;
#endif

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

	Vars.User.about = parsedUser["about"];
	Vars.User.activity_visible = parsedUser["activity_visible"];
	Vars.User.age = parsedUser["age"];
	Vars.User.alert_optout = parsedUser["alert_optout"].get<std::vector<int>>();
	Vars.User.allow_post_profile = parsedUser["allow_post_profile"];
	Vars.User.allow_receive_news_feed = parsedUser["allow_receive_news_feed"];
	Vars.User.allow_send_personal_conversation = parsedUser["allow_send_personal_conversation"];
	Vars.User.allow_view_identities = parsedUser["allow_view_identities"];
	Vars.User.allow_view_profile = parsedUser["allow_view_profile"];
	auto avatarUrls = parsedUser["avatar_urls"];
	Vars.User.avatar_urls.o = avatarUrls["o"].is_null() ? "unknown" : avatarUrls["o"];
	Vars.User.avatar_urls.h = avatarUrls["h"].is_null() ? "unknown" : avatarUrls["h"];
	Vars.User.avatar_urls.l = avatarUrls["l"].is_null() ? "unknown" : avatarUrls["l"];
	Vars.User.avatar_urls.m = avatarUrls["m"].is_null() ? "unknown" : avatarUrls["m"];
	Vars.User.avatar_urls.s = avatarUrls["s"].is_null() ? "unknown" : avatarUrls["s"];
	Vars.User.can_ban = parsedUser["can_ban"];
	Vars.User.can_converse = parsedUser["can_converse"];
	Vars.User.can_edit = parsedUser["can_edit"];
	Vars.User.can_follow = parsedUser["can_follow"];
	Vars.User.can_ignore = parsedUser["can_ignore"];
	Vars.User.can_post_profile = parsedUser["can_post_profile"];
	Vars.User.can_view_profile = parsedUser["can_view_profile"];
	Vars.User.can_view_profile_posts = parsedUser["can_view_profile_posts"];
	Vars.User.can_warn = parsedUser["can_warn"];
	Vars.User.content_show_signature = parsedUser["content_show_signature"];
	Vars.User.creation_watch_state = parsedUser["creation_watch_state"];
	auto customFields = parsedUser["custom_fields"];
	Vars.User.custom_fields.skype = customFields["skype"].is_null() ? "unknown" : customFields["skype"];
	Vars.User.custom_fields.facebook = customFields["facebook"].is_null() ? "unknown" : customFields["facebook"];
	Vars.User.custom_fields.twitter = customFields["twitter"].is_null() ? "unknown" : customFields["twitter"];
	Vars.User.custom_title = parsedUser["custom_title"];
	/* object does not exist if dob is not saved in forum afaik. */
	if (parsedUser.contains("dob"))
	{
		auto dateOfBirth = parsedUser["dob"];
		Vars.User.dob.year = dateOfBirth["year"];
		Vars.User.dob.month = dateOfBirth["month"];
		Vars.User.dob.day = dateOfBirth["day"];
	}
	Vars.User.email = parsedUser["email"];
	Vars.User.email_on_conversation = parsedUser["email_on_conversation"];
	Vars.User.gravatar = parsedUser["gravatar"];
	Vars.User.interaction_watch_state = parsedUser["interaction_watch_state"];
	Vars.User.is_admin = parsedUser["is_admin"];
	/* for some reason the field disappeared in the response */
	if (parsedUser.contains("is_banned"))
	{
		Vars.User.is_banned = parsedUser["is_banned"];
	}
	Vars.User.is_discouraged = parsedUser["is_discouraged"];
	Vars.User.is_moderator = parsedUser["is_moderator"];
	Vars.User.is_staff = parsedUser["is_staff"];
	Vars.User.is_super_admin = parsedUser["is_super_admin"];
	Vars.User.last_activity = parsedUser["last_activity"];
	Vars.User.location = parsedUser["location"];
	Vars.User.message_count = parsedUser["message_count"];
	auto profileBannerUrls = parsedUser["profile_banner_urls"];
	Vars.User.profile_banner_urls.m = profileBannerUrls["m"].is_null() ? "unknown" : profileBannerUrls["m"];
	Vars.User.profile_banner_urls.l = profileBannerUrls["l"].is_null() ? "unknown" : profileBannerUrls["l"];
	Vars.User.push_on_conversation = parsedUser["push_on_conversation"];
	Vars.User.push_optout = parsedUser["push_optout"].get<std::vector<int>>();
	Vars.User.question_solution_count = parsedUser["question_solution_count"];
	Vars.User.reaction_score = parsedUser["reaction_score"];
	Vars.User.receive_admin_email = parsedUser["receive_admin_email"];
	Vars.User.register_date = parsedUser["register_date"];
	Vars.User.secondary_group_ids = parsedUser["secondary_group_ids"].get<std::vector<int>>();
	Vars.User.show_dob_date = parsedUser["show_dob_date"];
	Vars.User.show_dob_year = parsedUser["show_dob_year"];
	Vars.User.signature = parsedUser["signature"];
	Vars.User.timezone = parsedUser["timezone"];
	Vars.User.trophy_points = parsedUser["trophy_points"];
	Vars.User.usa_tfa = parsedUser["usa_tfa"];
	Vars.User.user_group_id = parsedUser["user_group_id"];
	Vars.User.user_id = parsedUser["user_id"];
	Vars.User.user_state = parsedUser["user_state"];
	Vars.User.user_title = parsedUser["user_title"];
	Vars.User.username = parsedUser["username"];
	Vars.User.view_url = parsedUser["view_url"];
	Vars.User.visible = parsedUser["visible"];
	Vars.User.vote_score = parsedUser["vote_score"];
	/* same here */
	if (parsedUser.contains("warning_points"))
	{
		Vars.User.warning_points = parsedUser["warning_points"];
	}
	Vars.User.website = parsedUser["website"];

	return true;
}