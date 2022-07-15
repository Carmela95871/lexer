#include "Token.h"

typedef struct Lexer_Structure
{
    unsigned char c;
    unsigned int i, len;
    const char *contents;

} Lexer_T;

Lexer_T *init_Lexer(const char *contents);
void Lexer_Advance(Lexer_T *lexer);
Token_T *Lexer_Get_Next_Token(Lexer_T *lexer);
Token_T *Lexer_Collect_Single_Char(Lexer_T *lexer, int token_type);
Token_T *Lexer_Collect_String(Lexer_T *lexer);
Token_T *Lexer_Collect_Number(Lexer_T *lexer);
Token_T *Lexer_Collect_Name(Lexer_T *lexer);
