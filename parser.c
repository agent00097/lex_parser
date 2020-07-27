#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.c"
#include "tokens.h"

int lookahead = 0;

void program(), function_list(), end_list(), function(), function_list_prime(), parameter(), parameter_prime(), statements(), statements_prime(), statement(), expexp(), exp_prime(), term(), term_prime(), factor(), exp_list(), exp_list_prime(), end_list_prime(), end(), function_prime(), statement_prime(), statement_double_prime(), statement_triple_prime(), factor_prime(), factor_double_prime(), end_prime(), end_double_prime(), match(int tokn);

char *syntax_err_msg = "Syntax Error: line %d";
char *accept_msg = "String Accepted";

int total_functions = 0;

int total_ids_in_fun = 0;

char id_store[20][20];

int storing_line_number[20][20];

int printed_global = 0;

int main(int argc, char **argv)
{
   for (int q = 0; q < 20; q++)
   {
      for (int w = 0; w < 20; w++)
      {
         storing_line_number[q][w] = -255;
      }
   }

   lookahead = yylex();
   program();
   while (lookahead > 0)
   { //yylex() returns 0 at EOF
      fprintf(stderr, "%d ", lookahead);
      lookahead = yylex();
   }
   printf("Number of functions defined: %d\n", total_functions);
   //printf("Identifier's : %d", id_counter);

   return 0;
}

void display()
{
   for (int l = 0; l < total_ids_in_fun; l++)
   {
      printf(" %s: ", id_store[l]);
      int k = 0;
      while (storing_line_number[l][k] != -255)
      {
         printf("%d ", storing_line_number[l][k]);
         k++;
      }
      printf("\n");
   }
   printf("\n");
}

void clear()
{
   for (int q = 0; q < 20; q++)
   {
      for (int w = 0; w < 20; w++)
      {
         id_store[q][w] = ' ';
      }
   }

   for (int q = 0; q < 20; q++)
   {
      for (int w = 0; w < 20; w++)
      {
         storing_line_number[q][w] = -255;
      }
   }

   total_ids_in_fun = 0;
}

int check()
{
   for (int u = 0; u < total_ids_in_fun; u++)
   {
      if (strcmp(id_store[u], name_of_id) == 0)
      {
         return u;
      }
   }
   return -2;
}

void program()
{
   function_list();
   end_list();
}

void function_list()
{
   function();
   function_list_prime();
}

void function_list_prime()
{
   if (lookahead == DEF)
   {
      function();
      function_list_prime();
   }
   else
   {
      return;
   }
}

void function()
{
   match(DEF);
   total_functions++;
   match(IDENTIFIER);
   printf("Function %s: line %d\n", name_of_id, line_number);
   match(LEFTB);
   function_prime();
}

void parameter()
{
   int c = check();
   //First checking if the identifier is already in the array
   if (check() != -2)
   {
      //Already exists
      //Now adding the line number associated with it
      int k = 0;
      while (storing_line_number[c][k] != -255)
      {
         k++;
      }
      storing_line_number[c][k] = line_number;
      //printf("%s was in %d\n", id_store[c], storing_line_number[c][k]);
   }
   else
   {
      //If it doesnt exist then we need to add it in the array
      strcpy(id_store[total_ids_in_fun], name_of_id);
      int k = 0;
      while (storing_line_number[total_ids_in_fun][k] != -255)
      {
         k++;
      }
      storing_line_number[total_ids_in_fun][k] = line_number;
      //printf("%s was in %d\n", id_store[total_ids_in_fun], storing_line_number[total_ids_in_fun][k]);
      total_ids_in_fun++;
   }
   //printf("Parameter : Identifier here is : %s", name_of_id);
   match(IDENTIFIER);
   parameter_prime();
}

