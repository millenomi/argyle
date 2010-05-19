
#include "ILTesting.h"
#include <stdarg.h>
#include <stdio.h>

namespace ILTest {
	
	TestCase::TestCase(Results* r, const char* name) {
		_r = ILRetain(r);
		_name = name;
	}
	
	const char* TestCase::name() {
		return _name;
	}
	
	TestCase::~TestCase() {
		ILRelease(_r);
	}
	
	void TestCase::assertTrue(bool c, const char* description, ...) {
		va_list l;
		va_start(l, description);
		
		char* newString;
		vasprintf(&newString, description, l);
		va_end(l);

		if (c)
			_r->passed(this, newString);
		else
			_r->failed(this, newString);
		
		free(newString);
	}

	void TestCase::began(const char* what) {
		_r->didBeginTestCase(this, what);
	}
}
