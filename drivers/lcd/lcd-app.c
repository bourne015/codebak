#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

int main(void)
{
	int fb;
	struct fb_var_screeninfo vinfo;
	unsigned long screensize;
	char *fbp;

	fb = open("/dev/fb0", O_RDWR);
	if (!fb) {
		printf("failed to open fb0\n");
		return -1;
	}
	printf("open fb0 successed\n");

	if (ioctl(fb, FBIOGET_VSCREENINFO, &vinfo)) {
		printf("failed to get vinfo\n");
		return -1;
	}

	printf("%d x %d  %dbpp", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

	screensize = vinfo.xres * vinfo.yres * 4;
	
	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE,
				MAP_SHARED, fb, 0);
	if ((int)fbp == -1) {
		printf("failed to mmap\n");
		return -1;
	}

	munmap(fbp, screensize);
	close(fb);

	return 0;
}
