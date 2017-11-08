// $Id: posix_util.h 9 2009-04-29 17:31:00Z mgpensar $

//---------------------------------------------------------------------------
// POSIXUtil.h
//---------------------------------------------------------------------------
//                           -=* VPatch *=-
//---------------------------------------------------------------------------
// Copyright (C) 2001-2005 Koen van de Sande / Van de Sande Productions
//---------------------------------------------------------------------------
// Website: http://www.tibed.net/vpatch
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#if !defined(POSIXUtil_H)
  #define POSIXUtil_H
  #include "global_types.h"
  #include "mg.h"
  #include <string>

  using namespace std;

  namespace POSIX
  {
	typedef struct ALT_FILETIME {
	  uint32_t dwLowDateTime;
	  uint32_t dwHighDateTime;
	} ALT_FILETIME;

	bool operator < (const ALT_FILETIME& left, const ALT_FILETIME& right);

	ALT_FILETIME getFileTime(const char* sFileName);
	uint32_t getFileSize(const char* sFileName);
	wstring getTempFile();
	extern void TimeT_To_FILETIME(time_t t, ALT_FILETIME *pft );
  }

#endif // POSIXUtil_H


