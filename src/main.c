#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tkmk00.h"
#include "utils.h"

#define TKMK00_VERSION "0.1"

typedef struct
{
   char *in_filename;
   char *out_dir;
   unsigned int a3;
   unsigned int offset;
} tkmk00_config_t;

// default configuration
static const tkmk00_config_t default_config = 
{
   NULL, // input filename
   NULL, // output directory
   0x01, // A3
   0x0,  // offset
};

static void print_usage(void)
{
   ERROR("Usage: tkmk00test [-d DIR] [-o OFFSET] [-v] FILE\n"
         "\n"
         "tkmk00test v" TKMK00_VERSION ": Mario Kart 64 TKMK00 decoder\n"
         "\n"
         "Optional arguments:\n"
         " -a A3        value to pass through A3 [0x01 or 0xBE] (default: 0x%02X)\n"
         " -d DIR       output directory\n"
         " -o OFFSET    offset of TKMK00 data in FILE (default: 0x%X)\n"
         " -v           verbose progress output\n"
         "\n"
         "File arguments:\n"
         " FILE        input ROM file\n",
         default_config.a3, default_config.offset);
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
               config->a3 = strtoul(argv[i], NULL, 0);
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

int main(int argc, char *argv[])
{
   char out_dir_gen[FILENAME_MAX];
   char out_filename[FILENAME_MAX];
   tkmk00_config_t config;
   unsigned char *in_buf = NULL;
   unsigned char *a1_buf = NULL;
   unsigned char *a2_buf = NULL;
   long in_size;
   long bytes_written;

   // get configuration from arguments
   config = default_config;
   parse_arguments(argc, argv, &config);
   if (config.out_dir == NULL) {
      config.out_dir = out_dir_gen;
      sprintf(config.out_dir, "%06X.decoded", config.offset);
   }

   // read input file into memory
   in_size = read_file(config.in_filename, &in_buf);
   if (in_size <= 0) {
      ERROR("Error reading input file \"%s\"\n", config.in_filename);
      exit(EXIT_FAILURE);
   }
   
   // verify input
   if (memcmp(&in_buf[config.offset], "TKMK00", 6)) {
      ERROR("Error: offset 0x%X does not begin with \"TKMK00\"\n", config.offset);
      exit(EXIT_FAILURE);
   }

   // allocate output memory
   size_t out_size = 1 * MB;
   a1_buf = malloc(out_size);
   a2_buf = malloc(out_size);
   
   // run decoder
   tkmk00decode(&in_buf[config.offset], a1_buf, a2_buf, config.a3);

   // write to output files
   sprintf(out_filename, "%s/a1.bin", config.out_dir);
   bytes_written = write_file(out_filename, a1_buf, out_size);
   if (bytes_written < (long)out_size) {
      ERROR("Error writing bytes to output file \"%s\"\n", out_filename);
      exit(EXIT_FAILURE);
   }
   
   sprintf(out_filename, "%s/a2.bin", config.out_dir);
   bytes_written = write_file(out_filename, a2_buf, out_size);
   if (bytes_written < (long)out_size) {
      ERROR("Error writing bytes to output file \"%s\"\n", out_filename);
      exit(EXIT_FAILURE);
   }

   return EXIT_SUCCESS;
}