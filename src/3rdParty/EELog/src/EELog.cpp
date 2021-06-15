/*
*   EELog.cpp
*
*
*  Epee Engine
*  Created by Alan Uthoff on 3/12/06.
Copyright (C) 2012

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
#include "EELog.h"
#include <iostream>
#include "EEStream.h"
#include "EENullStream.h"
#include "EEAssertStream.h"

EELog * EELog::GetInstance() 
{
    static EELog EELogInstance;
    if(!EELogInstance.isInited)
	{
        EELogInstance.Init();
	}
    return &EELogInstance;
}


void EELog::Init()
{
    isInited = true;
#ifdef TURN_OFF_LOGGING
    EENullStream * nullStream = new EENullStream();
    m_StreamLevels[EE_LEVEL_DEBUG] = nullStream;
    m_StreamLevels[EE_LEVEL_INFO] = nullStream;
    m_StreamLevels[EE_LEVEL_WARNING] = nullStream;
    m_StreamLevels[EE_LEVEL_ERROR] = nullStream;
#else
	m_StreamLevels[EE_LEVEL_INFO] = new EEStream();
	m_StreamLevels[EE_LEVEL_WARNING] = new EEStream();
    m_StreamLevels[EE_LEVEL_ERROR] = static_cast<EEStream *>(new EEAssertStream(std::cerr));
#ifdef NDEBUG
	m_StreamLevels[EE_LEVEL_DEBUG] = new EENullStream();
#else
	m_StreamLevels[EE_LEVEL_DEBUG] = new EEStream();
#endif

#endif
}

EELog::~EELog()
{
    if(isInited)
    {
#ifdef TURN_OFF_LOGGING
        delete m_StreamLevels[EE_LEVEL_DEBUG];
#else
        delete m_StreamLevels[EE_LEVEL_INFO];
        delete m_StreamLevels[EE_LEVEL_WARNING];
        delete m_StreamLevels[EE_LEVEL_ERROR];
        delete m_StreamLevels[EE_LEVEL_DEBUG];
#endif
    }
}

void EELog::PrependLevelInformation(EELogLevels _Level)
{
	EEStream * LevelStream = (m_StreamLevels[_Level]);
	assert(LevelStream != NULL);
	if(LevelStream == NULL)
		return;
	switch (_Level)
	{
	case EE_LEVEL_INFO:
		(*LevelStream)<<"INFO:";
		break;
	case EE_LEVEL_WARNING:
		(*LevelStream)<<"WARNNING:";
		break;
	case EE_LEVEL_ERROR:
		(*LevelStream)<<"ERROR:";
		break;
	case EE_LEVEL_DEBUG:
		(*LevelStream)<<"DEBUG:";
		break;
	default:
		break;
	}

}

EEStream & EELog::GetLogLevel(EELogLevels _Level)
{
	assert(_Level != EE_LEVEL_LAST);//EE_LEVEL_LAST is not a vaild level see EELogLevels for vaild list
	if(_Level == EE_LEVEL_LAST)
	{
		PrependLevelInformation(EE_LEVEL_INFO);
		return *(m_StreamLevels[EE_LEVEL_INFO]);
	}

	PrependLevelInformation(_Level);
	return *(m_StreamLevels[_Level]);
}
