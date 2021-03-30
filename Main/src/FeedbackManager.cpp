#include "stdafx.h"
#include "FeedbackManager.hpp"
#include "GameConfig.hpp"


FeedbackManager::FeedbackManager() {
    enabled = g_gameConfig.GetBool(GameConfigKeys::FeedbackEnabled);
    port = g_gameConfig.GetString(GameConfigKeys::FeedbackPort);

	connected = false;

	//Try to connect to the given port throuh CreateFile
	std::wstring s_temp = std::wstring(port.begin(), port.end());

	this->hSerial = CreateFile(s_temp.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (this->hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {

			printf("ERROR: Handle was not attached. Reason: %s not available.\n", port);

		}
		else
		{
			printf("ERROR!!!");
		}
	}
	else {

		connected = true;
	}
}

FeedbackManager::~FeedbackManager()
{
	if (connected)
	{
		connected = false;
		CloseHandle(hSerial);
	}
}


void FeedbackManager::slam(FeedbackLaser laser) {
	const char buffer[2] = { getLaserCode(laser), 0 };
	WriteData(buffer, 2);
}

char FeedbackManager::getLaserCode(FeedbackLaser laser) {
	if (laser == FeedbackLaser::Left) {
		return 2;
	}
	else {
		return 1;
	}
}

bool FeedbackManager::WriteData(const char *buffer, unsigned int nbChar)
{
	DWORD bytesSend;

	//Try to write the buffer on the Serial port
	if (!WriteFile(hSerial, (void *)buffer, nbChar, &bytesSend, 0))
	{
		return false;
	}
	else
	{
		return true;
	}

	printf("Sent bytes: %u\n", bytesSend);

}