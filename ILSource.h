
#ifndef ILSource_H
#define ILSource_H 1

#include "ILObject.h"
#include "ILTime.h"

class ILRunLoop;

class ILSource : public ILObject {
public:
	virtual void spin() = 0;
	virtual void setRunLoop(ILRunLoop* rl);
	virtual ILRunLoop* runLoop();
	
	virtual ILTimeInterval nextDesiredExecutionTime();
	
private:
	ILRunLoop* _runLoop;
};

#endif // #ifndef ILSource_H
