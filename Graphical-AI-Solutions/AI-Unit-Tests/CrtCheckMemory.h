#pragma once
#include "CppUnitTest.h"
#include <crtdbg.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct CrtCheckMemory
{
	_CrtMemState state1;
	_CrtMemState state2;
	_CrtMemState state3;
	CrtCheckMemory()
		: state1(_CrtMemState())
		, state2(_CrtMemState())
		, state3(_CrtMemState())
	{
		_CrtMemCheckpoint(&state1);
	}
	~CrtCheckMemory()
	{
		_CrtMemCheckpoint(&state2);

		// else just do this to dump the leaked blocks to stdout.
		if (_CrtMemDifference(&state3, &state1, &state2))
			_CrtMemDumpStatistics(&state3);

		// using google test you can just do this.
		Assert::AreEqual(0, _CrtMemDifference(&state3, &state1, &state2));
	}
};
