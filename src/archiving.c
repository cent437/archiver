#include "../libs/stack/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TO_DIGIT_4 (str_compressed[i] - 48) * 1000 + (str_compressed[i] - 48) * 100 + (str_compressed[i + 1] - 48) * 10 + (str_compressed[i + 2] - 48)
#define TO_DIGIT_3 (str_compressed[i] - 48) * 100 + (str_compressed[i + 1] - 48) * 10 + (str_compressed[i + 2] - 48)
#define TO_DIGIT_2 (str_compressed[i] - 48) * 10 + (str_compressed[i + 1] - 48)
#define TO_DIGIT_1 str_compressed[i + 1]

#define IS_DIGIT_4 isDigit(str_compressed[i]) && isDigit(str_compressed[i + 1]) && isDigit(str_compressed[i + 2]) && isDigit(str_compressed[i + 3])
#define IS_DIGIT_3 isDigit(str_compressed[i]) && isDigit(str_compressed[i + 1]) && isDigit(str_compressed[i + 2])
#define IS_DIGIT_2 isDigit(str_compressed[i]) && isDigit(str_compressed[i + 1])
#define IS_DIGIT_1 isDigit(str_compressed[i])

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
long long get_filesize(FILE *f)
{
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
void decompress(FILE *f_compressed, FILE *f_decompressed, long long compressed_size)
{
   int quantity = 0;
   char symbol = 0;
   char *str_compressed = (char *)malloc(compressed_size * sizeof(char));
   char *str_decompressed = NULL;
   if (fscanf(f_compressed, "%s", str_compressed) == 0)
   {
      perror("Ошибка. Чтение не произведено.");
      exit(1);
   }
   for (size_t i = 0; i < strlen(str_compressed);)
   {
      if (IS_DIGIT_4)
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
         if (fprintf(f_decompressed, "%s", str_decompressed) == 0)
         {
            perror("Ошибка. Разархивация не произведена.");
            exit(1);
         }
         free(str_decompressed);
      }
      if (IS_DIGIT_3)
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
         if (fprintf(f_decompressed, "%s", str_decompressed) == 0)
         {
            perror("Ошибка. Разархивация не произведена.");
            exit(1);
         }
         free(str_decompressed);
      }
      else if (IS_DIGIT_2)
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
         if (fprintf(f_decompressed, "%s", str_decompressed) == 0)
         {
            perror("Ошибка. Разархивация не произведена.");
            exit(1);
         }
         free(str_decompressed);
      }
      else if (IS_DIGIT_1)
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
         if (fprintf(f_decompressed, "%s", str_decompressed) == 0)
         {
            perror("Ошибка. Разархивация не произведена.");
            exit(1);
         }
         free(str_decompressed);
      }
   }
   free(str_compressed);
}