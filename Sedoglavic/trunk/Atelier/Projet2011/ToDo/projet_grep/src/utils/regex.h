#ifndef _REGEX_H_
#define _REGEX_H_ 1


/*
  returns 1 if matches
  returns 0 if not matches
  returns -1 wrong regex
  returns -2 wrong arguments
 */
extern int
RegexMatchesWith (const char * regex, const char *string);

#endif /* _REGEX_H_ */
