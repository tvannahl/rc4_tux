#include <stdio.h>

void fxor(FILE *in1, FILE *in2, FILE *fp_out)
{
    int x, y;
    x = fgetc (in1);
    y = fgetc (in2);
    while(x != EOF && y != EOF)
    {
        x = fgetc(in1);
        y = fgetc(in2);
        fputc(x^y, fp_out);
    }
}

int main(int argc, char** args)
{
    FILE *fp1, *fp2, *fp_out;
    if(argc != 4)
    {
        printf("%i Parameter erwartet %i erhalten.\n", 4-1, argc-1);
        return 2;
    }
    fp1 = fopen(args[1], "r");
    fp2 = fopen(args[2], "r");
    fp_out = fopen(args[3], "w");
    if(fp1 == NULL || fp2 == NULL || fp_out == NULL)
    {
        printf("Konnte eine oder beide Dateien nicht öffnen\n");
        return 1;
    }
    fxor(fp1, fp2, fp_out);
    fclose(fp1);
    fclose(fp2);
    fclose(fp_out);
}
