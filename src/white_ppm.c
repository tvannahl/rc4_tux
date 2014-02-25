#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* too lazy for parsing ppm header */
#define HEADER_LEN 4
#define WIDTH 196
#define HEIGHT 216

enum mode { NONE, TOP, BOTTOM };

void write_img(FILE *input, FILE *output, int white)
{
	if (white == 0)
	{
		fputc(fgetc(input), output);
		fputc(fgetc(input), output);
		fputc(fgetc(input), output);
	}
	else
	{
		fgetc(input);
		fputc(255, output);
		fgetc(input);
		fputc(255, output);
		fgetc(input);
		fputc(255, output);
	}
}

void whitening(enum mode m, FILE *fp_in, FILE *fp_out, FILE *hdr)
{
	char *puf;
	int head_len = 3;
	int width, height, c_range, retval, i;
	
	puf = malloc(255);

	/* copy header */
	for(i=0; i < HEADER_LEN; i++)
	{
		fgets (puf, 255, fp_in);
		fputs (puf, hdr);
	}

	free(puf);

	/* parsing image data */
	for(i=0; i< 3*HEIGHT*WIDTH ; i+=3)
	{
		if ((WIDTH*HEIGHT*3)/2 < i)
		{
			write_img(fp_in, fp_out, m == TOP);
		}
		else
		{
			write_img(fp_in, fp_out, m == BOTTOM);
		}
	}
}

void print_help(void)
{
    printf ("Usage: white_ppm [-t|-b|-h] input output\n");
    exit (1);
}

int main(int argc, char **argv)
{
    FILE *fp_in, *fp_out, *fp_hdr;
    int c;
    enum mode m = NONE;
    while ((c = getopt (argc, argv, "tbh")) != -1)
    {
        switch(c)
        {
            case 't':
                if (m != NONE)
                {
                    printf("You can choose only one mode\n");
                    return 1;
                }
                m = TOP;
                break;
            case 'b':
                if (m != NONE)
                {
                    printf("You can choose only one mode\n");
                    return 1;
                }
                m = BOTTOM;
                break;
            case 'h':
                print_help();
                break;
            default:
                print_help();
        }
    }
    if (argc != 5)
    {
        print_help();
    }
    fp_in = fopen(argv[2], "r");
    fp_out = fopen(argv[3], "w");
    fp_hdr = fopen(argv[4], "w");

    whitening (m, fp_in, fp_out, fp_hdr);

    fclose (fp_in);
    fclose (fp_out);
    fclose (fp_hdr);
    return 0;
}
