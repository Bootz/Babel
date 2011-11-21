Protocole Babel
===============

Le protocole BABEL est un protocole binaire, développé sur des systèmes
utilisant le protocole réseau UDP et TCP.

Le BABEL est un système d'audio-conférence multiplateforme qui (grâce à
l'utilisation d'un modèle client/serveur) est adapté à une exécution sur de
nombreuses machines, de façon distribuée. Une configuration type comprend un
processus unique (le serveur) qui fournit un point d'accès pour les clients,
leur permettant d'obtenir les informations nécessaires à leurs connexions.

Serveur
=======

Il agit comme un nœud central sur lequel chaque client doit obligatoirement
s'enregistrer. Il permet de faire le relais entre sa base de données,
contenant les informations sur les clients.


Clients
=======

Est un client tout ce qui se connecte à un serveur et qui n'est pas un
serveur.
Chaque client se différencie des autres par un pseudonyme unique, d'une
longueur maximal de trente caractères.


Protocole
=========

Le jeu de caractères reconnu est `US-ASCII`.

Les messages du protocole doivent être extraits du flux continu d'octets.
La solution actuelle consiste à désigner deux caractères donnés, CR et LF,
comme séparateurs de messages. Les messages vides sont ignorés en silence,
ce qui permet l'usage d'une suite de CR-LF entre les messages sans problèmes
supplémentaires.

Format des messages
-------------------

    <MESSAGE>	::= <COMMAND> <PARAM> <CRLF>
    <COMMAND>	::= [A-Z]*
    <PARAM>	::= [A-Z] <ESPACE> [A-Z]+
    <ESPACE>	::= [' ']
    <CRLF>	::= ["CR" + "LF"]

Note : `<ESPACE>` ne peut être constitué que du caractère ASCII `0x20`.

Commandes `CL_`
---------------

(`CL_` == **CL**ient: commandes relatives aux actions globales du clients)

### `CL_REGISTER <login> <mot de passe>`

Permet de s'enregistrer sur le serveur maître avec un nom d'utilisateur et un
mot de passe.

### `CL_LOGIN <login> <mot de passe>`

Permet de s'authentifier vis-à-vis du serveur.

### `CL_INFO [login1] [login2] [...]`

Permet de récupérer des informations sur un ou plusieurs clients.

Le serveur envois les informations de chaque client passé en paramètre.
Si aucun paramètre, le serveur envoie les infos de tous les clients connectés.

### `CL_QUIT`

Permet de quitter le serveur (se déconnecter).

Le serveur rompt la connexion avec le client.
Si la  connexion d'un client est fermée sans que le client ait envoyé `CL_QUIT`,
(par exemple, le programme client se termine, et une fin de fichier est envoyée
sur le socket), le serveur doit rompre la connexion avec ce client et le
signaler aux autres.

Commandes `CC_`
---------------

(`CC_` == **C**lient**C**all : commandes relatives aux actions d'appel du
client)

### `CC_CALL <login>`

Initialise une conférence audio avec un autre client connecté.

Le serveur qui va transmettre au login passé en paramètre un `CC_INCOMING`.

### `CC_ACCEPT <login>`

Accepter l'invitation d'un autre client à une conférence.
Est aussi utilisé pour reprendre un appel en attente.

Le serveur envoie alors un `CC_ACCEPTED` à l'appelant.
Avant d'envoyer ce message le client doit initialiser ses sockets ; à la
reception du `CC_ACCEPTED`, l'appelant se connecte.

### `CC_REFUSE <login>`

Permet de refuser l'invitation d'un autre client à une conférence.

Il envoie `CC_REFUSE <login appelant>` au serveur, qui va transmettre au login
passe en paramètre. Le serveur répond `CC_REFUSED` à l'appelant.

### `CC_WAIT <login>`

Met en attente un appel.

Il peut être utilisé à la reception de l'appel ou en plein milieu, et transmet
un `CC_PENDING` à l'autre client.

### `CC_END <login>`

Met un terme a une conférence.

Le serveur lance un `CC_ENDED` à l'autre client.
Une fois que le client a reçu `CC_ENDED` il déconnecte ses sockets et met fin à
la connexion.

