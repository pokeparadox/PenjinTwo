#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/mman.h>

#include "flush_uppermem_cache.h"

int mmuhack(void)
{
	int mmufd;
	system("/sbin/rmmod mmuhack");
	system("/sbin/insmod mmuhack.o");
	mmufd = open("/dev/mmuhack", O_RDWR);
	if(mmufd < 0) return 0;

	close(mmufd);
	return 1;
}

int mmuunhack(void)
{
	system("/sbin/rmmod mmuhack");
	return 1;
}

void benchmark(void *memptr)
{
    int starttime = time (NULL);
    int a,b,c,d;
    volatile unsigned int *pp = (unsigned int *) memptr;

    while (starttime == time (NULL));

    printf ("read test @ %p\n", memptr);
    for (d = 0; d < 3; d ++)
    {
        starttime = time (NULL);
        b = 0;
        c = 0;
        while (starttime == time (NULL))
        {
            for (a = 0; a < 20000; a ++)
            {
                b += pp[a];
            }
            c ++;
        }
        printf ("Count is %d. %dMB/sec\n",  c, (c * 20000)/1024/1024);
    }

    printf ("write test\n");
    for (d = 0; d < 3; d ++)
    {
        starttime = time (NULL);
        b = 0;
        c = 0;
        while (starttime == time (NULL))
        {
            for (a = 0; a < 20000; a ++)
            {
                pp[a] = 0x37014206;
            }
            c ++;
        }
        printf ("Count is %d. %dMB/sec\n",  c, (c * 20000)/1024/1024);
    }

    printf  ("combined test (read, write back)\n");
    for (d = 0; d < 3; d ++)
    {
        starttime = time (NULL);
        b = 0;
        c = 0;
        while (starttime == time (NULL))
        {
            for (a = 0; a < 20000; a ++)
            {
                pp[a] += 0x55017601;
            }
            c ++;
        }
        printf ("Count is %d. %dMB/sec\n",  c, (c * 20000)/1024/1024);
    }

    printf ("test complete\n");
}


#define SIZE 65536*4

int main( int argc, char* argv[] )
{
	int ret;
	int memfd = open("/dev/mem", O_RDWR);
	if(memfd < 0) return 1;

	void *hacked_buf = mmap((void *)0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, 0x02000000);

	ret = mmuhack();
	if (!ret)
	{
		printf("mmuhack failed!\n");
		munmap(hacked_buf, SIZE);
		close(memfd);
		return 2;
	}

	void *normal_buf = mmap((void *)0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, 0x02100000);
	void *secbuf = malloc(SIZE);

	memset (hacked_buf, 0x55, SIZE);
	memset (normal_buf, 0x55, SIZE);
	memset (secbuf, 0x55, SIZE);

	printf("mmaped 0x02000000 hacked buffer @ VA: %p\n\n", hacked_buf);
	benchmark (hacked_buf);
	printf("\nmmaped 0x02100000 not hacked buffer @ VA: %p\n\n", normal_buf);
	benchmark (normal_buf);
	printf("\nmalloc'd buffer @ VA: %p\n\n", secbuf);
	benchmark (secbuf);

	/* example of flushing cache. Normally this is done just before flipping the buffer */
	flush_uppermem_cache(hacked_buf, (char *)hacked_buf + 320*240, 0);

	printf ("\nClosing files...\n");
	mmuunhack();
	munmap(hacked_buf, SIZE);
	munmap(normal_buf, SIZE);
	printf("free\n");
	free(secbuf);
	printf("close\n");
	close(memfd);
	printf ("Exiting...\n");

	return 0;
}

