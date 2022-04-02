# FT_IRC

Ce projet a pour but de recréer un serveur IRC simple.

## To-Do list

 - [X] Pouvoir s'authentifier
 - [X] Pouvoir définir un nickname
 - [X] Pouvoir définir un username
 - [X] Pouvoir rejoindre un channel
 - [X] Envoyer des messages privés
 - [X] Recevoir des messages privés
 - [ ] Avoir des utilisateurs "operator"
 - [ ] Implémenter les commandes spécifiques aux operators
  - [ ] KILL
  - [ ] OPER

### Plus spécifiquement
 - [ ] Gerer propremement les deconnexions, notamment avec la commande QUIT
 - [X] Utiliser le retour de la fonction erase pour ne plus avoir besoin de la boucle de disconnect dans processClientActivity
