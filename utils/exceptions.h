//
// Created by Андрей on 01.05.2023.
//

#ifndef DZ2_OOP_UTILS_EXCEPTIONS_H_
#define DZ2_OOP_UTILS_EXCEPTIONS_H_


#include <cstdio>
#include <exception>


inline const int DEFAULT_EXC_STR_LEN = 400;


class BaseException : public std::exception
{
 public:
	explicit BaseException(
		const  char * filename,
		const  int line,
		const char *className,
		const char *time,
		const char *exceptionName,
		const char *additionalInfo)
	{
		sprintf(errorText,
			"In file: %s\n"
			"at line: %d\n"
			"in class: %s\n"
			"on time: %s\n"
			"source: %s\b"
			"reason: %s\n",
			filename, line, className, time, exceptionName,additionalInfo);
	}

	virtual const char *what() const noexcept
	{
		return errorText;
	}

 private:
	char errorText[DEFAULT_EXC_STR_LEN];
};





























#endif //DZ2_OOP_UTILS_EXCEPTIONS_H_
