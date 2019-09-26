//*****************************************************************************
// purpose: CSE 4713 / 6713 Assignment 1: Lexical Analyzer
// created: 2-6-2019
//  author: Jason C McQueen
//*****************************************************************************
#include "lexer.h"
#include <ctype.h>
#include <assert.h>
#include <string.h>

//*****************************************************************************
// Do the lexical parsing
char lexeme[MAX_LEXEME_LEN];  // Character buffer for lexeme
char left_over = '\0';
int yylex()
{
  static char c = -1;         // Have we read the first character yet?
  int char_type;              // Hold the character type

  // Prepare the buffer to hold the lexeme
  for( int i = 0; i < MAX_LEXEME_LEN; i++ ){
    lexeme[i] = '\0';
  yytext = lexeme;
  yyleng = 0;}

  // Test for end of file
  if( feof(yyin) ) {
    // Ready for next time
    c = -1;
    // Done!
    return( TOK_EOF );
  }
  //if we have a left over, put them in before we read any more
  if (left_over != '\0'){
    if(!isspace(c) && c != '\n'){
      c = left_over;
      left_over = '\0';
    //  printf("USED A LEFT OVER: %c", c);       DEBUG
    }
  }

  if (isspace(c)){
    c = fgetc(yyin);
  }
  // If the very first character has not yet been read, read it
  if( c < 0 )
    c = fgetc( yyin );

// its a space, and we don't want to read spaces as lexemes
 if ((int)c == 32){
   c = fgetc( yyin );
 }



 //test for OPERATORS
 //      +               -               *               /               :                =            <                >
if((int)c == 43 || (int)c == 45 || (int)c == 42 || (int)c == 47 || (int)c == 58 || (int)c == 61 || (int)c == 60 || (int)c == 62 ){
    lexeme[yyleng++] = c;
  if ((int)c == 43){
    c = -1;
    return TOK_PLUS;
  }
  if ((int)c == 45){
    c = -1;
    return TOK_MINUS;
  }
  if ((int)c == 42){
    c = -1;
    return TOK_MULTIPLY;
  }
  if ((int)c == 47){
    c = -1;
    return TOK_DIVIDE;
  }
  //equal sign
  if ((int)c == 61){
    c = fgetc(yyin);
    if((int)c == 61){
      lexeme[yyleng++] = c;
    c = -1;
    return TOK_EQUALTO;
  }
  else{
    left_over = c;
    c = -1;
    return TOK_UNKNOWN;
  }
  }
  if((int)c == 58){
    c = fgetc(yyin);
    if((int)c == 61){
      lexeme[yyleng++] = c;
    c = -1;
    return TOK_ASSIGN;
  }
  }
  if((int)c == 60){
    c = fgetc(yyin);
    if((int)c == 62){
      lexeme[yyleng++] = c;
    c = -1;
    return TOK_NOTEQUALTO;
  }
  else{
    left_over = c;
    c = -1;
    return TOK_LESSTHAN;
  }
  }
  if((int)c == 62){
    c = -1;
    return TOK_GREATERTHAN;
  }
}

//test for PUNCTUATION
//PUNCTUATION MARKS
//       (                )              ;                [                ]              {                 }               ,
if ((int)c == 40 || (int)c == 41 || (int)c == 59 || (int)c == 91 || (int)c == 93 || (int)c == 123 || (int)c == 125 || (int)c == 44){
lexeme[yyleng++] = c;
//       (
if ((int)c == 40){
  c = -1;
  return TOK_OPENPAREN;
}
//       )
if((int)c == 41){
  c = -1;
  return TOK_CLOSEPAREN;
}
//      ;
if ((int)c == 59){
  c = -1;
  return TOK_SEMICOLON;
}
//     [
if ((int)c == 91){
  c = -1;
  return TOK_OPENBRACKET;
}
//     ]
if((int)c == 93){
  c = -1;
  return TOK_CLOSEBRACKET;
}
//       {
if((int)c == 123){
  c = -1;
  return TOK_OPENBRACE;
}
//        }
if((int)c == 125){
  c = -1;
  return TOK_CLOSEBRACE;
}
//        ,
if((int)c == 44){
  c = -1;
  return TOK_COMMA;
}
}

//test for a LETTER
if (((int)c >= 65 && (int)c <= 90 ) ||  ((int)c >= 97 && (int)c <=122)){
  lexeme[yyleng++] = c;
  c = fgetc(yyin);
  // while its a letter or a number or an underscore
  while ((((int)c >= 65 && (int)c <= 90 ) ||  ((int)c >= 97 && (int)c <=122)) || ((int)c > 47 && (int)c <= 57) || (int)c == 95) {
    lexeme[yyleng++] = c;
    c = fgetc(yyin);
  }
//make all of our keys to compare to the lexeme string and define our result ints from the strcmps
char if_key [] = "if";
char else_key[] = "else";
char for_key[] = "for";
char while_key[] = "while";
char print_key[] = "print";
char return_key[] = "return";
char continue_key[] = "continue";
char break_key[] = "break";
char debug_key[] = "debug";
char read_key[] = "read";
char let_key[] = "let";
char int_key[] = "int";
char float_key[] = "float";
char string_key[] = "string";
char and_key[] = "and";
char or_key[] = "or";
char not_key[] = "not";
char length_key[] = "length";

int if_res, else_res, for_res, while_res, print_res, return_res, continue_res, break_res, debug_res, read_res, let_res, int_res, float_res, string_res, and_res, or_res, not_res, length_res;
//make our string out of the lexeme array, and because it has nulls in it...
//...and those won't work with strcmp.  So let's make another one, but only as long as yyleng
char *lexeme_compare = new char[yyleng];
for (int i = 0; i < yyleng; i++){
  lexeme_compare[i] = lexeme[i];
}
//start comparing to all of our afformentioned keys
if_res = strcmp(lexeme_compare, if_key);
else_res = strcmp(lexeme_compare, else_key);
for_res = strcmp(lexeme_compare, for_key);
while_res = strcmp(lexeme_compare, while_key);
print_res = strcmp(lexeme_compare, print_key);
return_res = strcmp(lexeme_compare, return_key);
continue_res = strcmp(lexeme_compare, continue_key);
break_res = strcmp(lexeme_compare, break_key);
debug_res = strcmp(lexeme_compare, debug_key);
read_res = strcmp(lexeme_compare, read_key);
let_res = strcmp(lexeme_compare, let_key);
int_res = strcmp(lexeme_compare, int_key);
float_res = strcmp(lexeme_compare, float_key);
string_res = strcmp(lexeme_compare, string_key);
and_res = strcmp(lexeme_compare, and_key);
or_res = strcmp(lexeme_compare, or_key);
not_res = strcmp(lexeme_compare, not_key);
length_res = strcmp(lexeme_compare, length_key);

//check results, and see if it found any KEYWORDS or DATATYPE SPECIFIERS or OPERATORS(logic)
if (if_res == 0){
  left_over = c;
  c = -1;
  return TOK_IF;
}
else if (else_res == 0){
  left_over = c;
  c = -1;
  return TOK_ELSE;
}
else if(for_res == 0){
  left_over = c;
  c = -1;
  return TOK_FOR;
}
else if(while_res == 0){
  left_over = c;
  c = -1;
  return TOK_WHILE;
}
else if(print_res == 0){
  left_over = c;
  c = -1;
  return TOK_PRINT;
}
else if(return_res == 0){
  left_over = c;
  c = -1;
  return TOK_RETURN;
}
else if(continue_res == 0){
  left_over = c;
  c = -1;
  return TOK_CONTINUE;
}
else if(break_res == 0){
  left_over = c;
  c = -1;
  return TOK_BREAK;
}
else if(debug_res == 0){
  left_over = c;
  c = -1;
  return TOK_DEBUG;
}
else if(read_res == 0){
  left_over = c;
  c = -1;
  return TOK_READ;
}
else if(let_res == 0){
  left_over = c;
  c = -1;
  return TOK_LET;
}
else if(int_res == 0){
  left_over = c;
  c = -1;
  return TOK_INT;
}
else if(float_res == 0){
  left_over = c;
  c = -1;
  return TOK_FLOAT;
}
else if(string_res == 0){
  left_over = c;
  c = -1;
  return TOK_STRING;
}
else if(and_res == 0){
  left_over = c;
  c = -1;
  return TOK_AND;
}
else if (or_res == 0){
  left_over = c;
  c = -1;
  return TOK_OR;
}
else if(not_res == 0){
  left_over = c;
  c = -1;
  return TOK_NOT;
}
else if(length_res == 0){
  left_over = c;
  c = -1;
  return TOK_LENGTH;
}
//it isn't a keyword, datatype specifier, or logic operator, so it's gotta be an identifier
else{
  if (!isspace(c)){
    left_over = c;
  }
  c = -1;
  return TOK_IDENTIFIER;
}
//deallocate the memory of the lexeme compare string
delete[] lexeme_compare;
}


//test for a NUMBER
if ((int)c > 47 && (int)c <= 57){
  while((int)c > 47 && (int)c <= 57){
    lexeme[yyleng++] = c;
    c = fgetc(yyin);}
  //printf("\n c = %c ... at while loop 1", c);}
    //if its not a number, and not a period, then return its an integer
    if ((int)c <= 45 || (int)c > 57){
      //if we have a left over from the while function, read it on the next iteration
      if(!isspace(c)){
        //printf("PUT %c IN LEFTOVER" , c);
        left_over = c;
      }
      c = -1;
      return TOK_INTLIT;
    }
    //if c is a period, then it's a float
    if ((int)c == 46){
      lexeme[yyleng++] = c;
      c = fgetc(yyin);
      //make sure it's a number, and add it to the float
      while((int)c > 47 && (int)c <= 57){
        lexeme[yyleng++] = c;
        c = fgetc(yyin);
      }
        //if its anything other than a number, return the float
        if ((int)c <= 47 || (int)c > 57){
          // if we have a left over, read it on the next iteration
          if (!isspace(c)){
            left_over = c;
          }
          c = -1;
          //printf("RETURNED A FLOAT\n"); :::::: DEBUG
          return TOK_FLOATLIT;
        }
    }
  }

//test for a string literal
  if (c == '"'){
    //printf("STARTS WITH A QUOTATION"); :::::DEBUG
    lexeme[yyleng++] = c;
    c = fgetc(yyin);
    while(c != '"'){
      lexeme[yyleng++] = c;
      c = fgetc(yyin);
      if(feof(yyin)){
        c = -1;
        return TOK_EOF_SL;
      }
      //just in case the file ends while in a string
    if (c == '"'){
    lexeme[yyleng++] = c;
    c = -1;
    return (TOK_STRINGLIT);
      }
    }
}

//test for newline
if (c == '\n'){
  //printf("RETURNED NEW LINE");            DEBUG
  c = -1;
  return TOK_NEWLINE;
}
if (c == '\r'){
  //printf("CARRIAGE RETURN");              DEBUG
  c = -1;
  return TOK_CARRETURN;
}
if (c == '\f'){
  //printf("FORM FEED");                    DEBUG
  c = -1;
  return TOK_FORMFEED;
}
// Test for end of file
if( feof(yyin) ) {
  // Ready for next time
  c = -1;
  // Done!
  return( TOK_EOF );
}
  // Store current character and read the next
  lexeme[yyleng++] = c;
  c = fgetc( yyin );

  // We don't yet know how to recognize any lexemes
  return( TOK_UNKNOWN );
}
