#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "include/Token.h"
#include "include/Tokenizer.h"

Token_T *init_Token(int token, char *value)
{
    Token_T *tok = calloc(1, sizeof(sizeof *tok));
    tok->Token_Type = token;
    tok->Token_Value = value;

    return tok;
}

const char *token_type(int type)
{
    switch (type)
    {
    case PLUS: return "PLUS";
    case NAME: return "NAME";
    }
}

Lexer_T *init_Lexer(const char *contents)
{
    Lexer_T *lexer = calloc(1, sizeof(struct Lexer_Structure));
    lexer->contents = contents;
    lexer->len = strlen(contents);
    lexer->i = 0;
    lexer->c = contents[lexer->i];

    return lexer;
}

void Lexer_Advance(Lexer_T *lexer)
{
    if (lexer->i < lexer->len)
    {
        lexer->i += 1;
        lexer->c = lexer->contents[lexer->i];
    }
}

Token_T *Lexer_Collect_Single_Char(Lexer_T *lexer, int token_type)
{
    char *str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';
    Lexer_Advance(lexer);

    return init_Token(token_type, str);
}

Token_T *Lexer_Collect_String(Lexer_T *lexer)
{
    char *value = calloc(1, sizeof(char));
    unsigned int len = 0;

    Lexer_Advance(lexer);
    while (lexer->c != '\0' && lexer->c != '"')
    {
        value = realloc(value, (len + 1) * sizeof(char));
        value[len++] = lexer->c;
        Lexer_Advance(lexer);
    }
    value[len] = '\0';
    if (lexer->c == '"')
        Lexer_Advance(lexer);

    return init_Token(STRING, value);
}

Token_T *Lexer_Collect_Name(Lexer_T *lexer)
{
    char *value = calloc(1, sizeof(char));
    unsigned int len = 0;

    while (isalnum(lexer->c) || lexer->c == '_')
    {
        value = realloc(value, (len + 1) * sizeof(char));
        value[len++] = lexer->c;
        Lexer_Advance(lexer);
    }
    value[len] = '\0';

    return init_Token(NAME, value);
}

Token_T *Lexer_Collect_Number(Lexer_T *lexer)
{
    char *value = calloc(1, sizeof(char));
    unsigned int len = 0;

    while (isdigit(lexer->c) || lexer->c == '.')
    {
        value = realloc(value, (len + 1) * sizeof(char));
        value[len++] = lexer->c;
        Lexer_Advance(lexer);
    }
    value[len] = '\0';

    return init_Token(NUMBER, value);
}

Token_T *Lexer_Get_Next_Token(Lexer_T *lexer)
{
    while (lexer->c != 0)
    {
        if (lexer->c == ' ' || lexer->c == '\n')
        {
            Lexer_Advance(lexer);
            continue;
        }
        if (isalpha(lexer->c) || lexer->c == '_')
            return Lexer_Collect_Name(lexer);

        if (isdigit(lexer->c))
            return Lexer_Collect_Number(lexer);

        if (lexer->c == '"')
            return Lexer_Collect_String(lexer);

        switch (lexer->c)
        {
        case '+': return Lexer_Collect_Single_Char(lexer, PLUS);
        }
    }

    return (void *)0;
}

int main(int argc, char *argv[])
{
    Lexer_T *lexer = init_Lexer("a + b");
    Token_T *token = (void *)0;

    while ((token = Lexer_Get_Next_Token(lexer)) != (void *)0)
    {
        printf("LexToken(%s, '%s')\n", token_type(token->Token_Type), token->Token_Value);
    }

    return 0;
}
