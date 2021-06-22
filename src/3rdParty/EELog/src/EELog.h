/*
*  EELog.h
*
*  Epee Engine
*  Created by Alan Uthoff on 3/12/06.
Copyright (C) 2011

This Code is free software; you can redistribute it and/or
modify it under the terms of the zlib/libpng License as published
by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.


*/
#ifndef Example_EELog_h
#define Example_EELog_h
#include "EEStream.h"
#include <ostream>
#include <sstream>
#ifndef  TURN_ON_LOGGING
    #define TURN_OFF_LOGGING
#endif
enum EELogLevels
{
	EE_LEVEL_INFO = 0,
	EE_LEVEL_WARNING,
	EE_LEVEL_ERROR,
	EE_LEVEL_DEBUG,
	EE_LEVEL_LAST,
};

#ifdef TURN_OFF_LOGGING
    #define EE_INFO	EELog::GetInstance()->GetLogLevel(EE_LEVEL_INFO)
    #define EE_WARNING EELog::GetInstance()->GetLogLevel(EE_LEVEL_WARNING)
    #define EE_ERROR  EELog::GetInstance()->GetLogLevel(EE_LEVEL_ERROR)
    #define EE_DEBUG EELog::GetInstance()->GetLogLevel(EE_LEVEL_DEBUG)
#else
    #define EE_INFO	EELog::GetInstance()->GetLogLevel(EE_LEVEL_INFO)
    #define EE_WARNING EELog::GetInstance()->GetLogLevel(EE_LEVEL_WARNING)
    #define EE_ERROR  EELog::GetInstance()->GetLogLevel(EE_LEVEL_ERROR)
    #define EE_DEBUG EELog::GetInstance()->GetLogLevel(EE_LEVEL_DEBUG)
#endif
class EELog
{

public:
	static EELog * GetInstance();
	static void Destroy();
	EEStream & GetLogLevel(EELogLevels _Level);

protected:
	EEStream * m_StreamLevels[EE_LEVEL_LAST];
private:
	static EELog * EELogInstance;
    bool isInited;
    EELog(){isInited = false;}
    ~EELog();
	EELog(const EELog &){};
	EELog & operator = (const EELog &)
	{
		return *this;
	}
	void Init();
	void TearDown();
	void PrependLevelInformation(EELogLevels _Level);

};

#endif
