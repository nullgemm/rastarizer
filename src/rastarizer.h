#ifndef H_RASTARIZER
#define H_RASTARIZER

#include <stdint.h>

struct ras_buf
{
	uint8_t *buf;
	uint16_t width;
	uint16_t height;
};

uint32_t gamma_22(uint32_t x);
uint32_t r_gamma_22(uint32_t x);

void pixel_blend(
	struct ras_buf ras,
	uint16_t x,
	uint16_t y,
	uint8_t r,
	uint8_t g,
	uint8_t b,
	uint8_t a);

void pixel_set(
	struct ras_buf ras,
	uint16_t x,
	uint16_t y,
	uint8_t r,
	uint8_t g,
	uint8_t b,
	uint8_t a);

void ras_disk(
	struct ras_buf ras,
	uint16_t ox,
	uint16_t oy,
	uint16_t r);

void ras_disk2(
	struct ras_buf ras,
	uint32_t ox,
	uint32_t oy,
	uint32_t r);

void ras_ring(
	struct ras_buf ras,
	uint16_t ox,
	uint16_t oy,
	uint16_t ro,
	uint16_t ri);

void ras_ring2(
	struct ras_buf ras,
	uint32_t ox,
	uint32_t oy,
	uint32_t ro,
	uint32_t ri);

void ras_ring3(
	struct ras_buf ras,
	uint32_t ox,
	uint32_t oy,
	uint32_t ro,
	uint32_t ri);

void ras_rounded_rectangle(
	struct ras_buf ras,
	uint16_t x1,
	uint16_t x2,
	uint16_t y1,
	uint16_t y2,
	uint16_t r);

void ras_bezier_cubic(
	struct ras_buf ras,
	int32_t p0x,
	int32_t p0y,
	int32_t p1x,
	int32_t p1y,
	int32_t p2x,
	int32_t p2y,
	int32_t p3x,
	int32_t p3y);

void ras_line(
	struct ras_buf ras,
	int32_t x1,
	int32_t y1,
	int32_t x2,
	int32_t y2);

void ras_precision_line(
	struct ras_buf ras,
	int32_t x1,
	int32_t y1,
	int32_t x2,
	int32_t y2);

void ras_polygon(
	struct ras_buf ras,
	uint32_t* points,
	uint32_t count);

void ras_precision_polygon(
	struct ras_buf ras,
	uint32_t* points,
	uint32_t count);

#endif
