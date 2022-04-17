#ifndef _INSTANCE_READER_H_
#define _INSTANCE_READER_H_

#include <string>
#include "matriz.h"

class ProblemInstanceFileError: public std::exception {
	private:
		std::string wrongInput;
	public:
		ProblemInstanceFileError(std::string wrongInput_): wrongInput(wrongInput_){}
		const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW;
};

class InstanceReader {
    public:
        InstanceReader(){}
        ProblemInstance readFromStdin();
};

#endif