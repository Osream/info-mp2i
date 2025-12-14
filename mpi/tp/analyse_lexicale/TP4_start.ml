type token = CONST of int | EOF | PARG | PARD 
   | PLUS | FOIS | DIV | MOINS

exception Lexical_error

type op = Plus | Moins | Fois | Div
type arbreSyntaxe = Const of int
                  | Bin of arbreSyntaxe * op * arbreSyntaxe
                  | Neg of arbreSyntaxe

exception Syntax_error

let ch1 = "((-75+9) * (7- 9))"

let ch1_token = [
   PARG;
   PARG;
   MOINS;
   CONST 75;
   PLUS;
   CONST 9;
   PARD;
   FOIS;
   PARG;
   CONST 7;
   MOINS;
   CONST 9;
   PARD;
   PARD;
   EOF
]

let print_token t =
   match t with
   |PARG -> print_string "(; "
   |PARD -> print_string "); "
   |PLUS -> print_string "+; "
   |MOINS -> print_string "-; "
   |FOIS -> print_string "*; "
   |DIV -> print_string "/; "
   |CONST k -> print_int k; print_string "; "
   |EOF -> ()

let print_lex l =
   print_string "[";
   List.iter print_token l;
   print_string "]\n"

(*
let get_number str i =
   let res = ref 0 
   and j = ref i in
   while (int_of_char str.[!j] >= 48) && (int_of_char str.[!j] <= 57) do
      res := !res*10 + (int_of_char str.[!j] - 48);
      incr j
   done;
   (CONST !res, !j-1)

let first_token str i =
   let res = ref EOF 
   and indx_res = ref i in
   if i = String.length str then
      (!res, !indx_res)
   else if String.length str < i then
      raise Lexical_error
   else if (int_of_char str.[i] >= 48) && (int_of_char str.[i] <= 57) then
      get_number str i
   else
      try
         for j = i to String.length str - 1 do
            indx_res := j;
            match str.[j], !res with
            | '(', EOF -> res := PARG
            | ')', EOF -> res := PARD
            | '+', EOF -> res := PLUS
            | '-', EOF -> res := MOINS
            | '*', EOF -> res := FOIS
            | '/', EOF -> res := DIV 
            | ' ', EOF -> ()
            | '\n', EOF -> ()
            | '\t', EOF -> ()
            | ' ', _ -> raise Exit
            | '\n', _ -> raise Exit
            | '\t', _ -> raise Exit
            | _, _ -> raise Exit
         done;
         raise Exit
      with
         | Exit ->  print_int (!indx_res-1); (!res, !indx_res-1)
         | Lexical_error -> raise Lexical_error

let lexer s = 
   let taille = String.length s in
   let rec parcours_aux str i acc= 
      print_int i;
      print_newline ();
      match (first_token str i) with
      | EOF, t when t = taille -> acc@[EOF]
      | _, t when t = taille -> raise Lexical_error
      | lex, indx -> (parcours_aux str (indx+1) (acc@[lex]))
   in
   let res = parcours_aux s 0 [] in
   res
*)

let rec parserE t_lst =
   match t_lst  with
   | [] -> raise Syntax_error
   | t::q -> match t with
            | PARG -> parserB t_lst
            | CONST n -> Const n, q
            | MOINS -> let abr, suite = parserE q in Neg abr, suite
            | _ -> raise Syntax_error
and parserB t_lst =
   match t_lst with
   | [] -> raise Syntax_error
   | t::q -> let abrg, suite_tmp1 = parserE q in 
               let op, suite_tmp2 = parserO suite_tmp1 in 
               let abrd, suite = parserE suite_tmp2 in
               Bin (abrg, op, abrd), List.tl suite
and parserO t_lst =
   match t_lst  with
   |[] -> raise Syntax_error
   | t::q -> match t with
            | PLUS -> Plus, q
            | MOINS -> Moins, q
            | FOIS -> Fois, q
            | DIV -> Div, q
            | _ -> raise Syntax_error

let parser t_lst =
   let abr, suite =parserE t_lst in
   match suite with
   | [EOF] -> abr
   | _ -> raise Syntax_error

let operation (operant : op) n p =
   match operant with
   | Plus -> n + p
   | Moins -> n - p
   | Fois -> n * p
   | Div -> n / p

(*let evaluation str = (*Cette fonction doit finir mais la fonction first token ne fonctionne pas*)*)