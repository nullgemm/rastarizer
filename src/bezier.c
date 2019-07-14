#include "rastarizer.h"
#include "math32.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

void ras_precision_bezier_cubic(
	struct ras_buf ras,
	int32_t p0x,
	int32_t p0y,
	int32_t p1x,
	int32_t p1y,
	int32_t p2x,
	int32_t p2y,
	int32_t p3x,
	int32_t p3y)
{
    int32_t ax = 3 * (p1x - p2x) + p3x - p0x;
    int32_t ay = 3 * (p1y - p2y) + p3y - p0y;

    int32_t bx = 3 * (p0x + p2x - (2 * p1x));
    int32_t by = 3 * (p0y + p2y - (2 * p1y));

    int32_t cx = 3 * (p1x - p0x);
    int32_t cy = 3 * (p1y - p0y);

    int32_t dx = p0x;
    int32_t dy = p0y;

    int32_t pointX = dx;
    int32_t pointY = dy;

	int32_t xpxl_old = pointX;
	int32_t ypxl_old = pointY;

    int32_t steps = 20 - 1;
	int32_t steps2 = steps * steps;
	int32_t steps3 = steps2 * steps;

    int32_t firstFDX = (ax / steps3) + (bx / steps2) + (cx / steps);
    int32_t firstFDY = (ay / steps3) + (by / steps2) + (cy / steps);

    int32_t secondFDX = ((6 * ax) / steps3) + ((2 * bx) / steps2);
    int32_t secondFDY = ((6 * ay) / steps3) + ((2 * by) / steps2);

    int32_t thirdFDX = (6 * ax) / steps3;
    int32_t thirdFDY = (6 * ay) / steps3;    

    for (int32_t i = 0; i < steps; ++i)
	{
        pointX += firstFDX;
        pointY += firstFDY;

        firstFDX += secondFDX;
        firstFDY += secondFDY;

        secondFDX += thirdFDX;
        secondFDY += thirdFDY;

		ras_precision_line(ras, xpxl_old, ypxl_old, pointX, pointY);

		xpxl_old = pointX;
		ypxl_old = pointY;
    }
}

void ras_bezier_cubic(
	struct ras_buf ras,
	int32_t p0x,
	int32_t p0y,
	int32_t p1x,
	int32_t p1y,
	int32_t p2x,
	int32_t p2y,
	int32_t p3x,
	int32_t p3y)
{
	ras_precision_bezier_cubic(
		ras,
		p0x << 8,
		p0y << 8,
		p1x << 8,
		p1y << 8,
		p2x << 8,
		p2y << 8,
		p3x << 8,
		p3y << 8);
}
