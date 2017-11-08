// $Id: validation.h 32 2010-07-15 03:57:01Z mgpensar $

#ifndef validationH
#define validationH
#endif


#include <string>

/// Checks if parameter is in range.
/// \param param_name the parameter name
/// \param value the parameter value
/// \param min minimum value.
/// \param max maximum value.
/// \param loc the locale, default locale is platform dependent.
/// \throws std::invalid_argument exception if value is not in range.
template <typename T, class String = std::string>
void argument_range_check (String param_name, T value, T min, T max, Locale loc = locale())
{
    if (value < min)
    {
        std::stringstream ss;
        ss << param_name << " = " << value << " is less than min (" << min << ")." << std::endl;
        throw std::invalid_argument (ss.str ());
    }
    else if (value > max)
    {
        std::stringstream ss;
        ss << param_name << " = " << value << " is greater than max (" << min << ")." << std::endl;
        throw std::invalid_argument (ss.str ());
    }
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
