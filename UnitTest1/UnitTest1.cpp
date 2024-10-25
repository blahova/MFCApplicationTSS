#include "pch.h"
#include "CppUnitTest.h"
//#include "../TSS/Library.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// tu sa bude testovat funkcia na vypocet histogramu
			//treba pridat header file Library.h do projektu tss 
			//kde sa bude cosi definovat, ta funkcia teda, a tento header sa includne do tohto projectu ako #include "../TSS/Library.h"
			//potom sa ta funkcia bude volat TU
			//ta funkcia bude potom už nie v classe ale zvlast a všetko do nej musi ist ako vstup
		}
	};
}
