type 'a file = 'a Queue.t
        
let creer () =
    Queue.create ()
        
let est_vide f =
    Queue.is_empty f
        
let emfiler elt f =
    Queue.push elt f
        
let defiler f =
    assert (not (est_vide f));
    Queue.pop f

