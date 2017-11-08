// $Id: sys_user_info.cpp 40 2010-07-16 22:04:49Z mgpensar $

#ifdef VISUAL_STUDIO
#include "stdafx.h"
#endif

#ifdef CODE_GEAR
#pragma hdrstop
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

#include "sys_user_info.h"

//---------------------------------------------------------------------------

#ifdef CODE_GEAR
#pragma package(smart_init)
#endif

namespace pensar_digital
{
    namespace cpplib
    {
        #ifdef WIN32
        void getUserName (std::string* s)
        {
            unsigned long max = 100;
            char buf[100];
            bool ok = GetUserName(buf, &max) != 0;
            if (!ok) throw "getUserName: Não foi possível pegar o nome do usuário.";
            *s = buf;
        }
        #endif

        fs::path get_user_home ()
        {
            char*  s;
            std::string home;

            #ifdef WINDOWS
            // Get home dir from environment variables
            s = getenv("USERPROFILE");
            if (s)
            {
                if (s)
                    home = s;
            }
            else
            {
                s = getenv("HOMEPATH");
                char* home_drive = getenv ("HOMEDRIVE");
                if (home_drive)
                    home = home_drive;
                home += s;
            }
            #elif defined(UNIX)
            // Try get home dir from environment variable
            s = getenv("HOME");
            if (s)
                home = str;
            else
            {
                // Try to retrieve the home dir -- first use user's ID,
                //  and if failed, then use user's login name.
                if (!s_GetHomeByUID(home))
                {
                    s_GetHomeByLOGIN(home);
                }
            }
            #endif

         return home;
        }
    }   // namespace cpplib
}       // namespace pensar_digital
