// $Id: constantes.cpp 40 2010-07-16 22:04:49Z mgpensar $

#ifdef VISUAL_STUDIO
  #include "stdafx.h"
#endif

#ifdef CODE_GEAR
#pragma hdrstop
#endif

#include "constantes.h"

namespace pensar_digital
{
    namespace cpplib
    {
        const int ID_INEXISTENTE = -1;
        #ifdef CODE_GEAR
        #pragma package(smart_init)
        #endif
    }   // namespace cpplib
}       // namespace pensar_digital
