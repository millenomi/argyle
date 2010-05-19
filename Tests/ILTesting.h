
#include "Argyle.h"

namespace ILTest {
	
	class TestCase;
	class Results : public ILObject {
	public:
		virtual void didBeginTestCase(TestCase* c, const char* what) {}
		virtual void passed(TestCase* c, const char* description) {}
		virtual void failed(TestCase* c, const char* description) {}
	};
	
	class TestCase : public ILObject {
		Results* _r;
		const char* _name;
		
	protected:
		void began(const char* what);
		
	public:
		TestCase(Results* r, const char* name);
		virtual ~TestCase();
		virtual void run() = 0;
		
		const char* name();
		
	protected:
		void assertTrue(bool c, const char* description, ...);
	};

	
#define ILTestTrue(condition) this->assertTrue(condition, "%s at %s:%d", #condition, __FILE__, __LINE__)
#define ILTestFalse(condition) this->assertTrue(!(condition), "!(%s) at %s:%d", #condition, __FILE__, __LINE__)

#define ILTestEqualValues(a, b) this->assertTrue(sizeof(a) == sizeof(b) && a == b, "%s == %s at %s:%d", #a, #b, __FILE__, __LINE__)
#define ILTestNotEqualValues(a, b) this->assertTrue(sizeof(a) != sizeof(b) || a != b, "%s != %s at %s:%d", #a, #b, __FILE__, __LINE__)
	
#define ILTestEqualObjects(a, b) this->assertTrue((a)->equals(b), "%s equal()s %s at %s:%d", #a, #b, __FILE__, __LINE__)
#define ILTestNotEqualObjects(a, b) this->assertTrue(!((a)->equals(b)), "%s not equal()s %s at %s:%d", #a, #b, __FILE__, __LINE__)
}
