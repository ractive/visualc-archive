
#include <stdio.h>
#include <stdlib.h>

#define RGBMAX 255
#define HLSMAX 255

#define UNDEFINED (HLSMAX*2/3)

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

void get_HLS(int R, int G, int B, int &H, int &L, int &S) {
	int hue = 0;
	int cMax = 0;
	int cMin = 0;
	int rg = 0, gg = 0, bg = 0;

	int Rdelta = 0, Gdelta = 0, Bdelta = 0;

		
		cMax = max(max(R, G), B);
		cMin = min(min(R, G), B);

		L = ( ((cMax+cMin)*HLSMAX) + RGBMAX )/(2*RGBMAX);

      if (cMax == cMin) {           /* r=g=b --> achromatic case */ 
         S = 0;                     /* saturation */ 
         H = UNDEFINED;             /* hue */ 
      }
      else {                        /* chromatic case */ 
         /* saturation */ 
         if (L <= (HLSMAX/2))
            S = ( ((cMax-cMin)*HLSMAX) + ((cMax+cMin)/2) ) / (cMax+cMin);
         else
            S = ( ((cMax-cMin)*HLSMAX) + ((2*RGBMAX-cMax-cMin)/2) )
               / (2*RGBMAX-cMax-cMin);

			 /* hue */ 
		  Rdelta = ( ((cMax-R)*(HLSMAX/6)) + ((cMax-cMin)/2) ) / (cMax-cMin);
		  Gdelta = ( ((cMax-G)*(HLSMAX/6)) + ((cMax-cMin)/2) ) / (cMax-cMin);
		  Bdelta = ( ((cMax-B)*(HLSMAX/6)) + ((cMax-cMin)/2) ) / (cMax-cMin);

         if (R == cMax)
            H = Bdelta - Gdelta;
         else if (G == cMax)
            H = (HLSMAX/3) + Rdelta - Bdelta;
         else /* B == cMax */ 
            H = ((2*HLSMAX)/3) + Gdelta - Rdelta;

         if (H < 0)
            H += HLSMAX;
         if (H > HLSMAX)
            H -= HLSMAX;
      }
}

int HueToRGB(int n1, int n2, int hue)
{
	/* range check: note values passed add/subtract thirds of range */ 
	if (hue < 0)
		hue += HLSMAX;

	if (hue > HLSMAX)
		hue -= HLSMAX;

	/* return r,g, or b value from this tridrant */ 
	if (hue < (HLSMAX/6))
		return ( n1 + (((n2-n1)*hue+(HLSMAX/12))/(HLSMAX/6)) );
	if (hue < (HLSMAX/2))
		return ( n2 );
	if (hue < ((HLSMAX*2)/3))
		return ( n1 +    (((n2-n1)*(((HLSMAX*2)/3)-hue)+(HLSMAX/12))/(HLSMAX/6)));
	else
		return ( n1 );
}


void get_RGB(int hue, int lum, int sat, int &R, int &G, int &B)
{
	int  Magic1,Magic2;       /* calculated magic numbers (really!) */ 

	if (sat == 0) {            /* achromatic case */ 
		R=G=B=(lum*RGBMAX)/HLSMAX;
		if (hue != UNDEFINED) {
			/* ERROR */ 
		}
	}
	else  {                    /* chromatic case */ 
		/* set up magic numbers */ 
		if (lum <= (HLSMAX/2))
			Magic2 = (lum*(HLSMAX + sat) + (HLSMAX/2))/HLSMAX;
		else
			Magic2 = lum + sat - ((lum*sat) + (HLSMAX/2))/HLSMAX;
		
		Magic1 = 2*lum-Magic2;

		/* get RGB, change units from HLSMAX to RGBMAX */ 
		R = (HueToRGB(Magic1,Magic2,hue+(HLSMAX/3))*RGBMAX + (HLSMAX/2))/HLSMAX;
		G = (HueToRGB(Magic1,Magic2,hue)*RGBMAX + (HLSMAX/2)) / HLSMAX;
		B = (HueToRGB(Magic1,Magic2,hue-(HLSMAX/3))*RGBMAX + (HLSMAX/2))/HLSMAX;
	}
}

void transform(int &r, int &g, int&b) {

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
}

int main(int argc, char* argv[])
{
	int r = 0, g = 0, b = 0;
	int H = 0, L = 0, S = 0;
	int old_B = 0;
	int hl = 0, hu = 0, ll = 0;
	float lum;

	/*FILE * fp = fopen("params.inf", "r");
	if (!fp) {
		return 1;
	}

	fscanf(fp, "%f\n%d\n%d\n%d", &lum, &ll, &hl, &hu);


	fclose(fp);*/
	

	while(scanf("%d %d %d", &r, &g, &b) != -1) {
		//fprintf(stderr, "%d: %d, %d, %d\n", t, r, g, b);

		transform(r, g, b);
		get_HLS(r, g, b, H, L, S);
		old_B = b;
#ifdef _DEBUG
		fprintf(stderr, "H%4d S%4d L%4d R%4d, G%4d, B%4d\n", H, S, L, r, g, b);
#endif
		//if (H > hl && H < hu) {
		if (H > 50 && H < 150) {
			if (argc < 2) {
				lum = 1.5;
			}
			else {
				sscanf(argv[1], "%f", &lum);
			}

			L = (int)(L * lum);
			S = (int)(S * lum);
			//L = min(L, ll);
			L = min(L, 220);
			S = min(S, 255);
			get_RGB(H, L, S, r, g, b);

			b = old_B;
			transform(r, g, b);
		}

		printf("%d %d %d\n", r, g, b);
	}

	
	return 0;
}

