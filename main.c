#include <stdlib.h>
#include <stdio.h>

void writeWavHeader(int dataSize, FILE *outputFile){
    fwrite("RIFF", 1, 4, outputFile);
    fwrite(36 + dataSize, 1, 4, outputFile);
}

int main(){
    FILE *outputFile = fopen("output.bin", "wb");
    writeWavHeader(1, outputFile);
    fclose(outputFile);
}