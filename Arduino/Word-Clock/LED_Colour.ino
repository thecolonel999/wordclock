/*
 *  Neopixel LED colour functions
 * 
 * 
 *  Author: Josef Schneider
 *  Licence: http://creativecommons.org/licenses/by/3.0/
 *
 *  Description:
 *    Alas the neopixels are not perfect in terms of colour and brightness.
 *  The functions in this file try to rectify this as much as possible.
 *  
 */

#include <Adafruit_NeoPixel.h>
#include <avr/pgmspace.h>

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t wheel_spectrum(byte WheelPos) {
	uint32_t colour;

	if(WheelPos < 85) {
		colour = Adafruit_NeoPixel::Color(255 - WheelPos * 3, WheelPos * 3, 0);
	} else if(WheelPos < 170) {
		WheelPos -= 85;
		colour = Adafruit_NeoPixel::Color(0, 255 - WheelPos * 3, WheelPos * 3);
	} else {
		WheelPos -= 170;
		colour = Adafruit_NeoPixel::Color(WheelPos * 3, 0, 255 - WheelPos * 3);
	}

	return colour;
}

// Linear brightness curve from http://rgb-123.com/ws2812-color-output/
const uint8_t linear_brightness_curve[256] PROGMEM = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 
	1, 1, 1, 1, 1, 2, 2, 2,
	2, 2, 2, 3, 3, 3, 3, 3, 
	4, 4, 4, 4, 5, 5, 5, 5,
	6, 6, 6, 7, 7, 7, 8, 8, 
	8, 9, 9, 9, 10, 10, 11, 11,
	11, 12, 12, 13, 13, 13, 14, 14, 
	15, 15, 16, 16, 17, 17, 18, 18,
	19, 19, 20, 21, 21, 22, 22, 23, 
	23, 24, 25, 25, 26, 27, 27, 28,
	29, 29, 30, 31, 31, 32, 33, 34, 
	34, 35, 36, 37, 37, 38, 39, 40,
	40, 41, 42, 43, 44, 45, 46, 46, 
	47, 48, 49, 50, 51, 52, 53, 54,
	55, 56, 57, 58, 59, 60, 61, 62, 
	63, 64, 65, 66, 67, 68, 69, 70,
	71, 72, 73, 74, 76, 77, 78, 79, 
	80, 81, 83, 84, 85, 86, 88, 89,
	90, 91, 93, 94, 95, 96, 98, 99,
	100,102,103,104,106,107,109,110,
	111,113,114,116,117,119,120,121,
	123,124,126,128,129,131,132,134,
	135,137,138,140,142,143,145,146,
	148,150,151,153,155,157,158,160,
	162,163,165,167,169,170,172,174,
	176,178,179,181,183,185,187,189,
	191,193,194,196,198,200,202,204,
	206,208,210,212,214,216,218,220,
	222,224,227,229,231,233,235,237,
	239,241,244,246,248,250,252,255
};

inline uint8_t getLinearBrightness(const uint8_t bright) {
	return pgm_read_byte(linear_brightness_curve + bright);
}

