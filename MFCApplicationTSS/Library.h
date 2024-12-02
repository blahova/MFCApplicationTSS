#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <Windows.h> 

void CalculateHistogramFromPixels(const BYTE* pix, int width, int height, int stride,
	std::vector<int>& red, std::vector<int>& green,std::vector<int>& blue)
{
	red.assign(256, 0);
	green.assign(256, 0);
	blue.assign(256, 0);

	for (int y = 0; y < height; ++y)
	{
		const BYTE* row = pix + y * stride;
		for (int x = 0; x < width; ++x)
		{
			BYTE B = row[x * 4];
			BYTE G = row[x * 4 + 1];
			BYTE R = row[x * 4 + 2];

			red[R]++;
			green[G]++;
			blue[B]++;
		}
	}
}

#endif // LIBRARY_H
