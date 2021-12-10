/bin/ls
m_test.c
microshell
microshell.c
microshell.dSYM
microshell_01.c
microshell_02.c
microshell_03.c
out.res
subject.en.txt
subject.fr.txt
test.sh

/bin/cat microshell.c
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
//#include <stdio.h>

#define STDIN		0
#define STDOUT		1

typedef struct s_cmd {
	char    **args;
	int      pipe[2];
	int      prev_pipe;
	int      type[2];
}	t_cmd;

int strl(const char *str)
{
	int i = 0;
	while (str && str[i++]);
	return (--i);
}

void fatal()
{
	write(2, "error: fatal\n", strl("error: fatal\n"));
	exit(1);
}

void   exec_cmd(t_cmd *list, char **envp)
{
	pid_t  pid;
 	int       ex;

 	if ((list->type[1] == 1 || list->type[0] == 1) && (pipe(list->pipe)))
  		fatal();
	if ((pid = fork()) < 0)
		fatal();
	if (pid == 0)
 	{
 		if ((list->type[1] == 1) && (dup2(list->pipe[1], 1)) < 0)
			fatal();
		if ((list->type[0] == 1) && (dup2(list->prev_pipe, 0)) < 0)
			fatal();
		if ((ex = execve(list->args[0], list->args, envp)) < 0)
		{
			write(2, "error: cannot execute ", 22);
			write(2, list->args[0], strl(list->args[0]));
			write(2, "\n", 1);
		}
		exit(ex);
	}
	else
 	{
  		waitpid(pid, 0, 0);
 		if (list->type[1] == 1 || list->type[0] == 1)
  		{
   			close(list->pipe[1]);
   			if (list->type[1] != 1)
    			close(list->pipe[0]);
  		}
  		if (list->type[0] == 1)
   			close(list->prev_pipe);
 	}
}

int list_len(t_cmd *list, int start, char **argv){
	int end;
	int len;

	end = start;
 	while (argv[end] && strcmp(argv[end], ";") && strcmp(argv[end], "|"))
  		end++;
	len = end - start;
	if (len > 0)
	{ //      /bin/ls ; /bin/echo kak dela | /bin/cat -e
 		list->args = &argv[start];
  		list->type[0] = list->type[1];
		if (!argv[end])
			list->type[1] = 0;
  		else if (!strcmp(argv[end], "|"))
			list->type[1] = 1;
  		else
   			list->type[1] = 2;// ";"
 		argv[end] = NULL; //null for last row of 2d array
  		list->prev_pipe = list->pipe[0];
 	}
 	return (end);
}
int main(int argc, char **argv, char **envp) {
	t_cmd list;
	int  i;
	int  start;

	i = 0;
  	while (i < argc && argv[++i])
	{
   		start = i;
   		i = list_len(&list, i, argv);
   		if (!strcmp(argv[start], "cd"))
		{
	   		if (i - start != 2)
    			 write(2, "error: cd: bad arguments\n", strl("error: cd: bad arguments\n"));
			else if (chdir(list.args[1]) == -1)
    		{
				write(2, "error: cd: cannot change directory to ", strl("error: cd: cannot change directory to "));
				write(2, list.args[1], strl(list.args[1]));
				write(2, "\n", 1);
			}
		}
		else if (i > start)
			exec_cmd(&list, envp);
		// write(1, "\n", 1);
	}
	return 0;
}
/bin/ls microshell.c
microshell.c

/bin/ls salut

;

; ;

; ; /bin/echo OK
OK

; ; /bin/echo OK ;
OK

; ; /bin/echo OK ; ;
OK

; ; /bin/echo OK ; ; ; /bin/echo OK
OK
OK

/bin/ls | /usr/bin/grep microshell
microshell
microshell.c
microshell.dSYM
microshell_01.c
microshell_02.c
microshell_03.c

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro
microshell
microshell.c
microshell.dSYM
microshell_01.c
microshell_02.c
microshell_03.c

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro
microshell
microshell.c
microshell.dSYM
microshell_01.c
microshell_02.c
microshell_03.c

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell
microshell
microshell.c
microshell.dSYM
microshell_01.c
microshell_02.c
microshell_03.c

/bin/ls ewqew | /usr/bin/grep micro | /bin/cat -n ; /bin/echo dernier ; /bin/echo
dernier


