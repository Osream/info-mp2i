type token = CONST of int | EOF | PARG | PARD | PLUS | FOIS | DIV | MOINS

exception Lexical_error

type op = Plus | Moins | Fois | Div

type arbreSyntaxe =
    Const of int
  | Bin of arbreSyntaxe * op * arbreSyntaxe
  | Neg of arbreSyntaxe

exception Syntax_error

val ch1 : string

val print_token : token -> unit

val print_lex : token list -> unit
