
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM_ENTERO = 258,
     NUM_REAL = 259,
     CHAR = 260,
     ERROR_LEXICO = 261,
     OTROS = 262,
     ID = 263,
     LIT_CADENA = 264,
     TIPO_DATO = 265,
     IF = 266,
     DEFAULT = 267,
     ELSE = 268,
     WHILE = 269,
     DO = 270,
     SWITCH = 271,
     BREAK = 272,
     CASE = 273,
     FOR = 274,
     GOTO = 275,
     CONTINUE = 276,
     RETURN = 277,
     IGUALDAD = 278,
     ASIGNACION_INCREMENTO = 279,
     AND = 280,
     OR = 281,
     DISTINTO = 282,
     MAYOR_IGUAL = 283,
     MENOR_IGUAL = 284,
     INCREMENTO = 285,
     DECREMENTO = 286
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 28 "../src/TP4.y"

   struct mytruct
   {
        int tipo;
        int entero;
        float real;
        char* cadena;
        char caracter;
   } mystruct;




/* Line 1676 of yacc.c  */
#line 97 "TP4.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


