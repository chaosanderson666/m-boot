#ifndef _LCD_H_
#define _LCD_H_

#define MVAL		(13)
#define MVAL_USED 	(0)
#define INVVDEN		(1)
#define BSWP		(0)
#define HWSWP		(1)

#define M5D(n) ((n) & 0x1fffff)	/* To get lower 21bits */

#define LCD_XSIZE_TFT 	(480)	
#define LCD_YSIZE_TFT 	(272)

#define SCR_XSIZE_TFT 	(480)	
#define SCR_YSIZE_TFT 	(272)

/* Timing parameter for 4.3' LCD */
#define VBPD 		(2)
#define VFPD 		(4)
#define VSPW 		(8)

#define HBPD 		(10)
#define HFPD 		(19)
#define HSPW 		(30)

#define CLKVAL_TFT 	(4) 	

#define HOZVAL_TFT          (LCD_XSIZE_TFT -1)
#define LINEVAL_TFT         (LCD_YSIZE_TFT -1)

#endif /* _LCD_H_ */
