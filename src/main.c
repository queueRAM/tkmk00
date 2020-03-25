#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "n64graphics.h"
#include "tkmk00.h"
#include "utils.h"

#define TKMK00_VERSION "0.1"

typedef struct
{
   char *in_filename;
   char *out_dir;
   uint32_t alpha_color;
   uint32_t offset;
} tkmk00_config_t;

static const uint32_t OFFSET_ALL = 0xFFFFFFFF;

// default configuration
static const tkmk00_config_t default_config = 
{
   NULL, // input filename
   NULL, // output directory
   0x01, // color to clear alpha
   OFFSET_ALL, // offset
};

static void print_usage(void)
{
   ERROR("Usage: tkmk00test [-d DIR] [-o OFFSET] [-v] FILE\n"
         "\n"
         "tkmk00test v" TKMK00_VERSION ": Mario Kart 64 TKMK00 decoder\n"
         "\n"
         "Optional arguments:\n"
         " -a ALPHA     RGBA color to clear alpha bit [usually 0x01 or 0xBE] (default: 0x%02X)\n"
         " -d DIR       output directory (default: pwd)\n"
         " -o OFFSET    offset of TKMK00 data in FILE (default: all)\n"
         " -v           verbose progress output\n"
         "\n"
         "File arguments:\n"
         " FILE        input ROM file\n",
         default_config.alpha_color);
   exit(EXIT_FAILURE);
}

// parse command line arguments
static void parse_arguments(int argc, char *argv[], tkmk00_config_t *config)
{
   int i;
   int file_count = 0;
   if (argc < 2) {
      print_usage();
   }
   for (i = 1; i < argc; i++) {
      if (argv[i][0] == '-') {
         switch (argv[i][1]) {
            case 'a':
               if (++i >= argc) {
                  print_usage();
               }
               config->alpha_color = strtoul(argv[i], NULL, 0);
               break;
            case 'd':
               if (++i >= argc) {
                  print_usage();
               }
               config->out_dir = argv[i];
               break;
            case 'o':
               if (++i >= argc) {
                  print_usage();
               }
               config->offset = strtoul(argv[i], NULL, 0);
               break;
            case 'v':
               g_verbosity = 1;
               break;
            default:
               print_usage();
               break;
         }
      } else {
         switch (file_count) {
            case 0:
               config->in_filename = argv[i];
               break;
            default: // too many
               print_usage();
               break;
         }
         file_count++;
      }
   }
   if (file_count < 1) {
      print_usage();
   }
}

// find all TKMK00 blocks in the buffer
static int find_tkmk00(unsigned char *buf, unsigned int buf_len, unsigned int *offsets)
{
   unsigned int i;
   int count = 0;
   for (i = 0; i < buf_len - 0x10; i += 4) {
      if (0 == memcmp(&buf[i], "TKMK00", 6)) {
         offsets[count++] = i;
      }
   }
   return count;
}

static void extract_tkmk00(uint8_t *buf, char *out_dir, uint32_t offset, uint32_t alpha_color)
{
   char out_filename[FILENAME_MAX];
   uint8_t *a1_buf = NULL;
   uint8_t *a2_buf = NULL;
   long bytes_written;
   int w, h;
   int a1_size, a2_size;
   size_t out_size;

   // verify input
   if (memcmp(&buf[offset], "TKMK00", 6)) {
      ERROR("Error: offset 0x%X does not begin with \"TKMK00\"\n", offset);
      exit(EXIT_FAILURE);
   }

   // allocate output memory
   out_size = 512 * KB;
   a1_buf = calloc(1, out_size);
   a2_buf = calloc(1, out_size);

   w = read_u16_be(&buf[offset + 0x8]);
   h = read_u16_be(&buf[offset + 0xA]);
   
   // run decoder
   tkmk00_decode(&buf[offset], a1_buf, a2_buf, alpha_color);

   make_dir(out_dir);

   // write to output files
   sprintf(out_filename, "%s/%06X.a1.bin", out_dir, offset);
   a1_size = w * h;
   bytes_written = write_file(out_filename, a1_buf, a1_size);
   if (bytes_written < a1_size) {
      ERROR("Error writing to output file \"%s\"\n", out_filename);
      exit(EXIT_FAILURE);
   }
   
   sprintf(out_filename, "%s/%06X.a2.bin", out_dir, offset);
   a2_size = 2 * w * h;
   bytes_written = write_file(out_filename, a2_buf, a2_size);
   if (bytes_written < a2_size) {
      ERROR("Error writing to output file \"%s\"\n", out_filename);
      exit(EXIT_FAILURE);
   }

   sprintf(out_filename, "%s/%06X.png", out_dir, offset);
   rgba *img = raw2rgba((char*)a2_buf, w, h, 16);
   rgba2png(img, w, h, out_filename);

   free(a1_buf);
   free(a2_buf);
}

int main(int argc, char *argv[])
{
   char out_dir_gen[FILENAME_MAX];
   unsigned int offsets[128];
   tkmk00_config_t config;
   uint8_t *in_buf = NULL;
   long in_size;
   unsigned int offset_count;
   unsigned int i;

   // get configuration from arguments
   config = default_config;
   parse_arguments(argc, argv, &config);
   if (config.out_dir == NULL) {
      config.out_dir = out_dir_gen;
      sprintf(config.out_dir, "%s.tkmk00", basename(config.in_filename));
   }

   // read input file into memory
   in_size = read_file(config.in_filename, &in_buf);
   if (in_size <= 0) {
      ERROR("Error reading input file \"%s\"\n", config.in_filename);
      exit(EXIT_FAILURE);
   }

   if (config.offset == OFFSET_ALL) {
      offset_count = find_tkmk00(in_buf, (unsigned int)in_size, offsets);
   } else {
      offsets[0] = config.offset;
      offset_count = 1;
   }

   for (i = 0; i < offset_count; i++) {
      extract_tkmk00(in_buf, config.out_dir, offsets[i], config.alpha_color);
   }

   return EXIT_SUCCESS;
}
