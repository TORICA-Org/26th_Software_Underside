#pragma once

void init_NeoPixel();


// 色の定数定義（Lightup_NeoPixel()用）
#define RED 0
#define GREEN 1
#define BLUE 2

void Lightup_NeoPixel(int color);

void NeoPixel_off();