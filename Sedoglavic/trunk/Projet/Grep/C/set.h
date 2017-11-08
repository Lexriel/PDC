int     addtoset          (set_t **,NODE *) ;
int     recursiveaddtoset (set_t **, set_t *) ;
set_t * copy_set          (set_t *) ;
set_t * create_set        (NODE *) ;
set_t * cup               (set_t *, set_t *) ;
set_t * nextunmarkedstate (set_t *set) ;
void    delete_set        (set_t *) ;

/* cup return a set that is the merge of its argument.
 * cells are copyed
 */
