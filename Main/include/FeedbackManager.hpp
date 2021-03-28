#pragma once

#include "stdafx.h"

class FeedbackManager {

public:
	FeedbackManager();
	~FeedbackManager();

	void slam();

private:
	HANDLE hSerial;
    bool enabled;
	bool connected;
    String port;

	bool WriteData(const char *buffer, unsigned int nbChar);
};
