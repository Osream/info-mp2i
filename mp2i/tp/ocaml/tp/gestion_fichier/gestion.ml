let copie10 pathin pathout=
  let file_to_read = open_in pathin and file_to_write = open_out pathout in
  for i = 0 to 9 do
    output_string file_to_write (input_line file_to_read);
    output_string file_to_write "\n"
  done;
  close_in file_to_read;
  close_out file_to_write

let copie pathin pathout =
  try
    let file_to_read = open_in pathin and file_to_write = open_out pathout in
    try
      while true do
        output_string file_to_write (input_line file_to_read);
        output_string file_to_write "\n"
      done
    with End_of_file -> close_in file_to_read;
    close_out file_to_write
  with Sys_error pathin -> output_string stderr "Ce fichier n'est pas accessible.\n"

let serialise_pile stc file= 
  try
    let file_to_write = open_out file in
    let tmp = Stack.create () in
    while not(Stack.is_empty stc) do 
      let value = Stack.pop stc in
      output_string file_to_write (string_of_int value);
      output_string file_to_write "\n";
      Stack.push value tmp
    done;
    while not(Stack.is_empty tmp) do 
      Stack.push (Stack.pop tmp) stc
    done;
    close_out file_to_write
  with Sys_error file -> output_string stderr "Ce fichier n'est pas accessible.\n"

let deserialise_pile file = 
  let tmp = Stack.create () and res = Stack.create () in
  let file_to_read = open_in file in
  try
    while true do
        let value = input_line file_to_read in
      Stack.push (int_of_string value) tmp
    done
  with End_of_file -> 
  close_in file_to_read;
  while not(Stack.is_empty tmp) do
    Stack.push (Stack.pop tmp) res
  done;
  res
 
  

let _ =
  let pile = Stack.create () in
  Stack.push 2 pile;
  Stack.push 3 pile;
  Stack.push 4 pile;
  serialise_pile pile Sys.argv.(1)