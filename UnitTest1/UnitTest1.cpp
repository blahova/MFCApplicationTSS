#include "pch.h"
#include "CppUnitTest.h"
#include "../MFCApplicationTSS/Library.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
        TEST_METHOD(TestHistogramSingleRedPixel)
        {
            // ediny pixel- iba cerveny
            const int width = 1;
            const int height = 1;
            const int stride = width * 4; 

            
            const BYTE pixels[] = {
                0, 0, 255, 0 
            };

            // ocakavane vysledky
            std::vector<int> expectedRed(256, 0), expectedGreen(256, 0), expectedBlue(256, 0);
            expectedRed[255] = 1;  
            expectedGreen[0] = 1;  
            expectedBlue[0] = 1;   

            // vypocitany vysledok
            std::vector<int> red(256), green(256), blue(256);
            CalculateHistogramFromPixels(pixels, width, height, stride, red, green, blue);

            Assert::IsTrue(red == expectedRed, L"Red histogram does not match expected values.");
            Assert::IsTrue(green == expectedGreen, L"Green histogram does not match expected values.");
            Assert::IsTrue(blue == expectedBlue, L"Blue histogram does not match expected values.");
        }

        TEST_METHOD(TestHistogram2x2Pixels)
        {
            // 2x2 pixlov
            const int width = 2;
            const int height = 2;
            const int stride = width * 4; 
            const BYTE pixels[] = {
                0, 0, 128, 0,   // tmavo cervena
                0, 128, 0, 0,   // tmavo zelena
                128, 0, 0, 0,   // tmavo modra
                64, 64, 64, 0   // tmava seda
            };

            std::vector<int> expectedRed(256, 0), expectedGreen(256, 0), expectedBlue(256, 0);
            expectedRed[128] = 1;  
            expectedRed[64] = 1;   
            expectedRed[0] = 2;    
            
            expectedGreen[128] = 1; 
            expectedGreen[64] = 1;  
            expectedGreen[0] = 2;   

            expectedBlue[128] = 1; 
            expectedBlue[64] = 1;   
            expectedBlue[0] = 2;    

            std::vector<int> red(256), green(256), blue(256);
            CalculateHistogramFromPixels(pixels, width, height, stride, red, green, blue);

            Assert::IsTrue(red == expectedRed, L"Red histogram does not match expected values.");
            Assert::IsTrue(green == expectedGreen, L"Green histogram does not match expected values.");
            Assert::IsTrue(blue == expectedBlue, L"Blue histogram does not match expected values.");
        }

        TEST_METHOD(TestHistogram3x3Pixels)
        {
            // 3x3 obrazok
            const int width = 3;
            const int height = 3;
            const int stride = width * 4; 
            const BYTE pixels[] = {
                0, 0, 255, 0,  // cervena
                0, 255, 0, 0,  // zelena
                255, 0, 0, 0,  // modra
                0, 255, 255, 0, // zlta
                255, 255, 0, 0, // tyrkysova
                255, 0, 255, 0, // maenta
                255, 255, 255, 0, // biela
                0, 0, 0, 0,  // cierna
                128, 128, 128, 0  // seda
            };

            std::vector<int> expectedRed(256, 0), expectedGreen(256, 0), expectedBlue(256, 0);
            expectedRed[255] = 4;  
            expectedRed[0] = 4;    
            expectedRed[128] = 1; 
            expectedGreen[255] = 4;
            expectedGreen[0] = 4;   
            expectedBlue[255] = 4; 
            expectedBlue[0] = 4;   
            expectedBlue[128] = 1;
            expectedGreen[128] = 1;

            std::vector<int> red(256), green(256), blue(256);
            CalculateHistogramFromPixels(pixels, width, height, stride, red, green, blue);

            Assert::IsTrue(red == expectedRed, L"Red histogram does not match expected values.");
            Assert::IsTrue(green == expectedGreen, L"Green histogram does not match expected values.");
            Assert::IsTrue(blue == expectedBlue, L"Blue histogram does not match expected values.");
        }


	};
}
