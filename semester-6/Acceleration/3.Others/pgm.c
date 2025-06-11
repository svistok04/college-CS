#include "pgm.h"

unsigned char* read_pgm(const char* filename, int* width, int* height) {
  FILE* f = fopen(filename, "rb");
  if (!f) { perror("fopen"); return NULL; }
  char magic[3];
  if (!fgets(magic, sizeof(magic), f)) { fclose(f); return NULL; }
  if (magic[0] != 'P' || magic[1] != '5') { fclose(f); return NULL; }

  int w = 0, h = 0, maxval = 0;
  int c;

  do {
    c = fgetc(f);
  } while (
  c == '#' 
  ? (fgets((char[1024]){}, 1024, f), 1) 
  : (ungetc(c, f), 0)
);
  fscanf(f, "%d %d", &w, &h);

  do {
    c = fgetc(f);
  } while (
  c == '#' 
  ? (fgets((char[1024]){}, 1024, f), 1) 
  : (ungetc(c, f), 0)
);
  fscanf(f, "%d", &maxval);

  fgetc(f);

  unsigned char* data = malloc(w * h);
  fread(data, 1, w * h, f);
  fclose(f);
  *width = w;
  *height = h;
  return data;
}


void write_pgm(const char* filename, const unsigned char* data, int width, int height) {
  FILE* f = fopen(filename, "wb");
  if (!f) { perror("fopen"); return; }
  fprintf(f, "P5\n%d %d\n255\n", width, height);
  fwrite(data, 1, width * height, f);
  fclose(f);
}
