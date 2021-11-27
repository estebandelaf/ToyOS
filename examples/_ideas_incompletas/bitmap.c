#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bitmap {
	void *map;
	int bits;
	int bytes;
};

struct bitmap *bitmap_make (int bits);
void bitmap_setall (struct bitmap *bitmap, short int value);
void bitmap_set (struct bitmap *bitmap, int bit, short int value);
short int bitmap_get (struct bitmap *bitmap, int bit);
void bitmap_destroy (struct bitmap *bitmap);

struct bitmap *bitmap_make (int bits)
{
	int bytes = (bits / 8) + (bits % 8 ? 1 : 0);
	struct bitmap *bitmap = malloc(sizeof(struct bitmap));
	bitmap->map = malloc(bytes);
	bitmap->bits = bits;
	bitmap->bytes = bytes;
	bitmap_setall (bitmap, 0);
	return bitmap;
}

void bitmap_setall (struct bitmap *bitmap, short int value)
{
	memset (bitmap->map, value, bitmap->bytes);
}

void bitmap_set (struct bitmap *bitmap, int bit, short int value)
{

}

short int bitmap_get (struct bitmap *bitmap, int bit)
{
	/*return (bitmap->map >> (bitmap->bits - 1 - bit));*/
	short int *a = malloc(10);
	*a = 7;
	printf ("bit = %d\n", a >> 2);
	/*printf ("%lu\n", sizeof(short int));*/
	return a;
}

void bitmap_destroy (struct bitmap *bitmap)
{
	free (bitmap->map);
	free (bitmap);
}

int main (int argc, char *argv[])
{
	int i;
	struct bitmap *bitmap = bitmap_make (4);
	bitmap_set (bitmap, 0, 1);
	bitmap_set (bitmap, 2, 1);
	for (i=0; i<4; ++i)
		printf ("bit[%d] = %d\n", i, bitmap_get(bitmap, i));
	bitmap_destroy (bitmap);
	return 0;
}
