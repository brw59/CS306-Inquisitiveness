(* Does an insertion sort on `alist` *)
let rec isort alist = 
   match alist with
   | []         -> []
   | head::tail -> insert head (isort tail)

(* a function that inserts item in the proper place *)
and insert item alist =
   match alist with
   | []         -> [item]
   | head::tail ->
      if item <= head then
         item :: alist
      else
         head :: insert item tail (* Note: recursively traverses the list till it reaches a place to insert it *)
;; 

(*

let print_int_space i =
   print_string (string i) ^ " " (* need a way to convert an int to a string*)
;;
*)

let print_int_space i =
   print_int i;
   print_string " ";;

print_string "This is an insertion sort\n";;


print_string "\n from: \t";;

List.map (print_int_space) [9; 4; 6; 7; 5; 1];;


print_string "\n to: \t";;

List.map (print_int_space) (isort [9; 4; 6; 7; 5; 1]);;


