
#include "Argyle.h"
#include "ILApp.h" // TODO
#include "ILTesting.h"

#include <cstdio>
using namespace ILTest;

class TestTest : public TestCase {
	ILTestCase(TestTest) {
		ILTestWith(testBasics);
	}
	
	void testBasics() {
		ILTestTrue(true);
		ILTestFalse(false);
		ILTestEqualValues(1, 1);
		ILTestNotEqualValues(1, 2);
		ILTestNotEqualValues(1, (double)1);
		ILTestEqualObjects(new ILNumber(42), new ILNumber(42));
		ILTestNotEqualObjects(new ILNumber(42), new ILNumber(33));		
	}
};

int main(int argc, const char* argv[]) {
	ILReleasePool pool;
	ILApp app(argc, argv);
	
	TestCase::setDefaultResults(new ResultsStdoutDisplay());
	TestCase::runAllOf(new TestTest(), NULL);
	
	return app.end();
}
