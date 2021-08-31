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

extern CXenForo g_XenForo;
