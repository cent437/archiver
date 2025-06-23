#include "../libs/stack/stack.h"
#include "archiving.h"
#include <stdlib.h>
#include <string.h>
void help()
{
   puts("a.out [ПУТЬ_ДО_ФАЙЛА] -[ПАРАМЕТРЫ]");
   puts("-h    --help      Вывод данной справки.");
   puts("-a    --archive   Архивировать файл, указанный в [ПУТЬ_ДО_ФАЙЛА].");
   puts("-e    --extract   Разархивировать файл, указанный в [ПУТЬ_ДО_ФАЙЛА].");
}
int main(int argc, char *argv[])
{
   FILE *f_src, *f_dest;
   if (argc == 1)
   {
      puts("Ошибка: нет входных данных. Для справки используйте параметр --help.");
      exit(0);
   }
   if (argc > 1)
   {
      for (size_t arg_number = 0; arg_number < argc; arg_number++)
      {
         if (strcmp(argv[arg_number], "--help") == 0 || strcmp(argv[arg_number], "-h") == 0)
         {
            help();
            exit(0);
         }
         if (strcmp(argv[arg_number], "--archive") == 0 || strcmp(argv[arg_number], "-a") == 0)
         {
            f_src = fopen(argv[1], "rb");
            long long file_size = get_filesize(f_src);
            fclose(f_src);

            f_src = fopen(argv[1], "r");
            f_dest = fopen("compressed.txt", "w");
            compress(f_src, file_size);
            print_to_file(f_dest);
         }
         if (strcmp(argv[arg_number], "--extract") == 0 || strcmp(argv[arg_number], "-e") == 0)
         {
            f_src = fopen(argv[1], "rb");
            long long file_size = get_filesize(f_src);
            fclose(f_src);

            f_src = fopen(argv[1], "r");
            f_dest = fopen("decompressed.txt", "w+");
            decompress(f_src, f_dest, file_size);
         }
      }
   }
   fclose(f_src);
   fclose(f_dest);
   return 0;
}
