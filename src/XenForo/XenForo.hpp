/* header guard */
#pragma once

/* endpoints */
#include "Endpoints/Auth.hpp"

class CXenForo
{
public:
	struct Endpoints_t
	{
		CAuth Auth;
	} Endpoint;
};

CXenForo g_XenForo;
