Protocole Babel
===============

Le protocole BABEL est un protocole binaire, développé sur des systèmes utilisant le protocole réseau UDP et TCP.
Le BABEL est un système d'audioconférence multiplateforme qui (grâce à l'utilisation d'un modèle client/serveur) est adapté à une exécution sur de nombreuses machines, de façon distribuée. Une configuration type comprend un processus unique (le serveur) qui fournit un point d'accès pour les clients, leur permettant d'obtenir les informations nécessaires à leurs connexions.

Serveur
=======

Il agit comme un nœud central sur lequel chaque client doit obligatoirement s'enregistrer. Il permet de faire le relais entre sa base de données, contenant les informations sur l'intégralité des clients, et les clients eux-mêmes.


Clients
=======

Est un client tout ce qui se connecte à un serveur et qui n'est pas un serveur.
Chaque client se différencie des autres par un pseudonyme unique, d'une longueur maximal de trente caractères.


Protocole
=========

* Le jeu de caracteres autorisés : US-ASCII
Les messages du protocole doivent être extraits du flux continu d'octets. La solution actuelle consiste à désigner deux caractères donnés, CR et LF, comme séparateurs de messages. Les messages vides sont ignorés en silence, ce qui permet l'usage d'une suite de CR-LF entre les messages sans problèmes supplémentaires.

Format des messages
-------------------
<MESSAGE> ::= <COMMAND> <PARAM> <CRLF>
<COMMAND> ::= [A-Z]*
<PARAM>	  ::= [A-Z] <ESAPCE> [A-Z]+
<ESPACE>  ::= [' ']
<CRLF>	  ::= ["CR" + "LF"]

Note : <ESPACE> ne peut être constitué que du caractère ASCII '0x20'.

Commandes 'CL_' (relatives aux clients)
------------------------------------

### CL_REGISTER <login> <mot de passe>

La commande CL_REGISTER est utilisée pour enregistrer un nouveau client. Le mot de passe doit être défini avant toute tentative de connexion. Il n'est pas possible d'envoyer plusieurs commandes CL_REGISTER avant de s'enregistrer.

Réponses numériques : ERR_NEEDMOREPARAMS, ERR_ALREADYREGISTERED, OK

### CL_LOGIN <login> <mot de passe> <host>

La commande CL_LOGIN est utilisée pour connecter un client déjà enregistré. Le message CL_LOGIN est utilisé au début d'une connexion pour spécifier le login d'utilisateur.

Réponses numériques : ERR_NEEDMOREPARAMS, ERR_NOTREGISTRED, OK

### CL_INFO [login]

La commande CL_INFO est utilisée pour récupérer des informations sur un ou plusieurs clients connectés sur le serveur. Si aucun paramètre n'est passé alors le serveur envoie les infos de tous les clients connectés. S'il y a un paramètre alors il envoie les informations du login passé en paramètre.

Réponses numériques : ERR_UNKNOWNKNLOGIN

### CL_UPDATE <login>

_ramnes: commande inutile, si il y a une update à faire, le serveur envoie directement un CL_INFO <login du client en question> à tout les autres clients

La commande CL_UPDATE est utilisée pour que le serveur fasse savoir au client qu'il y a des données à mettre à jour pour sa base (changement d'état, nouveau client connecté ...) Le client répondra par GET_INFO suivi du login passé en paramètre.

### CL_QUIT

Une session de client se termine par un message QUIT. Le serveur doit rompre la connexion avec le client qui envoie un message QUIT. Si pour une autre raison une connexion d'un client est fermée sans que le client ait envoyé de message QUIT, (par exemple, le programme client se termine, et une fin de fichier est envoyée sur le socket), le serveur doit rompre la connexion avec ce client et le signaler aux autres. Si le client envoie QUIT alors qu'il est en communication il doit d'abord mettre fin à cette communication.

Réponses numériques : OK_QUITDONE, ERR_CALLING

Commandes 'SV_' (relatives au serveur)
-----------------------------------

### SV_END

Le message SV_END est nécessaire pour signaler le départ ou la mort du serveur. Si un serveur souhaite rompre une connexion il doit envoyer un message SV_END ce qui clôt la connexion, quittant le réseau.

Commandes 'C_' (relatives au appels)
---------------------------------

Lors de l'établissement d'une connexion client / client, tous les messages doivent passer par le serveur qui se charge de transmettre les informations.

### C_CALL <login>

Le message C_CALL est utilisé lorsqu'un client souhaite initialiser une conférence audio avec un autre client connecté. Il envoie C_CALL <login à appeler> au serveur, qui va transmettre au login passé en paramètre C_CALL <login appelant>.
Avant d'envoyer ce message le client doit initialiser ses deux sockets, si rien n'a échoué alors il peut envoyer le message.

Réponses numériques : ERR_NOSUCHLOGIN

### C_ACCEPT [login]

Le message C_ACCEPT est utilisé lorsqu'un client souhaite accepter l'invitation d'un autre client à une conférence. Il envoie C_ACCEPT <login appelant> au serveur, qui va transmettre C_ACCEPT au login passé en paramètre.
Avant d'envoyer ce message le client doit initialiser ses sockets, si rien n'a échoué alors il peut envoyer le message.
Le serveur quant à lui doit transmettre C_ACCEPT sans paramètre.
Une fois que le client a reçu C_ACCEPT sans paramètre il connecte ses sockets afin de commencer la connexion.

Réponses numériques : ERR_NOSUCHLOGIN

### C_REFUSE [login]

Le message C_REFUSE est utilisé lorsqu'un client souhaite refuser l'invitation d'un autre client à une conférence. Il envoie C_REFUSE <login appelant> au serveur, qui va transmettre au login passe en paramètre.
Le serveur quant à lui doit transmettre C_REFUSE sans le paramètre.
Une fois que le client a reçu C_REFUSE sans paramètre, il déconnecte ses sockets.

Réponses numériques : ERR_NOSUCHLOGIN

### C_END <login>

Le message C_END est utilisé lorsqu' un client souhaite mettre un terme a une conférence. Il envoie C_END <login appelant> au serveur qui va transmettre au login passe en paramètre.
Le serveur quant à lui doit transmettre C_END sans le paramètre.
Une fois que le client a reçu C_END sans paramètre il déconnecte ses sockets et met fin à la connexion.

Réponses numériques : ERR_NOSUCHLOGIN
