//*****************************************************************************
// purpose: CSE 4713 / 6713 Assignment 1: Lexical Analyzer
//          Driver code
// created: 8-25-2015
//  author: J. Edward Swan II
//
// edited: 2/6/2019
// edited by: Jason McQueen
//*****************************************************************************
#include "lexer.h"

// Instantiate global variables
FILE *yyin;         // input stream
FILE *yyout;        // output stream
int   yyleng;       // length of current lexeme
char *yytext;       // text of current lexeme

// Do the analysis
int main( int argc, char* argv[] )
{
  int token;   // hold each token code
  // Set the input and output streams
  yyin = stdin;
  yyout = stdout;

  // Do the lexical parsing
  token = yylex();
  while( token != TOK_EOF )
  {
    //if token is not equal to a newline, form feed, or carriage return
    if(token != TOK_NEWLINE && token != TOK_FORMFEED && token != TOK_CARRETURN){
    // What did we find?
    printf("lexeme: |%s|, length: %d, token: %d\n", yytext, yyleng, token);
    // Is it an error?
    if( token == TOK_UNKNOWN )
      printf("   ERROR: unknown token\n");
    if( token == TOK_EOF_SL )
      printf("   ERROR: end of file while in a string literal\n");
    }
    // Get the next token
    token = yylex();
  }
}
