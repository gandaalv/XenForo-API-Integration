/* header guard */
#pragma once

/* windows includes */
#include <string>
#include <vector>
#include <iostream>

/* dependency includes */
#include <cpr/cpr.h>
#include <fmt/core.h>
#include <json/json.hpp>

struct Auth_t
{
	bool success;

	struct User_t
	{
		std::string about;
		bool activity_visible;
		int age;
		std::vector<int> alert_optout; /* i guess its an integer? */
		std::string allow_post_profile;
		std::string allow_receive_news_feed;
		std::string allow_send_personal_conversation;
		std::string allow_view_identities;
		std::string allow_view_profile;
		struct AvatarUrls_t
		{
			std::string o, h, l, m, s;
		} avatar_urls;
		bool can_ban;
		bool can_converse;
		bool can_edit;
		bool can_follow;
		bool can_ignore;
		bool can_post_profile;
		bool can_view_profile;
		bool can_view_profile_posts;
		bool can_warn;
		bool content_show_signature;
		std::string creation_watch_state;
		struct CustomFields_t
		{
			std::string skype, facebook, twitter;
		} custom_fields;
		std::string custom_title;
		struct DateOfBirth_t
		{
			int year, month, day;
		} dob;
		std::string email;
		bool email_on_conversation;
		std::string gravatar;
		std::string interaction_watch_state;
		bool is_admin;
		bool is_banned;
		bool is_discouraged;
		bool is_moderator;
		bool is_staff;
		bool is_super_admin;
		int last_activity;
		std::string location;
		int message_count;
		struct ProfileBannerUrls_t
		{
			std::string m, l;
		} profile_banner_urls;
		bool push_on_conversation;
		std::vector<int> push_optout; /* i guess integer again? */
		int question_solution_count;
		int reaction_score;
		bool receive_admin_email;
		int register_date;
		std::vector<int> secondary_group_ids; /* thats an int for sure */
		bool show_dob_date;
		bool show_dob_year;
		std::string signature;
		std::string timezone;
		int trophy_points;
		bool usa_tfa; /* can be a array apperently? + typo from xenforo */
		int user_group_id;
		int user_id;
		std::string user_state;
		std::string user_title;
		std::string username;
		std::string view_url;
		bool visible;
		int vote_score;
		int warning_points;
		std::string website;

	} User;
};

class CAuth
{
public:
	bool setup(std::string_view szEndpointUrl, std::string_view szApiKey);
	bool request(std::string_view szLogin, std::string_view szPassword);

	Auth_t Vars;

private:
	std::string m_szEndpointUrl;
	std::string m_szApiKey;
	cpr::Header m_cprHeader;
};