#ifndef __BITMAP__
#define __BITMAP__
#include <stdint.h>
#define BYTESPERPIXEL 3
#define WIDTH_ERROR 3
#include "robot.h"
#include <string>
#include <iostream>
#include "hash.h"

using namespace std;

namespace bitmap{

  /* Capcaleres del fitxer per el format 
   * bmp.
   */
  typedef struct {
    unsigned char magic[2];
  }bmpfile_magic;
 
  typedef struct {
    uint32_t filesz;
    uint16_t creator1;
    uint16_t creator2;
    uint32_t bmp_offset;
  }bmpfile_header;

  typedef struct {
    uint32_t header_sz;
    uint32_t width;
    uint32_t height;
    uint16_t nplanes;
    uint16_t bitspp;
    uint32_t compress_type;
    uint32_t bmp_bytesz;
    uint32_t hres;
    uint32_t vres;
    uint32_t ncolors;
    uint32_t nimpcolors;
  } bmp_dib_v3_header_t;

  /* Funcio que passa les dades recollides per
   * el robot al fitxer bitmap que ens mostrara
   * el mapa de l'entorn.
   */
  void hashMapToBitMap(Robot&, const string&);

}

#endif
