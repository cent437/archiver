#include "libs/stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
void compress(char *str)
{
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
}
void help()
{
   puts("Одним из параметров всегда должен быть путь к файлу.");
   puts("a.out [ПУТЬ_ДО_ФАЙЛА]");
   puts("-h    --help      Подсказка.");
   puts("-a    --archive   Архивировать файл, указанный в [ПУТЬ_ДО_ФАЙЛА].");
   puts("-e    --extract   Разархивировать файл, указанный в [ПУТЬ_ДО_ФАЙЛА].");
}
int main(int argc, char *argv[])
{

   int ui_index = -1;
   char *way_to_file;
   FILE *f;
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
            // compress(way_to_file);
            exit(0);
         }
         if (strcmp(argv[arg_number], "--extract") == 0 || strcmp(argv[arg_number], "-e") == 0)
         {
            help();
            exit(0);
         }
         if (argv[arg_number][0] == 'D')
         {
            printf("Открыт файл %s.", argv[arg_number]);
            strcpy(way_to_file, argv[arg_number]);
         }
      }
   }
   return 0;
}
