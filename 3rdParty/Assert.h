#ifndef Assert_h
#define Assert_h

#include <sstream>

#ifdef ENABLE_ASSERTS

	bool internal_assert(const char* file, unsigned int line, const char* expression, const std::string& description);

	#define ASSERT_DESCRIPTION(expression, description) \
		if (!(expression)) \
		{ \
			std::ostringstream stream; \
			stream << description; \
			if (internal_assert(__FILE__, __LINE__, #expression, stream.str())) \
			{ \
				__debugbreak();\
			} \
		} \

	#define ASSERT_RESULT_DECL(resultVariable, expression) resultVariable = expression
#else 

	#define ASSERT_DESCRIPTION(expression, description)

	#define ASSERT_RESULT_DECL(resultVariable, expression) expression

#endif

#endif
