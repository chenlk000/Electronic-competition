#ifndef DSP_FILTER
#define DSP_FILTER

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "cmsis_os.h"
#include "arm_math.h"
#include "log.h"

#define SINWAVE_SAMPLE 512

const short sin_wave_12ADC[SINWAVE_SAMPLE] = {
25,
50,
75,
100 ,
126 ,
151 ,
176 ,
201 ,
226 ,
251 ,
276 ,
301 ,
325 ,
350 ,
375 ,
400 ,
424 ,
449 ,
473 ,
498 ,
522 ,
546 ,
570 ,
595 ,
619 ,
642 ,
666 ,
690 ,
714 ,
737 ,
760 ,
784 ,
807 ,
830 ,
853 ,
876 ,
898 ,
921 ,
943 ,
965 ,
988 ,
1009,
1031,
1053,
1074,
1096,
1117,
1138,
1159,
1179,
1200,
1220,
1240,
1260,
1280,
1299,
1319,
1338,
1357,
1375,
1394,
1412,
1430,
1448,
1466,
1483,
1500,
1517,
1534,
1551,
1567,
1583,
1599,
1615,
1630,
1645,
1660,
1674,
1689,
1703,
1717,
1730,
1744,
1757,
1769,
1782,
1794,
1806,
1818,
1829,
1840,
1851,
1862,
1872,
1882,
1892,
1902,
1911,
1920,
1928,
1937,
1945,
1952,
1960,
1967,
1974,
1980,
1987,
1993,
1998,
2004,
2009,
2013,
2018,
2022,
2026,
2029,
2033,
2036,
2038,
2040,
2042,
2044,
2046,
2047,
2047,
2048,
2048,
2048,
2047,
2047,
2046,
2044,
2042,
2040,
2038,
2036,
2033,
2029,
2026,
2022,
2018,
2013,
2009,
2004,
1998,
1993,
1987,
1980,
1974,
1967,
1960,
1952,
1945,
1937,
1928,
1920,
1911,
1902,
1892,
1882,
1872,
1862,
1851,
1840,
1829,
1818,
1806,
1794,
1782,
1769,
1757,
1744,
1730,
1717,
1703,
1689,
1674,
1660,
1645,
1630,
1615,
1599,
1583,
1567,
1551,
1534,
1517,
1500,
1483,
1466,
1448,
1430,
1412,
1394,
1375,
1357,
1338,
1319,
1299,
1280,
1260,
1240,
1220,
1200,
1179,
1159,
1138,
1117,
1096,
1074,
1053,
1031,
1009,
988 ,
965 ,
943 ,
921 ,
898 ,
876 ,
853 ,
830 ,
807 ,
784 ,
760 ,
737 ,
714 ,
690 ,
666 ,
642 ,
619 ,
595 ,
570 ,
546 ,
522 ,
498 ,
473 ,
449 ,
424 ,
400 ,
375 ,
350 ,
325 ,
301 ,
276 ,
251 ,
226 ,
201 ,
176 ,
151 ,
126 ,
100 ,
75  ,
50  ,
25  ,
0   ,
-25 ,
-50 ,
-75 ,
-100,
-126,
-151,
-176,
-201,
-226,
-251,
-276,
-301,
-325,
-350,
-375,
-400,
-424,
-449,
-473,
-498,
-522,
-546,
-570,
-595,
-619,
-642,
-666,
-690,
-714,
-737,
-760,
-784,
-807,
-830,
-853,
-876,
-898,
-921,
-943,
-965,
-988,
-1009,
-1031,
-1053,
-1074,
-1096,
-1117,
-1138,
-1159,
-1179,
-1200,
-1220,
-1240,
-1260,
-1280,
-1299,
-1319,
-1338,
-1357,
-1375,
-1394,
-1412,
-1430,
-1448,
-1466,
-1483,
-1500,
-1517,
-1534,
-1551,
-1567,
-1583,
-1599,
-1615,
-1630,
-1645,
-1660,
-1674,
-1689,
-1703,
-1717,
-1730,
-1744,
-1757,
-1769,
-1782,
-1794,
-1806,
-1818,
-1829,
-1840,
-1851,
-1862,
-1872,
-1882,
-1892,
-1902,
-1911,
-1920,
-1928,
-1937,
-1945,
-1952,
-1960,
-1967,
-1974,
-1980,
-1987,
-1993,
-1998,
-2004,
-2009,
-2013,
-2018,
-2022,
-2026,
-2029,
-2033,
-2036,
-2038,
-2040,
-2042,
-2044,
-2046,
-2047,
-2047,
-2048,
-2048,
-2048,
-2047,
-2047,
-2046,
-2044,
-2042,
-2040,
-2038,
-2036,
-2033,
-2029,
-2026,
-2022,
-2018,
-2013,
-2009,
-2004,
-1998,
-1993,
-1987,
-1980,
-1974,
-1967,
-1960,
-1952,
-1945,
-1937,
-1928,
-1920,
-1911,
-1902,
-1892,
-1882,
-1872,
-1862,
-1851,
-1840,
-1829,
-1818,
-1806,
-1794,
-1782,
-1769,
-1757,
-1744,
-1730,
-1717,
-1703,
-1689,
-1674,
-1660,
-1645,
-1630,
-1615,
-1599,
-1583,
-1567,
-1551,
-1534,
-1517,
-1500,
-1483,
-1466,
-1448,
-1430,
-1412,
-1394,
-1375,
-1357,
-1338,
-1319,
-1299,
-1280,
-1260,
-1240,
-1220,
-1200,
-1179,
-1159,
-1138,
-1117,
-1096,
-1074,
-1053,
-1031,
-1009,
-988,
-965,
-943,
-921,
-898,
-876,
-853,
-830,
-807,
-784,
-760,
-737,
-714,
-690,
-666,
-642,
-619,
-595,
-570,
-546,
-522,
-498,
-473,
-449,
-424,
-400,
-375,
-350,
-325,
-301,
-276,
-251,
-226,
-201,
-176,
-151,
-126,
-100,
-75 ,
-50 ,
-25 ,
0   
};
//#define 
int dsp_print2(float32_t *data1,float32_t *data2);
int dsp_print(float32_t *data);//float32_t *data
int dsp_test(void);
int dsp_init(void);

int dsp_multi_frequency(void);
int dsp_ave(uint16_t * buffer);
int dsp_filt();
#define FS 100000.0f
#define F0  20000.0f

#endif


