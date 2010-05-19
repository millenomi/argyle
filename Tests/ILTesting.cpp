
#include "ILTesting.h"
#include <stdarg.h>
#include <stdio.h>

namespace ILTest {
	
	void TestCase::runAllOf(TestCase* t, ...) {
		va_list l;
		va_start(l, t);
		
		TestCase* theCase = t;
		while (theCase) {
			theCase->run();
			theCase = va_arg(l, TestCase*);
		}
		
		va_end(l);
	}
	
	static Results* ILTestDefaultResults = NULL;
	
	Results* TestCase::defaultResults() {
		return ILTestDefaultResults;
	}
	
	void TestCase::setDefaultResults(Results* r) {
		if (r != ILTestDefaultResults) {
			ILRelease(ILTestDefaultResults);
			ILTestDefaultResults = ILRetain(r);
		}
	}
	
	TestCase::TestCase(Results* r, const char* name) {
		if (!r)
			r = TestCase::defaultResults();
		
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
	
	void TestCase::setUp() {}
	void TestCase::tearDown() {}
	
	
	void Results::didBeginTestCase(TestCase* c, const char* what) {}
	void Results::passed(TestCase* c, const char* description) {}
	void Results::failed(TestCase* c, const char* description) {}	
	
	void ResultsStdoutDisplay::didBeginTestCase(TestCase* c, const char* what) {
		printf(" == == = STARTING TEST CASE: %s of %s\n", what, c->name());
	}
	
	void ResultsStdoutDisplay::passed(TestCase* c, const char* description) {
		printf(" ok: %s\n", description);
	}
	
	void ResultsStdoutDisplay::failed(TestCase* c, const char* description) {
		fprintf(stderr, "!! failed: %s\n", description);
	}
	
	Results::Results() {}
	Results::~Results() {}
}

