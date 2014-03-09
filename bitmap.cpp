
#include "bitmap.h"


void bitmap::hashMapToBitMap(Robot &r, const string &filename)
{

  HashMap hm = r.getHash();
  int width = hm.getMx();
  int height = hm.getMy();
  int mx = hm.getMinx();
  int my = hm.getMiny();

  cout << mx << endl;
  cout << my << endl;
  cout << height << endl;
  cout << width << endl;

  height += abs(my);
  width  += abs(mx);


  FILE *fd;
  fd = fopen(filename.c_str(), "wb");

  bitmap::bmpfile_magic fm;
  fm.magic[0] = 'B';
  fm.magic[1] = 'M';


  bitmap::bmpfile_header fh;

  fh.creator1 = 0;
  fh.creator2 = 0;
  fh.bmp_offset = sizeof(bmpfile_magic) + sizeof(bmpfile_header) + sizeof(bmp_dib_v3_header_t);


  if (width == 0) throw WIDTH_ERROR;
  int rowsize;
  int padding = 0;
  if (((width * BYTESPERPIXEL) % 4) == 0) {
    rowsize = (width * BYTESPERPIXEL) / 4;
  }
  else{
    rowsize = ((width * BYTESPERPIXEL) / 4) + 1;
    padding = (width * BYTESPERPIXEL) % 4;
  }

  cout << hm;
  cout << "padding " << padding << endl;
  fh.filesz = fh.bmp_offset + (rowsize  * height);


  bitmap::bmp_dib_v3_header_t bd;

  bd.header_sz = sizeof(bmp_dib_v3_header_t);
  bd.width = width;
  bd.height = height;
  bd.nplanes = 1;
  bd.bitspp = BYTESPERPIXEL * 8;
  bd.compress_type = 0;
  bd.bmp_bytesz = rowsize  * height;
  bd.hres = 0;
  bd.vres = 0;
  bd.ncolors = 0;
  bd.nimpcolors = 0;

  cout << "image size " << rowsize * height << endl;
  cout << "heigth " << height << endl;
  cout << "rowsize " << rowsize << endl;
  cout << "width " << width << endl;
  fwrite(&fm, sizeof(bmpfile_magic), 1, fd);
  fwrite(&fh, sizeof(bmpfile_header), 1, fd);
  fwrite(&bd, sizeof(bmp_dib_v3_header_t), 1, fd);



  unsigned int data;
  int val;

  for (int y = my; y < height - abs(my); y++){
    for (int x = mx; x < width - abs(mx); x++){

      val = hm.getValue(x, y);      
      int ot = r.cnf.OBJECT_THRESHOLD;
      if (val > ot){
        if (val > ot && val <= 50 + ot) { data = 0x00909090; }
        else if (val > 50 + ot && val <= 100 + ot) { data = 0X00808080; }
        else if (val > 100 + ot && val <= 200 + ot) { data = 0X00707070; }
        else if (val > 200 + ot && val <= 300 + ot) { data = 0x00606060; }
        else if (val > 300 + ot && val <= 400 + ot) { data = 0x00505050; }
        else if (val > 400 + ot && val <= 500 + ot) { data = 0x00404040; }
        else { data = 0x00000000; }
      } else {
        data = 0xFFFFFFFF;
      }
      fwrite(&data, BYTESPERPIXEL, 1, fd);
    }
    if (padding){
      data = 0x00000000;
      fwrite(&data, (4 - padding) , 1, fd);
    }
  }
  fclose(fd);
  cout << "Final Imatge " << endl;


}
