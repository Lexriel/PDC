// $Id: validation.h 4 2009-04-09 00:29:51Z mgpensar $

#ifndef validationH
#define validationH
#endif


#include <string>
#include <locale>
#include <iostream>
#include <stdexcept>
#include <sstream>

namespace pensar_digital
{
    namespace cpplib
    {
        static const bool USE_EXCEPTIONS = false;

        /// Checks if parameter is in range.
        /// \param param_name the parameter name
        /// \param value the parameter value
        /// \param min minimum value.
        /// \param loc the locale, default locale is platform dependent.
        /// \throws std::invalid_argument exception if value is not in range.
        template <typename T, class String = std::string>
        bool min_check (T value, T min, String param_name = "", bool no_throw = true, std::locale loc = std::locale())
        {
            bool ok = true;
            std::stringstream ss;

            if (value < min)
            {
                ss << param_name << " = " << value << " is less than min (" << min << ")." << std::endl;
                ok = false;
                if (no_throw)
                    std::cerr << ss.str ();
                else
                    throw std::invalid_argument (ss.str ());
            }

            return ok;
        }

        /// Checks if parameter is in range.
        /// \param param_name the parameter name
        /// \param value the parameter value
        /// \param max maximum value.
        /// \param loc the locale, default locale is platform dependent.
        /// \throws std::invalid_argument exception if value is not in range.
        template <typename T, class String = std::string>
        bool max_check (T value, T max, String param_name = "", bool no_throw = true, std::locale loc = std::locale())
        {
            bool ok = true;
            std::stringstream ss;

            if (value > max)
            {
                ss << param_name << " = " << value << " is greater than max (" << max << ")." << std::endl;
                ok = false;
                if (no_throw)
                    std::cerr << ss.str ();
                else
                    throw std::invalid_argument (ss.str ());
            }

            return ok;
        }

        /// Checks if parameter is in range.
        /// \param param_name the parameter name
        /// \param value the parameter value
        /// \param min minimum value.
        /// \param max maximum value.
        /// \param loc the locale, default locale is platform dependent.
        /// \throws std::invalid_argument exception if value is not in range.
        template <typename T, class String = std::string>
        bool range_check (T value, T min, T max, String param_name = "", bool no_throw = true, std::locale loc = std::locale())
        {
            bool ok = min_check (value, min, param_name, no_throw, loc);
            if (ok)
                ok = max_check (value, max, param_name, no_throw, loc);
            return ok;
        }

        #ifdef CODE_GEAR
        #include <vcl.h>


        extern const AnsiString MSG_INVALID_DATE;
        extern const AnsiString MSG_INVALID_CPF_1;
        extern const AnsiString MSG_INVALID_CPF_2;
        extern const AnsiString MSG_INVALID_NAME;
        extern const AnsiString MSG_EMPTY;
        extern const AnsiString MSG_INVALID_PHONE_NUMBER;
        extern const int CPF_SIZE;

        typedef struct vr
        {
            bool ok;
            AnsiString err_msg;
            operator bool () const { return ok; }
            operator std::string () const
            {
                AnsiString s = ok ? "true" + err_msg: "false, " + err_msg;
                std::string s1 = s.c_str ();
                return s1;
            }
                bool operator == (const struct vr& v) {return ok == v.ok && err_msg == v.err_msg;}
        } VALIDATION_RESULT;

        class validation_exception// : public std::runtime_error
        {
            private:
            int err_code;
            void* p;
            AnsiString err_msg;
            public:
            validation_exception (AnsiString err_message = "", void* somepointer = 0, int err = 0): err_msg(err_message), err_code(err), p(somepointer) {};
            void* get_pointer () {return p;}
            AnsiString __fastcall what ()
            {
                return err_msg;
            }
            int __fastcall get_err_code () { return err_code; }
        };

        class cpf_exception : public validation_exception
        {
            public:
            cpf_exception (AnsiString err_msg = "", void* somepointer = 0, int err = 0) : validation_exception (err_msg, somepointer, err) {};
        };

        class cnpj_exception : public validation_exception
        {
            public:
            cnpj_exception (AnsiString err_msg = "", void* somepointer = 0, int err = 0) : validation_exception (err_msg, somepointer, err) {};
        };

        class date_exception : public validation_exception
        {
            public:
            date_exception (AnsiString err_msg = "", void* somepointer = 0, int err = 0) : validation_exception (err_msg, somepointer, err) {};
        };

        class name_exception : public validation_exception
        {
            public:
            name_exception (AnsiString err_msg = "", void* somepointer = 0, int err = 0) : validation_exception (err_msg, somepointer, err) {};
        };

        extern VALIDATION_RESULT is_valid_cpf  (AnsiString cpf, void* somepointer = 0,  bool use_exception = true) throw (cpf_exception);
        extern VALIDATION_RESULT is_valid_cnpj (AnsiString cnpj, void* somepointer = 0, bool use_exception = true) throw (cnpj_exception);
        extern VALIDATION_RESULT is_valid_complete_name (AnsiString name, void* somepointer = 0, bool use_exception = true) throw (name_exception);
        extern VALIDATION_RESULT is_not_empty (AnsiString s, void* somepointer = 0, bool use_exception = true) throw (validation_exception);
        extern VALIDATION_RESULT is_valid_date (AnsiString date, void* somepointer = 0, bool use_exception = true) throw (date_exception);
        extern VALIDATION_RESULT is_valid_phone_number (AnsiString phone, void* somepointer = 0, bool use_exception = true) throw (validation_exception);
#endif
    }   // namespace cpplib
}       // namespace pensar_digital
