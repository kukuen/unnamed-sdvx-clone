#pragma once

#include "stdafx.h"

DefineEnum(
	FeedbackLaser,
	Left,
	Right
)

class FeedbackManager {

public:
	FeedbackManager();
	~FeedbackManager();

	void slam(FeedbackLaser laser);

private:
	HANDLE hSerial;
    bool enabled;
	bool connected;
    String port;

	bool WriteData(const char *buffer, unsigned int nbChar);

	static char getLaserCode(FeedbackLaser laser);
};
