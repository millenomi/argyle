
#include "Argyle.h"
#include "ILSource.h"
#include "ILRunLoop.h"

void ILSource::setRunLoop(ILRunLoop* rl) {
	_runLoop = rl;
}

ILRunLoop* ILSource::runLoop() {
	return _runLoop;
}

