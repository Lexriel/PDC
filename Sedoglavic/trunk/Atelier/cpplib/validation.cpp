// $Id: validation.cpp 32 2010-07-15 03:57:01Z mgpensar $

#ifdef VISUAL_STUDIO
#include "stdafx.h"
#endif
#ifdef CODE_GEAR
#pragma hdrstop
#endif

#include <vector>

#include "validation.hpp"
#include "string_util.h"

namespace pensar_digital
{
    namespace cpplib
    {

        #ifdef CODE_GEAR

        const AnsiString MSG_INVALID_DATE  = "Por favor preencha uma data no formato dd/mm/yyyy.";
        const AnsiString MSG_INVALID_CPF_1 = "Número de dígitos do CPF está incorreto. Por favor redigite.";
        const AnsiString MSG_INVALID_CPF_2 = "CPF inválido. Por favor redigite.";
        const AnsiString MSG_INVALID_NAME  = "Por favor preencha seu nome completo sem abreviações.";
        const AnsiString MSG_EMPTY         = "Por favor preencha o campo acima.";
        const AnsiString MSG_INVALID_PHONE_NUMBER = "Número de telefone inválido, por favor redigite.";

        const int CPF_SIZE = 11;

        VALIDATION_RESULT is_valid_cpf  (AnsiString cpf, void* somepointer, bool use_exception) throw (cpf_exception)
        {
            VALIDATION_RESULT vr;
            vr.ok = true;

            AnsiString d = only_digits (cpf);
            if (d.Length() != CPF_SIZE)
            {
                vr.err_msg = MSG_INVALID_CPF_1;
                vr.ok = false;
                if (use_exception) throw cpf_exception (vr.err_msg, somepointer);
            }
            else
            {
                int i;
                int j; // just count
                int digit; // A number digit
                int coeficient; // A coeficient
                int sum; // The sum of (Digit * Coeficient)
                int foundDv[] = { 0, 0 }; // The found Dv1 and Dv2
                int dv1 = StrToInt (d[CPF_SIZE - 1]);
                int dv2 = StrToInt (d[CPF_SIZE]);
                for (j = 0; j < 2; j++)
                {
                    sum = 0;
                    coeficient = 2;
                    for (i = CPF_SIZE - 2 + j; i >= 1; i--)
                    {
                        digit = StrToInt (d[i]);
                        sum += digit * coeficient;
                        coeficient++;
        //				if (coeficient > 9 && isCnpj)
        //					coeficient = 2;
                    }
                    foundDv[j] = CPF_SIZE - sum % CPF_SIZE;
                    if (foundDv[j] >= 10)
                        foundDv[j] = 0;
                }
                if (! (dv1 == foundDv[0] && dv2 == foundDv[1]))
                {
                    vr.ok = false;
                    vr.err_msg = MSG_INVALID_CPF_2;
                    if (use_exception) throw cpf_exception (vr.err_msg, somepointer);
                }
            }
            return vr;
        }
        //---------------------------------------------------------------------------

        VALIDATION_RESULT is_valid_cnpj (AnsiString cnpj, void* somepointer, bool use_exception) throw (cnpj_exception)
        {
            VALIDATION_RESULT vr;
            vr.ok = true;
            return vr;
        }
        //---------------------------------------------------------------------------

        VALIDATION_RESULT is_valid_complete_name (AnsiString name, void* somepointer, bool use_exception) throw (name_exception)
        {
            VALIDATION_RESULT vr;
            vr.ok = true;

            vector<string> v;
            split (name.c_str (), ' ', &v);
            if (v.size () < 2 || name.Pos(".") != 0)
            {
                vr.ok = false;
                vr.err_msg = MSG_INVALID_NAME;
                if (use_exception) throw name_exception (vr.err_msg, somepointer);
            }

            return vr;
        }
        //---------------------------------------------------------------------------

        VALIDATION_RESULT is_not_empty (AnsiString s, void* somepointer, bool use_exception) throw (validation_exception)
        {
            VALIDATION_RESULT vr;
            vr.ok = true;

            if (s == "")
            {
                vr.ok = false;
                vr.err_msg = MSG_EMPTY;
                if (use_exception) throw validation_exception (vr.err_msg, somepointer);
            }

            return vr;
        }
        //---------------------------------------------------------------------------

        VALIDATION_RESULT is_valid_date (AnsiString date, void* somepointer, bool use_exception) throw (date_exception)
        {
            VALIDATION_RESULT vr;
            vr.ok = true;
            try
            {
                StrToDate (date);
            }
            catch (EConvertError& e)
            {
                vr.ok = false;
                vr.err_msg = MSG_INVALID_DATE;
                if (use_exception) throw date_exception (vr.err_msg, somepointer);
            }
            return vr;
        }
        //---------------------------------------------------------------------------

        VALIDATION_RESULT is_valid_phone_number (AnsiString phone, void* somepointer, bool use_exception) throw (validation_exception)
        {
            VALIDATION_RESULT vr;
            vr.ok = true;
            static const int MIN_SIZE = 8;
            static const int MAX_SIZE = 13;

            AnsiString d = only_digits (phone);
            if (d.Length() < MIN_SIZE || d.Length () > MAX_SIZE)
            {
                vr.err_msg = MSG_INVALID_PHONE_NUMBER;
                vr.ok = false;
                if (use_exception) throw validation_exception (vr.err_msg, somepointer);
            }
            return vr;
        }
        //---------------------------------------------------------------------------

            AnsiString format_cpf (AnsiString cpf)
            {
                AnsiString d = only_digits (cpf);
                AnsiString result = d;
                int size = d.Length ();
                if (size == CPF_SIZE)
                {
                    AnsiString n1 = d.SubString (0, 3);
                    AnsiString n2 = d.SubString (4, 3);
                    AnsiString n3 = d.SubString (7, 3);
                    AnsiString dv = d.SubString (10, 2);
                    result = n1 + "." + n2 + "." + n3 + "-" + dv;
                }
                return result;
            }

#pragma package(smart_init)
#endif
    }   // namespace cpplib
}       // namespace pensar_digital
