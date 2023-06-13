## Fixed:
* InsertBefore() does not return EXIT_SUCCESS when completing successfully
* InsertBefore() does not increment counter
* PrintList breaks upon an empty list being passed through
* Memory is never freed in text_program.c

## Unaddressed:
* InsertBefore() causes the program to crash, cause is currently unknown, upon viewing code there are likely multiple reasons
* Very small memory leak is occurring, not sure of the cause