// Rainbow colour wheel lookup table
const uint8_t COLOR_WHEEL[] PROGMEM = {
	255,0,0,    252,3,0,    250,5,0,
	247,8,0,    244,11,0,   242,13,0,
	239,16,0,    236,19,0,  234,21,0,
	231,24,0,    228,27,0,  226,29,0,
	223,32,0,    220,35,0,    218,37,0,
	215,40,0,    213,43,0,    210,45,0,
	207,48,0,    205,50,0,    202,53,0,
	199,56,0,    197,58,0,    194,61,0,
	191,64,0,    189,66,0,    186,69,0,
	183,72,0,    181,74,0,    178,77,0,
	175,80,0,    173,82,0,    170,85,0,
	170,88,0,    170,90,0,    170,93,0,
	170,96,0,    170,98,0,    170,101,0,
	170,104,0,    170,106,0,    170,109,0,
	170,112,0,    170,114,0,    170,117,0,
	170,120,0,    170,122,0,    170,125,0,
	170,128,0,    170,130,0,    170,133,0,
	170,135,0,    170,138,0,    170,141,0,
	170,143,0,    170,146,0,    170,149,0,
	170,151,0,    170,154,0,    170,157,0,
	170,159,0,    170,162,0,    170,165,0,
	170,167,0,    170,170,0,    165,173,0,
	159,175,0,    154,178,0,    149,181,0,
	143,183,0,    138,186,0,    133,189,0,
	128,191,0,    122,194,0,    117,197,0,
	112,199,0,    106,202,0,    101,205,0,
	96,207,0,    90,210,0,     85,213,0,
	80,215,0,    74,218,0,     69,220,0,
	64,223,0,    58,226,0,    53,228,0,
	48,231,0,    43,234,0,    37,236,0,
	32,239,0,    27,242,0,    21,244,0,
	16,247,0,    11,250,0,    5,252,0,
	0,255,0,    0,252,3,    0,250,5,
	0,247,8,    0,244,11,    0,242,13,
	0,239,16,    0,236,19,    0,234,21,
	0,231,24,    0,228,27,    0,226,29,
	0,223,32,    0,220,35,    0,218,37,
	0,215,40,    0,213,43,    0,210,45,
	0,207,48,    0,205,50,    0,202,53,
	0,199,56,    0,197,58,    0,194,61,
	0,191,64,    0,189,66,    0,186,69,
	0,183,72,    0,181,74,    0,178,77,
	0,175,80,    0,173,82,    0,170,85,
	0,165,90,    0,159,96,    0,154,101,
	0,149,106,    0,143,112,    0,138,117,
	0,133,122,    0,128,128,    0,122,133,
	0,117,138,    0,112,143,    0,106,149,
	0,101,154,    0,96,159,    0,90,165,
	0,85,170,    0,80,175,    0,74,181,
	0,69,186,    0,64,191,    0,58,197,
	0,53,202,    0,48,207,    0,43,213,
	0,37,218,    0,32,223,    0,27,228,
	0,21,234,    0,16,239,    0,11,244,
	0,5,250,    0,0,255,    3,0,255,
	5,0,252,    8,0,250,    11,0,247,
	13,0,244,    16,0,242,    19,0,239,
	21,0,236,    24,0,234,    27,0,231,
	30,0,228,    32,0,225,    35,0,223,
	38,0,220,    40,0,217,    43,0,215,
	46,0,212,    48,0,209,    51,0,207,
	54,0,204,    56,0,201,    59,0,199,
	62,0,196,    64,0,193,    67,0,191,
	70,0,188,    72,0,185,    75,0,183,
	78,0,180,    81,0,177,    83,0,174,
	86,0,172,    89,0,169,    91,0,166,
	94,0,164,    97,0,161,    99,0,158,
	102,0,156,    105,0,153,    107,0,150,
	110,0,148,    113,0,145,    115,0,142,
	118,0,140,    121,0,137,    123,0,134,
	126,0,132,    129,0,129,    132,0,126,
	134,0,123,    137,0,121,    140,0,118,
	142,0,115,    145,0,113,    148,0,110,
	150,0,107,    153,0,105,    156,0,102,
	158,0,99,    161,0,97,    164,0,94,
	166,0,91,    169,0,89,    172,0,86,
	174,0,83,    177,0,81,    180,0,78,
	183,0,75,    185,0,72,    188,0,70,
	191,0,67,    193,0,64,    196,0,62,
	199,0,59,    201,0,56,    204,0,54,
	207,0,51,    209,0,48,    212,0,46,
	215,0,43,    217,0,40,    220,0,38,
	223,0,35,    225,0,32,    228,0,30,
	231,0,27,    234,0,24,    236,0,21,
	239,0,19,    242,0,16,    244,0,13,
	247,0,11,    250,0,8,    252,0,5,
	255,0,3
};

uint32_t wheel_rainbow(byte WheelPos) {
	uint32_t colour;

	uint8_t r = pgm_read_byte(COLOR_WHEEL + 3 * WheelPos + 0);
	uint8_t g = pgm_read_byte(COLOR_WHEEL + 3 * WheelPos + 1);
	uint8_t b = pgm_read_byte(COLOR_WHEEL + 3 * WheelPos + 2);
	colour = Adafruit_NeoPixel::Color(r, g, b);
	return colour;
}

