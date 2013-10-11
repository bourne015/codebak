#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int fd_fb;
struct fb_var_screeninfo var;	/* Current var */
struct fb_fix_screeninfo fix;	/* Current fix */
int screen_size;
unsigned char *fbmem;
unsigned int line_width;
unsigned int pixel_width;

int fd_hzk16;
struct stat hzk_stat;
unsigned char *hzkmem;



/* color : 0x00RRGGBB */
void lcd_put_pixel(int x, int y, unsigned int color)
{
	unsigned char *pen_8 = fbmem+y*line_width+x*pixel_width;
	unsigned int *pen_32;	
	unsigned int red, green, blue;	

	pen_32 = (unsigned int *)pen_8;
	*pen_32 = color;
}

void lcd_put_chinese(int x, int y, unsigned char *str)
{
	unsigned int area  = str[0] - 0xA1;
	unsigned int where = str[1] - 0xA1;
	unsigned char *dots = hzkmem + (area * 94 + where)*32;
	unsigned char byte;

	int i, j, b;
	for (i = 0; i < 16; i++)
		for (j = 0; j < 2; j++) {
			byte = dots[i*2 + j];
			for (b = 7; b >=0; b--) {
				if (byte & (1<<b))
					lcd_put_pixel(x+j*8+7-b, y+i, 0xffffff);
				
			}
		}
}

int main(int argc, char **argv)
{
	unsigned char str[] = "жа";

	fd_fb = open("/dev/fb0", O_RDWR);
	if (fd_fb < 0) {
		printf("can't open /dev/fb0\n");
		return -1;
	}

	if (ioctl(fd_fb, FBIOGET_VSCREENINFO, &var)) {
		printf("can't get var\n");
		return -1;
	}

	if (ioctl(fd_fb, FBIOGET_FSCREENINFO, &fix))
	{
		printf("can't get fix\n");
		return -1;
	}

	line_width  = var.xres * var.bits_per_pixel / 8;
	pixel_width = var.bits_per_pixel / 8;
	screen_size = var.xres * var.yres * var.bits_per_pixel / 8;
	fbmem = (unsigned char *)mmap(NULL , screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);
	if (fbmem == (unsigned char *)-1)
	{
		printf("can't mmap\n");
		return -1;
	}

	fd_hzk16 = open("HZK16", O_RDONLY);
	if (fd_hzk16 < 0)
	{
		printf("can't open HZK16\n");
		return -1;
	}
	if(fstat(fd_hzk16, &hzk_stat))
	{
		printf("can't get fstat\n");
		return -1;
	}
	hzkmem = (unsigned char *)mmap(NULL , hzk_stat.st_size, PROT_READ, MAP_SHARED, fd_hzk16, 0);
	if (hzkmem == (unsigned char *)-1)
	{
		printf("can't mmap for hzk16\n");
		return -1;
	}

	memset(fbmem, 0, screen_size);

	printf("chinese code: %02x %02x\n", str[0], str[1]);
	lcd_put_chinese(var.xres/2 + 8,  var.yres/2, str);

	return 0;	
}

