#include <stdint.h> // uint8_t, uint16_t, uint32_t
#include <stdio.h> // FILE, EOF, NULL, fopen, fclose, fwrite
#include "rastarizer.h"

static inline uint32_t swap_u32(uint32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0x00FF00FF);
    return (val << 16) | (val >> 16);
}

uint8_t farbfeld(
	const char* file,
	uint32_t width,
	uint32_t height,
	uint8_t* rgba)
{
	FILE* fp = fopen(file, "w");

	if (fp == NULL)
	{
		return 0;
	}

	uint32_t size = ((uint32_t) 4) * width * height;
	int8_t ok = fwrite("farbfeld", 8, 1, fp);

	if (ok == 0)
	{
		return 0;
	}

	// remove for big-endian
	width = swap_u32(width);
	ok = fwrite(&width, 4, 1, fp);

	if (ok == 0)
	{
		return 0;
	}

	// remove for big-endian
	height = swap_u32(height);
	ok = fwrite(&height, 4, 1, fp);

	if (ok == 0)
	{
		return 0;
	}

	uint16_t value;

	for (uint32_t i = 0; i < size; ++i)
	{
		// leverages endianness mismatch to avoid byte swapping
		// replace by the following line for big-endian
		// value = ((uint16_t) rgba[i]) << 8;
		value = rgba[i];
		ok = fwrite(&value, 2, 1, fp);

		if (ok == 0)
		{
			return 0;
		}
	}

	ok = fclose(fp);

	return ok != EOF;
}

int main(void)
{
	uint8_t rgba[400*400*4];
	struct ras_buf ras = {rgba, 400, 400};

	for (uint32_t i = 0; i < 400*400*4; ++i)
	{
		rgba[i] = 0xFF;
	}

	// test all circles radi up to 10 pixels
#if 1
	ras_disk(ras, 80, 50, 40);
	ras_disk(ras, 10, 20, 10);
	ras_disk(ras, 10, 40, 9);
	ras_disk(ras, 10, 60, 8);
	ras_disk(ras, 10, 80, 7);
	ras_disk(ras, 10, 100, 6);
	ras_disk(ras, 10, 120, 5);
	ras_disk(ras, 10, 140, 4);
	ras_disk(ras, 10, 160, 3);
	ras_disk(ras, 10, 180, 2);
	ras_disk(ras, 10, 200, 1);
#endif

#if 1
	ras_disk2(ras, 320, 50, 40);
	ras_disk2(ras, 390, 20, 10);
	ras_disk2(ras, 390, 40, 9);
	ras_disk2(ras, 390, 60, 8);
	ras_disk2(ras, 390, 80, 7);
	ras_disk2(ras, 390, 100, 6);
	ras_disk2(ras, 390, 120, 5);
	ras_disk2(ras, 390, 140, 4);
	ras_disk2(ras, 390, 160, 3);
	ras_disk2(ras, 390, 180, 2);
	ras_disk2(ras, 390, 200, 1);
#endif

#if 0
	ras_rounded_rectangle(ras, 200, 300, 200, 350, 17);
#endif

#if 1
	ras_ring(ras, 110, 300, 100, 90);
	ras_ring(ras, 110, 300, 70, 69);
	ras_ring(ras, 110, 300, 65, 55);
#endif

#if 1
	ras_ring2(ras, 290, 300, 100, 90);
	ras_ring2(ras, 290, 300, 70, 69);
	ras_ring2(ras, 290, 300, 65, 55);
#endif

#if 1
	ras_ring3(ras, 200, 145, 100, 90);
	ras_ring3(ras, 200, 145, 70, 69);
	ras_ring3(ras, 200, 145, 65, 55);
#endif
	
	// lines
#if 1
	ras_line(ras, 100, 100, 200, 75);
	ras_line(ras, 100, 100, 125, 0);
	ras_line(ras, 1, 1, 10, 1);
	ras_line(ras, 1, 3, 1, 13);
#endif

	// plot gamma functions to check everything is right
#if 1
	for (uint32_t i = 0; i < 256; ++i)
	{
		pixel_set(ras, i, 399 - gamma_22(i), 0x00, 0x00, 0x00, 0xFF);
		pixel_set(ras, i, 399 - r_gamma_22(i), 0x00, 0x00, 0x00, 0xFF);
	}
#endif

	// cubic bezier
#if 1
	ras_bezier_cubic(ras, 300, 399, 310, 300, 390, 280, 380, 399);
	ras_bezier_cubic(ras, 300, 399, 390, 300, 310, 280, 380, 399);
	ras_bezier_cubic(ras, 350, 399, 390, 300, 310, 280, 360, 399);

	ras_bezier_cubic(ras, 10, 399, 20, 10, 379, 10, 389, 399);
	ras_bezier_cubic(ras, 10, 399, 389, 10, 10, 10, 389, 399);
#endif

	// polygon
#if 1
	uint32_t polygon[14] =
	{
		20,	20,
		50,	30,
		70,	40,
		60,	70,
		50,	60,
		10,	40,
		30,	30,
	};

	ras_polygon(ras, polygon, 7);
#endif

	uint8_t ok = farbfeld("test.ff", 400, 400, rgba);

	return (ok == 1) ? 0 : 1;
}
