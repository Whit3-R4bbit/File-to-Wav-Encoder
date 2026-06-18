#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void writeWavHeader(uint32_t dataSize, FILE *outputFile){

    // RIFF HEADER
    uint32_t chunkSize = 36 + dataSize;

    fwrite("RIFF", 1, 4, outputFile); // Chunk ID
    fwrite(&chunkSize, sizeof(uint32_t), 1, outputFile); // Size of file minus chunk ID and chunk size
    fwrite("WAVE", 1, 4, outputFile); // Format

    // fmt SUBCHUNK
    uint32_t Subchunk1Size = 16;
    uint16_t audioFormat = 1;
    uint16_t numChannels = 1;
    uint32_t sampleRate = 44100;
    uint32_t byteRate = sampleRate * numChannels * 2;
    uint16_t blockAlign = numChannels * 2;
    uint16_t bitsPerSample = numChannels * 2;

    fwrite("fmt ", 1, 4, outputFile); // fmt Subchunk ID
    fwrite(&Subchunk1Size, sizeof(uint32_t), 1, outputFile); // Size of subchunk minus subchunk ID and subchunk size
    fwrite(&audioFormat, sizeof(uint16_t), 1, outputFile);
    fwrite(&numChannels, sizeof(uint16_t), 1, outputFile);
    fwrite(&sampleRate, sizeof(uint32_t), 1, outputFile);
    fwrite(&byteRate, sizeof(uint32_t), 1, outputFile);
    fwrite(&blockAlign, sizeof(uint16_t), 1, outputFile);
    fwrite(&bitsPerSample, sizeof(uint16_t), 1, outputFile);

    // data SUBCHUNK
    fwrite("data", 1, 4, outputFile);
    fwrite(&dataSize, sizeof(uint32_t), 1, outputFile);
}

int main(){
    FILE *outputFile = fopen("output.bin", "wb");
    writeWavHeader(36, outputFile);
    fclose(outputFile);
}