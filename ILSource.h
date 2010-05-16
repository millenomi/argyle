
#ifndef ILSource_H
#define ILSource_H 1

class ILRunLoop;

class ILSource {
public:
	virtual void performPeriodicWork() = 0;
	void setRunLoop(ILRunLoop* rl);
	
protected:
	ILRunLoop* runLoop();
	
private:
	ILRunLoop* _runLoop;
};

#endif // #ifndef ILSource_H
