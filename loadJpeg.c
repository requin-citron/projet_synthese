#include "loadJpeg.h"


unsigned char texture[256][256][3];

void loadJpegImage(char *fichier){
  unsigned char image[256*256*3];
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE *file;
  unsigned char *ligne;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
#ifdef __WIN32
  if (fopen_s(&file,fichier,"rb") != 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
#elif __GNUC__
  if ((file = fopen(fichier,"rb")) == 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier %s\n", fichier);
      exit(1);
    }
#endif
  jpeg_stdio_src(&cinfo, file);
  jpeg_read_header(&cinfo, TRUE);
  if (((cinfo.image_width!=256)||(cinfo.image_height!=256)) && 0) {
    fprintf(stdout,"Erreur : l'image doit etre de taille 256x256\n");
    fprintf(stderr, "width: %d\nheight: %d\n", cinfo.image_width, cinfo.image_height);
    exit(1);
  }
  if (cinfo.jpeg_color_space==JCS_GRAYSCALE) {
    fprintf(stdout,"Erreur : l'image doit etre de type RGB\n");
    exit(1);
  }

  jpeg_start_decompress(&cinfo);
  ligne=image;
  while (cinfo.output_scanline<cinfo.output_height)
    {
      ligne=image+3*256*cinfo.output_scanline;
      jpeg_read_scanlines(&cinfo,&ligne,1);
    }
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(file);
  for (int i=0;i<256;i++){
    for (int j=0;j<256;j++) {
    texture[i][j][0]=image[i*256*3+j*3];
    texture[i][j][1]=image[i*256*3+j*3+1];
    texture[i][j][2]=image[i*256*3+j*3+2];
   }
  }
}

unsigned char *get_texture(){
  return texture;
}