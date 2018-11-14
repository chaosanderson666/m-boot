#include "mboot.h"
#include "lcd.h"
#include "S3C2440addr.h"

unsigned short LCD_BUFFER[LCD_YSIZE_TFT][LCD_XSIZE_TFT];

void lcd_init_reg(void)
{
	rGPCUP  = 0x00000000;
	rGPCCON = 0xaaaa02a9; 

	//    rGPDUP=0xffffffff; // Disable Pull-up register
	rGPDUP  = 0x00000000;
	rGPDCON = 0xaaaaaaaa; //Initialize VD[15:8]

	rLCDCON1 = (CLKVAL_TFT << 8)|(MVAL_USED << 7)|(3 <<5 )|(12 << 1)|0;
	// TFT LCD panel,16bpp TFT,ENVID=off
	rLCDCON2 = (VBPD << 24)|(LINEVAL_TFT << 14)|(VFPD << 6)|(VSPW);
	rLCDCON3 = (HBPD << 19)|(HOZVAL_TFT << 8)|(HFPD);
	rLCDCON4 = (MVAL << 8)|(HSPW);
	rLCDCON5 = (1 << 11) | (0 << 10) | (1 << 9) | (1 << 8) | (0 << 7) | (0 << 6)
		| (1 << 3)  |(BSWP << 1) | (HWSWP);
	//5:6:5 VCLK posedge BSWP=0,HWSWP=1;

	rLCDSADDR1 = (((U32)LCD_BUFFER>>22)<<21)|M5D((U32)LCD_BUFFER>>1);
	rLCDSADDR2 = M5D( ((U32)LCD_BUFFER+(SCR_XSIZE_TFT * LCD_YSIZE_TFT * 2)) >> 1 );
	rLCDSADDR3 = (((SCR_XSIZE_TFT - LCD_XSIZE_TFT) / 1) << 11)|(LCD_XSIZE_TFT / 1);
	rLCDINTMSK |= (3);       // MASK LCD Sub Interrupt
	rTCONSEL   &= (~7) ;     // Disable LPC3480
	rTPAL=0;                 // Disable Temp Palette
}

static void lcd_power_enable(int invpwren,int pwren)
{
	//GPG4 is setted as LCD_PWREN
	rGPGUP  = rGPGUP & ((~(1 << 4))|(1 << 4)); // Pull-up disable
	rGPGCON = rGPGCON & ((~(3 << 8))|(3 << 8)); //GPG4=LCD_PWREN
	rGPGDAT = rGPGDAT|(1 << 4);
	//Enable LCD POWER ENABLE Function
	rLCDCON5 = rLCDCON5 & ((~(1 << 3))|(pwren << 3));   // PWREN
	rLCDCON5 = rLCDCON5 & ((~(1 << 5))|(invpwren << 5));   // INVPWREN
}

void lcd_clear( U16 c)
{
	U16 x, y;
	for( y = 0 ; y < SCR_YSIZE_TFT ; y++ ){
		for( x = 0 ; x < SCR_XSIZE_TFT ; x++ ){
			LCD_BUFFER[y][x] = c ;
		}
	}
}

void put_pixel(U32 x,U32 y, U16 c )
{
	if ( (x < SCR_XSIZE_TFT) && (y < SCR_YSIZE_TFT) )
		LCD_BUFFER[(y)][(x)] = c;
}

extern unsigned char __VGA[];
void lcd_printf(U16 x, U16 y,U16 back_color,U16 char_color,S8 *p_str)
{
	U16 i,j;
	U8 *pZK, mask, buf;

	while(*p_str != 0 ){
		switch(*p_str){
			case '\n' :{break;}	
			default:{
						pZK = &__VGA[(*p_str)*16];
						for(i = 0; i < 16; i++){
							mask = 0x80;
							buf = pZK[i];
							for(j = 0; j < 8; j++){
								if( buf & mask ){
									put_pixel(x+j,y+i,char_color);
								}else{
									put_pixel(x+j,y+i,back_color);
								}
								mask = mask >> 1;
							}
						}
						x += 8;
						p_str++;
					}
		}
	}
}
static void lcd_envidonoff(int onoff)
{
	if(onoff == 1){
		rLCDCON1 |= 1;
	}
	else{
		rLCDCON1 &= 0x3fffe;
	}
}

void lcd_init(void)
{
	lcd_init_reg();
	lcd_power_enable(0, 1);
	lcd_envidonoff(1);
}
