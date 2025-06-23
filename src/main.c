#include "../libs/stack/stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define TO_DIGIT_4 (str_compressed[i] - 48) * 1000 + (str_compressed[i] - 48) * 100 + (str_compressed[i + 1] - 48) * 10 + (str_compressed[i + 2] - 48)
#define TO_DIGIT_3 (str_compressed[i] - 48) * 100 + (str_compressed[i + 1] - 48) * 10 + (str_compressed[i + 2] - 48)
#define TO_DIGIT_2 (str_compressed[i] - 48) * 10 + (str_compressed[i + 1] - 48)
#define TO_DIGIT_1 str_compressed[i + 1]
bool isDigit(char symbol)
{
   bool check = false;
   if (symbol < 0x30 || symbol > 0x39)
      return check;

   for (int i = 0x30; i <= 0x39; i++)
   {
      if (symbol == i)
      {
         check = !check;
         break;
      }
   }
   return check;
}
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
   push(symbol, quantity);
   free(str);
}
void decompress(const char *compressed_file, const char *new_file)
{
   int quantity = 0;
   char symbol = 0;
   char *str_compressed = (char *)malloc(get_filesize(compressed_file) * sizeof(char));
   char *str_decompressed = NULL;
   FILE *f_compressed = fopen(compressed_file, "r");
   FILE *f_destination = fopen(new_file, "w+");
   if (fscanf(f_compressed, "%s", str_compressed) == 0)
   {
      perror("Ошибка. Чтение не произведено.");
      exit(1);
   }
   for (size_t i = 0; i < strlen(str_compressed);)
   {
      if (isDigit(str_compressed[i]) && isDigit(str_compressed[i + 1]) && isDigit(str_compressed[i + 2]) && isDigit(str_compressed[i + 3]))
      {
         quantity = TO_DIGIT_4;
         symbol = str_compressed[i + 4];
         i += 5;
         str_decompressed = (char *)calloc(quantity, sizeof(char));
         if (str_decompressed == NULL)
         {
            perror("Ошибка выделения памяти.");
            exit(1);
         }
         memset(str_decompressed, symbol, quantity + 1);
         str_decompressed[quantity] = '\0';
         if (fprintf(f_destination, "%s", str_decompressed) == 0)
         {
            perror("Ошибка. Разархивация не произведена.");
            exit(1);
         }
         free(str_decompressed);
      }
      if (isDigit(str_compressed[i]) && isDigit(str_compressed[i + 1]) && isDigit(str_compressed[i + 2]))
      {
         quantity = TO_DIGIT_3;
         symbol = str_compressed[i + 3];
         i += 4;
         str_decompressed = (char *)calloc(quantity, sizeof(char));
         if (str_decompressed == NULL)
         {
            perror("Ошибка выделения памяти.");
            exit(1);
         }
         memset(str_decompressed, symbol, quantity + 1);
         str_decompressed[quantity] = '\0';
         if (fprintf(f_destination, "%s", str_decompressed) == 0)
         {
            perror("Ошибка. Разархивация не произведена.");
            exit(1);
         }
         free(str_decompressed);
      }
      else if (isDigit(str_compressed[i]) && isDigit(str_compressed[i + 1]))
      {
         quantity = TO_DIGIT_2;
         symbol = str_compressed[i + 2];
         i += 3;
         str_decompressed = (char *)calloc(quantity, sizeof(char));
         if (str_decompressed == NULL)
         {
            perror("Ошибка выделения памяти.");
            exit(1);
         }
         memset(str_decompressed, symbol, quantity + 1);
         str_decompressed[quantity] = '\0';
         if (fprintf(f_destination, "%s", str_decompressed) == 0)
         {
            perror("Ошибка. Разархивация не произведена.");
            exit(1);
         }
         free(str_decompressed);
      }
      else if (isDigit(str_compressed[i]))
      {
         quantity = (str_compressed[i] - 48);
         symbol = TO_DIGIT_1;
         i += 2;
         str_decompressed = (char *)calloc(quantity, sizeof(char));
         if (str_decompressed == NULL)
         {
            perror("Ошибка выделения памяти.");
            exit(1);
         }
         memset(str_decompressed, symbol, quantity + 1);
         str_decompressed[quantity] = '\0';
         if (fprintf(f_destination, "%s", str_decompressed) == 0)
         {
            perror("Ошибка. Разархивация не произведена.");
            exit(1);
         }
         free(str_decompressed);
      }
   }

   fclose(f_compressed);
   fclose(f_destination);
   free(str_compressed);
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
            decompress(argv[1], "new.txt");
            exit(0);
         }
      }
   }
   return 0;
}
