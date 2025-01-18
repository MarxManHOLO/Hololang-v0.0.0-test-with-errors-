#ifndef SHELLEXEC_H
#define SHELLEXEC_H

#include <stdio.h>
#include "SimpleString.h"
#include "HololangTypes.h"

namespace Hololang {


bool BeginExec(String cmd, double timeout, double currentTime, ValueList* outResult);


bool FinishExec(ValueList data, double currentTime, String* outStdout, String* outStderr, int* outStatus);



}

#endif 