void parameter_prime()
{
   if (lookahead == COMMA)
   {
      match(COMMA);
      int c = check();
      //First checking if the identifier is already in the array
      if (check() != -2)
      {
         //Already exists
         //Now adding the line number associated with it
         int k = 0;
         while (storing_line_number[c][k] != -255)
         {
            k++;
         }
         storing_line_number[c][k] = line_number;
         //printf("%s was in %d\n", id_store[c], storing_line_number[c][k]);
      }
      else
      {
         //If it doesnt exist then we need to add it in the array
         strcpy(id_store[total_ids_in_fun], name_of_id);
         int k = 0;
         while (storing_line_number[total_ids_in_fun][k] != -255)
         {
            k++;
         }
         storing_line_number[total_ids_in_fun][k] = line_number;
         //printf("%s was in %d\n", id_store[total_ids_in_fun], storing_line_number[total_ids_in_fun][k]);
         total_ids_in_fun++;
      }
      //printf("Parameter_prime : Identifier here is : %s\n", name_of_id);
      match(IDENTIFIER);
      parameter_prime();
   }
   else
   {
      return;
   }
}

void statements()
{
   statement();
   statements_prime();
}

void statements_prime()
{
   if (lookahead == IDENTIFIER || lookahead == PRINT || lookahead == RETURN)
   {
      statement();
      statements_prime();
   }
   else
   {
      return;
   }
}

void statement()
{
   if (lookahead == IDENTIFIER)
   {
      int c = check();
      //First checking if the identifier is already in the array
      if (check() != -2)
      {
         //Already exists
         //Now adding the line number associated with it
         int k = 0;
         while (storing_line_number[c][k] != -255)
         {
            k++;
         }
         storing_line_number[c][k] = line_number;
         //printf("%s was in %d\n", id_store[c], storing_line_number[c][k]);
      }
      else
      {
         //If it doesnt exist then we need to add it in the array
         strcpy(id_store[total_ids_in_fun], name_of_id);
         int k = 0;
         while (storing_line_number[total_ids_in_fun][k] != -255)
         {
            k++;
         }
         storing_line_number[total_ids_in_fun][k] = line_number;
         //printf("%s was in %d\n", id_store[total_ids_in_fun], storing_line_number[total_ids_in_fun][k]);
         total_ids_in_fun++;
      }
      //printf("Statement : Identifier here is : %s\n", name_of_id);
      match(IDENTIFIER);
      statement_triple_prime();
   }
   else if (lookahead == PRINT)
   {
      match(PRINT);
      match(LEFTB);
      exp_list();
      match(RIGHTB);
   }
   else
   {
      match(RETURN);
      expexp();
   }
}

void expexp()
{
   term();
   exp_prime();
}

void exp_prime()
{
   if (lookahead == PLUS)
   {
      match(PLUS);
      term();
      exp_prime();
   }
   else if (lookahead == MINUS)
   {
      match(MINUS);
      term();
      exp_prime();
   }
   else
   {
      return;
   }
}

void term()
{
   factor();
   term_prime();
}

void term_prime()
{
   if (lookahead == MULTIPLY)
   {
      match(MULTIPLY);
      factor();
      term_prime();
   }
   else if (lookahead == DIVIDE)
   {
      match(DIVIDE);
      factor();
      term_prime();
   }
   else
   {
      return;
   }
}

void factor()
{
   if (lookahead == IDENTIFIER)
   {
      int c = check();
      //First checking if the identifier is already in the array
      if (check() != -2)
      {
         //Already exists
         //Now adding the line number associated with it
         int k = 0;
         while (storing_line_number[c][k] != -255)
         {
            k++;
         }
         storing_line_number[c][k] = line_number;
         //printf("%s was in %d\n", id_store[c], storing_line_number[c][k]);
      }
      else
      {
         //If it doesnt exist then we need to add it in the array
         strcpy(id_store[total_ids_in_fun], name_of_id);
         int k = 0;
         while (storing_line_number[total_ids_in_fun][k] != -255)
         {
            k++;
         }
         storing_line_number[total_ids_in_fun][k] = line_number;
         //printf("%s was in %d\n", id_store[total_ids_in_fun], storing_line_number[total_ids_in_fun][k]);
         total_ids_in_fun++;
      }
      //printf("Factor : Identifier here is : %s\n", name_of_id);
      match(IDENTIFIER);
      factor_double_prime();
   }
   else if (lookahead == LEFTB)
   {
      match(LEFTB);
      expexp();
      match(RIGHTB);
   }
   else if (lookahead == MINUS)
   {
      match(MINUS);
      factor();
   }
   else
   {
      match(NUMBER);
   }
}

