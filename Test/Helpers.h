#pragma once

#include <iostream>
#include <sstream>

namespace Tests
{
	struct CaptureStdout
	{
		std::stringstream buffer;
		std::streambuf* oldCout;

		CaptureStdout() : oldCout(std::cout.rdbuf(buffer.rdbuf())) {}
		~CaptureStdout() { std::cout.rdbuf(oldCout); }

		std::string str() const { return buffer.str(); }
	};
}

