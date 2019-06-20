/* author: Tim */

#pragma once
#include <iostream>
#include <string>
#include <time.h>

// Include this file for debugging. Also contains headers that should only be used for debugging, like iostream
// This file and fucntions are to be used only in Debug mode. Using them in release mode will cause an early termination.

namespace Debug
{
	void initialize();
	void log(std::string msg);
	void close();
}