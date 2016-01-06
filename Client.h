#pragma once
#ifndef _CLIENT_H_
#define _CLIENT_H_
#endif


namespace Client {
	enum LOGIN_STATUS {
		LOGIN_FAILED,
		LOGIN_SUCCESS,
		LOGIN_ERR_USERNAME,
		LOGIN_ERR_PASSWORD,
		LOGIN_ERR_CONNECTION,
	};

	enum GAMES {
		CSGO,
		BATTLEFIELD3,
		BATTLEFIELD,
	};
}