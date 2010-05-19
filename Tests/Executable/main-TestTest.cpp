
#include "Argyle.h"
#include "ILApp.h" // TODO
#include "ILTesting.h"

#include <cstdio>
using namespace ILTest;

class TestTest : public TestCase {
public:
	TestTest(Results* r) : TestCase(r, "TestTest") {}
	
	virtual void run() {
		began("Test basic assertion methods");
		ILTestTrue(true);
		ILTestFalse(false);
		ILTestEqualValues(1, 1);
		ILTestNotEqualValues(1, 2);
		ILTestNotEqualValues(1, (double)1);
		ILTestEqualObjects(new ILNumber(42), new ILNumber(42));
		ILTestNotEqualObjects(new ILNumber(42), new ILNumber(33));
	}
};

class ResultStdoutDisplay : public Results {
	virtual void didBeginTestCase(TestCase* c, const char* what) {
		printf(" == == = STARTING TEST CASE: %s of %s\n", what, c->name());
	}
	
	virtual void passed(TestCase* c, const char* description) {
		printf(" ok: %s\n", description);
	}
	
	virtual void failed(TestCase* c, const char* description) {
		fprintf(stderr, "!! failed: %s\n", description);
	}
};

int main(int argc, const char* argv[]) {
	ILReleasePool pool;
	ILApp app(argc, argv);

	TestTest* t = new TestTest(new ResultStdoutDisplay());
	t->run();
	
	return app.end();
}
