// GifsicleMT.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

int main(int argc, char* argv[])
{
	int r = 0, g = 0, b = 0;

	while(scanf("%d %d %d", &r, &g, &b) != -1) {

		if (b > 191) {
			b = 255;
		}
		else if (b > 127) {
			b = 170;
		}
		else if (b > 63) {
			b = 85;
		}
		else {
			b = 0;
		}

		if (r > 223) {
			r = 255;
		}
		else if (r > 191) {
			r = 219;
		}
		else if (r > 159) {
			r = 183;
		}
		else if (r > 127) {
			r = 146;
		}
		else if (r > 95) {
			r = 110;
		}
		else if (r > 63) {
			r = 73;
		}
		else if (r > 31) {
			r = 37;
		}
		else {
			r = 0;
		}

		if (g > 223) {
			g = 255;
		}
		else if (g > 191) {
			g = 219;
		}
		else if (g > 159) {
			g = 183;
		}
		else if (g > 127) {
			g = 146;
		}
		else if (g > 95) {
			g = 110;
		}
		else if (g > 63) {
			g = 73;
		}
		else if (g > 31) {
			g = 37;
		}
		else {
			g = 0;
		}

		printf("%d %d %d\n", r, g, b);
	}

	return 0;
}