/bin/ls | /usr/bin/grep micro | /bin/cat -n ; /bin/echo dernier ; /bin/echo ftest ;
     1	microshell
     2	microshell.c
     3	microshell.dSYM
     4	microshell_01.c
     5	microshell_02.c
     6	microshell_03.c
dernier
ftest

/bin/echo ftest ; /bin/echo ftewerwerwerst ; /bin/echo werwerwer ; /bin/echo qweqweqweqew ; /bin/echo qwewqeqrtregrfyukui ;
ftest
ftewerwerwerst
werwerwer
qweqweqweqew
qwewqeqrtregrfyukui

/bin/ls ftest ; /bin/ls ; /bin/ls werwer ; /bin/ls microshell.c ; /bin/ls subject.fr.txt ;
leaks.res
m_test.c
microshell
microshell.c
microshell.dSYM
microshell_01.c
microshell_02.c
microshell_03.c
out.res
subject.en.txt
subject.fr.txt
test.sh
microshell.c
subject.fr.txt

/bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ;
microshell
microshell.c
microshell.dSYM
microshell_01.c
microshell_02.c
microshell_03.c
microshell
microshell.c
microshell.dSYM
microshell_01.c
microshell_02.c
microshell_03.c
microshell
microshell.c
microshell.dSYM
microshell_01.c
microshell_02.c
microshell_03.c
microshell
microshell.c
microshell.dSYM
microshell_01.c
microshell_02.c
microshell_03.c

/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b ; /bin/cat subject.fr.txt ;
Ecrire un programme qui aura ressemblera à un executeur de commande shell
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'argument votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.
N'oubliez pas de passer les variables d'environment à execve
Assignment name  : microshell
Expected files   : *.c *.h
Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
--------------------------------------------------------------------------------------

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'argument votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n' avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' et sortir
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.

Par exemple, la commande suivante doit marcher:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Conseils:
N'oubliez pas de passer les variables d'environment à execve

Conseils:
Ne fuitez pas de file descriptor!
/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep w ; /bin/cat subject.fr.txt ;
Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
Assignment name  : microshell
Expected files   : *.c *.h
Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
--------------------------------------------------------------------------------------

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'argument votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n' avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' et sortir
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.

Par exemple, la commande suivante doit marcher:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Conseils:
N'oubliez pas de passer les variables d'environment à execve

Conseils:
Ne fuitez pas de file descriptor!
/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep w ; /bin/cat subject.fr.txt
Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
Assignment name  : microshell
Expected files   : *.c *.h
Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
--------------------------------------------------------------------------------------

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'argument votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n' avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' et sortir
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.

Par exemple, la commande suivante doit marcher:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Conseils:
N'oubliez pas de passer les variables d'environment à execve

Conseils:
Ne fuitez pas de file descriptor!
/bin/cat subject.fr.txt ; /bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b | /usr/bin/grep z ; /bin/cat subject.fr.txt
Assignment name  : microshell
Expected files   : *.c *.h
Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
--------------------------------------------------------------------------------------

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'argument votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n' avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' et sortir
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.

Par exemple, la commande suivante doit marcher:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Conseils:
N'oubliez pas de passer les variables d'environment à execve

Conseils:
Ne fuitez pas de file descriptor!N'oubliez pas de passer les variables d'environment à execve
Assignment name  : microshell
Expected files   : *.c *.h
Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
--------------------------------------------------------------------------------------

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'argument votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n' avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' et sortir
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.

Par exemple, la commande suivante doit marcher:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Conseils:
N'oubliez pas de passer les variables d'environment à execve

Conseils:
Ne fuitez pas de file descriptor!
; /bin/cat subject.fr.txt ; /bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b | /usr/bin/grep z ; /bin/cat subject.fr.txt
Assignment name  : microshell
Expected files   : *.c *.h
Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
--------------------------------------------------------------------------------------

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'argument votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n' avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' et sortir
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.

Par exemple, la commande suivante doit marcher:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Conseils:
N'oubliez pas de passer les variables d'environment à execve

Conseils:
Ne fuitez pas de file descriptor!N'oubliez pas de passer les variables d'environment à execve
Assignment name  : microshell
Expected files   : *.c *.h
Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
--------------------------------------------------------------------------------------

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'argument votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n' avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' et sortir
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.

Par exemple, la commande suivante doit marcher:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Conseils:
N'oubliez pas de passer les variables d'environment à execve

Conseils:
Ne fuitez pas de file descriptor!
blah | /bin/echo OK
OK

blah | /bin/echo OK ;
OK

