#include <stdio.h>
#include <limits.h>

typedef int bool;
#define true 1
#define false 0

#pragma pack(push,1)

typedef struct {
  char fileType[2]; // 2 bytes
  int unsigned fileSize; // 4 bytes
  short reserved1; // 2 bytes
  short reserved2; // 2 bytes
  int unsigned dataOffset; // 4 bytes
} FileHeader; // total = 14 bytes

typedef struct {
  FileHeader fileHeader; // 14 bytes
  int unsigned headerSize; // 4 bytes
  int width; // 4 bytes
  int height; // 4 bytes
  short planes; // 2 bytes
  short bitsPerPixel; // 2 bytes
  int unsigned compression; // 4 bytes
  int unsigned bitmapSize; // 4 bytes
  int horizontalRes; // 4 bytes
  int verticalRes; // 4 bytes
  int unsigned numColors; // 4 bytes
  unsigned int importantColors; // 4 bytes
} BitmapHeader; // total = 54 bytes

#pragma pack(pop)

int main(int argc, char *argv[]) {
  printf("hey\n");

  FILE *input, *output;
  // allocate memory to the size in bytes of struct BitmapHeader and FileHeader
  BitmapHeader *bitmapHeader = (BitmapHeader*) malloc(sizeof(BitmapHeader));
  int n;
  char *data;

  bool val = true;
  printf("%d\n", val);

  // open file (location, "r" == can only read from file)
  input = fopen(argv[1], "r");

  // read file and map the data to the memory allocated to bitmapHeader
  n = fread(bitmapHeader, sizeof(BitmapHeader), 1, input);

  data = (char*) malloc(sizeof(char) * bitmapHeader->bitmapSize);
  fseek(input, sizeof(char) * bitmapHeader->fileHeader.dataOffset, SEEK_SET);
  n = fread(data, sizeof(char), bitmapHeader->bitmapSize, input);

  // open file (location, "w" == can only write to file)
  output = fopen(argv[2], "w");
  n = fwrite(bitmapHeader, sizeof(char), sizeof(BitmapHeader), output);
  fseek(output, sizeof(char) * bitmapHeader->fileHeader.dataOffset, SEEK_SET);
  n = fwrite(data, sizeof(char), sizeof(BitmapHeader), output);
  fseek(output, sizeof(char) * bitmapHeader->fileHeader.dataOffset, SEEK_SET);
  n = fwrite(data, sizeof(char), bitmapHeader->bitmapSize, output);

  fclose(input);
  fclose(output);
  free(bitmapHeader);
  free(data);
  return 0;
}
