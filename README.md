# miniShell
un shell en plus petit (mini)

Le projet Minishell a pour but de créer un shell avec quelques commandes et fonctionnement de bash posix.
Toutes les commandes sont disponible, mais seul echo, cd, pwd, export, unset, env et exit ont été recréer par nos soins.
Les heredocs, les redirections, les signaux ou encore les variables d'environnement sont disponible.

Les difficultés était de recréer le plus fidelement certain comportements (dans les heredocs par exemple) là oú nous n'avions pas d'idée du comportement de base.

Si vous rencontrez des soucis dans la compilation, assurez vous que la librairie 'readline' soit bien installée.
Sinon :
```
sudo apt-get install libreadline8
sudo apt-get install libreadline-dev
```
ou sur OSX :
```
brew install readline
```

Tout le projet a été fait avec Xavier Challe (xchalle).
