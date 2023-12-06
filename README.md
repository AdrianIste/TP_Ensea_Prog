# TP_Ensea_Prog

1. Read and Write
La fonction read permet de lire dans la console si on passe par la sortie standard "STDOUT_FILENO", on y associe un nombre d'octets maximum et elle renverra un entier qui est le nombre d'octets lus et écrit la chaîne de caractère dans le deuxième argument. On doit bien faire attention à supprimer le dernier caractère qui correspond à la touche "entrée" sinon on ne pourra pas exécuter la commande écrite

la fonction write permet d'écrire dans le terminal si on prend la sortie standard (STDOUT_FILENO), elle renvoie aussi un entier qui est le nombre de bits écrits. On doit aussi lui donner en argument le nombre de bites à écrire.

2.fork()

fork duplique le processus père et crée un processus fils afin de pouvoir travailler sur plusieurs CPU à la fois. on peut savoir dans que processus on se trouve en récupérant l'entier ret (si int ret=fork) alors si ret==0, on est dans le processus fils, si ret<0 il y a une erreur et sinon on se trouve dans le processus père.

wait(&status) permet d'attendre que le processus fils se termine et d'écrire dans statut un code qui explique comment s'est terminé le processus fils.

3.ctrl+D

ctrl+D envoie un signal "end of file" qui lorqu'il est lu, vaut 0 octets, c'est ainsi qu'on le détecte.

4. Identification de la fin du processus "child"
A l'aide des fonction WIFEXITED,WEXITSTATUS,WIFSIGNALED, et WTERMSIG, on peut récupérer l'information précise via (status) de comment s'est terminé le processus enfant.

5. strtok
C'est à l'aide de la fonction strtok (voir man2 strtok) qu'on peu séparer une commande en plusieurs arguments et ainsi exécuter des commandes complexes dans le shell.

6.Récupérer le temps

A l'aide de la librairie time.h, on peut mesurer un temps d'exécution : clock_gettime(clk_id, struct) permet d'enregistrer le temps de la clock choisie dans la struct (adéquate), on peut ensuire récupérer ces informations.
