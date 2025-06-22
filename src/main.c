#include "../libs/stack/stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
long long get_filesize(const char *filename)
{
   FILE *f = fopen(filename, "rb");
   long long file_size = 0;
   if (f == NULL)
      file_size = -1;
   else
   {
      fseek(f, 0, SEEK_END);
      file_size = ftello(f);
      fclose(f);
   }
   return file_size;
}
void compress(FILE *f, long long file_size)
{
   char *str = (char *)malloc(file_size * sizeof(char));
   fscanf(f, "%s", str);
   char symbol = str[0];
   int quantity = 0;
   for (size_t i = 0; i < strlen(str); i++)
   {
      if (symbol == str[i])
         quantity++;

      else
      {
         push(symbol, quantity);
         symbol = str[i];
         i--;
         quantity = 0;
      }
   }
   free(str);
}
void help()
{
   puts("Одним из параметров всегда должен быть путь к файлу.");
   puts("a.out [ПУТЬ_ДО_ФАЙЛА] -[ПАРАМЕТРЫ]");
   puts("-h    --help      Подсказка.");
   puts("-a    --archive   Архивировать файл, указанный в [ПУТЬ_ДО_ФАЙЛА].");
   puts("-e    --extract   Разархивировать файл, указанный в [ПУТЬ_ДО_ФАЙЛА].");
}
int main(int argc, char *argv[])
{

   FILE *f_src, *f_dest;
   if (argc == 1)
   {
      help();
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
            f_src = fopen(argv[1], "r");
            compress(f_src, get_filesize(argv[1]));
            fclose(f_src);

            f_dest = fopen("compressed.txt", "w");
            print_to_file(f_dest);
            fclose(f_dest);
         }
         if (strcmp(argv[arg_number], "--extract") == 0 || strcmp(argv[arg_number], "-e") == 0)
         {
            help();
            exit(0);
         }
      }
   }
   return 0;
}