Commandes `CI_` (serveur)
-------------------------

(`CI_` = **C**alls**I**nfo) 

### `CI_INCOMING <login>`

Le serveur prévient le client que <login> essaye de le joindre.

### `CI_PENDING <login>`

Le serveur prévient le client que <login> a mis en attente son appel.

### `CI_ENDED <login>`

Le serveur prévient le client que <login> a raccroché.

### `CI_ACCEPTED <login>`

Le serveur prévient le client que <login> a accepté un appel de sa part.

### `CI_REFUSED <login>`

Le serveur prévient le client que <login> a refusé son appel.

Commandes `SV_` (serveur)
-------------------------

### `SV_END`

Le message `SV_END` est nécessaire pour signaler le départ ou la mort du serveur.
Si un serveur souhaite rompre une connexion il doit envoyer un message `SV_END`
ce qui clôt la connexion, quittant le réseau.

Réponses numériques
-------------------

(Très largement inspiré des codes HTTP/SIP.)  
Envoyées par le serveur en réponse aux requètes des clients.

__1xx__ *Informations* 	    -- la requête a été reçue, en attente de traitement  
__2xx__ *Succès* 	    -- la requête a été reçue, comprise et acceptée  
__3xx__ *Redirection* 	    -- d'autres actions sont nécessaires pour compléter la requête  
__4xx__ *Erreurs client*    -- la requête envoyée n'est pas valide  
__5xx__ *Erreurs serveur*   -- le serveur ne peut pas répondre à une requête valide  

### 1xx Informations

__100__	`TRYING`	-- action en cours (connexion, ça sonne, etc)

### 2XX Succès

__200__ `OK`		-- action terminée avec succès

### 3XX Redirection

### 4XX Erreurs
  
__400__ `ERR_BADREQUEST`	-- la requête est invalide
__401__ `ERR_AUTHREQUIRED`	-- authentification requise  
__402__ `ERR_PAYMENTREQUIRED`	-- lol  
__403__ `ERR_FORBIDDEN`		-- accès refusé (login ou mot de passe invalide)   
__404__ `ERR_NOTFOUND`		-- ressource non trouvée  
__405__ `ERR_NOTAVAILABLE`	-- ressource non disponible
### 5XX Erreurs du serveur maître  
  
__500__ `ERR_SV_ERROR`		-- erreur du serveur  
__501__ `ERR_SV_NOTIMPLEMENTED`	-- fonctionnalité non implémentée    
__502__ `ERR_SV_BADGATEWAY`	-- mauvaise gateway  
__503__ `ERR_SV_UNAVAILABLE`	-- le serveur est en maintenance    
__504__ `ERR_SV_TIMEOUT`	-- le serveur ne répond plus   

Exemple de communication
------------------------

**?** (*230.402.19.301*) : CL_REGISTER bab3l ForTheWin  
**->** 200

**?** (*230.402.19.301*) : CL_LOGIN bab3l ForTheWin  
**->** 200

**bab3l** (*230.402.19.301*) : CL_INFO  
**->** [envoi d'une liste de BabelUser]

**bab3l** (*230.402.19.301*) : CC_CALL Mark0  
**->** 404

**?** (*211.12.156.3*) : CL_REGISTER Mark0 2143  
**->** 200

**bab3l** (*230.402.19.301*) : CC_CALL Mark0  
**->** 405

**?** (*211.12.156.3*) : CL_LOGIN Mark0 2143  
**->** 200

**bab3l** (*230.402.19.301*) : CC_CALL Mark0  
**->** 100

**Server to Mark0** : CI_INCOMING bab3l

**Mark0** (*211.12.156.3*) : CC_WAIT bab3l  
**->** 200

**Server to bab3l** : CI_PENDING Mark0

**Mark0** (*211.12.156.3*) : CC_ACCEPT bab3l  
**->** 200

**Server to bab3l** : CI_ACCEPTED Mark0  
...

Note : Toute la vérification de requète s'effectue coté client, avant l'envoi de
celle-ci. Une erreur 400 ne doit pas être possible.