#include "Assert.h"
#include <Windows.h>

bool
internal_assert(const char* file, unsigned int line, const char* expression, const std::string& description)
{
	std::ostringstream stream;
	stream << "Expression " << expression << " failed!" << std::endl << file << "(" << line << ") " << std::endl
		<< description << std::endl << "Do you want to ignore it and continue?";
	return MessageBoxA(0, stream.str().c_str(), "Assert!", MB_YESNO | MB_ICONEXCLAMATION | MB_DEFBUTTON2) != MB_OK;
}

