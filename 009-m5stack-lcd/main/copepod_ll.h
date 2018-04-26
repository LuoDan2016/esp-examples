/*

Copyright (c) 2018 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <stdint.h>
#include "driver/spi_master.h"
#include "framebuffer.h"
#include "ili9341.h"

// #define PLN_HAS_LL_HLINE
// #define PLN_HAS_LL_VLINE

extern spi_device_handle_t g_spi;
extern framebuffer_t g_fb;

void pod_ll_putpixel(uint16_t x1, uint16_t y1, uint16_t color);
void pod_ll_blit(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t *bitmap);
void pod_ll_hline(uint16_t x1, uint16_t y1, uint16_t w, uint16_t color);
void pod_ll_vline(uint16_t x1, uint16_t y1, uint16_t h, uint16_t color);