void exp_list()
{
   expexp();
   exp_list_prime();
}

void exp_list_prime()
{
   if (lookahead == COMMA)
   {
      match(COMMA);
      expexp();
      exp_list_prime();
   }
   else
   {
      return;
   }
}

void end_list()
{
   end();
   end_list_prime();
   display();
}

void end_list_prime()
{
   if (lookahead == IDENTIFIER || lookahead == PRINT)
   {
      end();
      end_list_prime();
   }
   else
   {
      return;
   }
}

void end()
{
   if (printed_global == 0)
   {
      printed_global++;
      printf("Global: line %d\n", line_number);
   }
   else
   {
      if (lookahead == IDENTIFIER)
      {
         int c = check();
         //First checking if the identifier is already in the array
         if (check() != -2)
         {
            //Already exists
            //Now adding the line number associated with it
            int k = 0;
            while (storing_line_number[c][k] != -255)
            {
               k++;
            }
            storing_line_number[c][k] = line_number;
            //printf("%s was in %d\n", id_store[c], storing_line_number[c][k]);
         }
         else
         {
            //If it doesnt exist then we need to add it in the array
            strcpy(id_store[total_ids_in_fun], name_of_id);
            int k = 0;
            while (storing_line_number[total_ids_in_fun][k] != -255)
            {
               k++;
            }
            storing_line_number[total_ids_in_fun][k] = line_number;
            //printf("%s was in %d\n", id_store[total_ids_in_fun], storing_line_number[total_ids_in_fun][k]);
            total_ids_in_fun++;
         }
         //printf("End : Identifier here is : %s\n", name_of_id);
         match(IDENTIFIER);
         end_double_prime();
      }
      else
      {
         match(PRINT);
         match(LEFTB);
         exp_list();
         match(RIGHTB);
      }
   }
}

void function_prime()
{
   if (lookahead == RIGHTB)
   {
      match(RIGHTB);
      match(COLON);
      statements();
      match(ENDDEF);
      //This is where I have to display and clear the existing variables
      display();
      clear();
   }
   else
   {
      parameter();
      match(RIGHTB);
      match(COLON);
      statements();
      match(ENDDEF);
      //This is where I have to display and clear the existing variables
      display();
      clear();
   }
}

void statement_prime()
{
   if (lookahead == INPUT)
   {
      match(INPUT);
      match(LEFTB);
      match(RIGHTB);
   }
   else
   {
      expexp();
   }
}

void statement_double_prime()
{
   if (lookahead == RIGHTB)
   {
      match(RIGHTB);
   }
   else
   {
      exp_list();
      match(RIGHTB);
   }
}

void statement_triple_prime()
{
   if (lookahead == LEFTB)
   {
      match(LEFTB);
      statement_double_prime();
   }
   else
   {
      match(ASSIGNMENT);
      statement_prime();
   }
}

void factor_prime()
{
   if (lookahead == RIGHTB)
   {
      match(RIGHTB);
   }
   else
   {
      exp_list();
      match(RIGHTB);
   }
}

void factor_double_prime()
{
   if (lookahead == LEFTB)
   {
      match(LEFTB);
      factor_prime();
   }
   else
   {
      return;
   }
}

void end_prime()
{
   if (lookahead == RIGHTB)
   {
      match(RIGHTB);
   }
   else
   {
      exp_list();
      match(RIGHTB);
   }
}

void end_double_prime()
{
   if (lookahead == LEFTB)
   {
      match(LEFTB);
      end_prime();
   }
   else
   {
      match(ASSIGNMENT);
      match(INPUT);
      match(LEFTB);
      match(RIGHTB);
   }
}

void match(int tokn)
{
   if (tokn == lookahead)
   {
      lookahead = yylex();
      if(lookahead == 1) {
         fprintf(stdout, "Unknown Token: line %d", line_number);
         exit(0);
      }
   }
   else
   {
      fprintf(stdout, "Syntax Error: line %d", line_number);
      exit(0);
   }
}