# Compte rendu IOT

## Sujet

Réaliser un projet IoT simple qui nécessite la communication de plusieurs appareils. 

Chaque appareil est doté d'un capteur de température. Chaque appareil se situe à l'emplacement d'une bouteille à l'intérieur d'un réfrigérateur. 
Les appareils communiquent à un capteur central qui sert de puit de donnée. 
Le puit de donnée centralise les données d'un réfrigérateur et peut les envoyer à un puit de donnée plus général qui peut centraliserai lui même les données de plusieurs réfrigérateurs (plusieurs dans la même pièce, dans le même bâtiment etc). 

On imagine que le puit de donnée se trouve sur la porte du réfrigérateur et donc la détection des noeuds température et puits de donnée se fait de proche en proche.
En revanche si on veut récupérer les données de plusieurs réfrigérateurs, on peut très bien imaginer un système de routage ou alors de multi-saut entre les puits de données réfrigérateurs et les puits de données plus généraux.

## Installation 

On clone le git du projet
https://github.com/ToufaDev/projetIot/tree/master/projet_iot

Le projet se basant sur Riot OS, il y a problablement des packages à installer :

```
sudo apt install binutils-arm-none-eabi 
sudo apt install  libnewlib-arm-none-eabi 
```

Pour compiler le code des capteurs de température, on se déplace dans le répertoire /projetIot puis `make`
Pour compiler le code du puit de donnée, on se dépalce dans le répertoire /puit_de_donnee puis `make`

## Implémentation

Dans le cadre de notre implémentation, nous n'avons qu'un code source qui gère l'utilisation du capteur de température (se trouvant dans /projetIot) et un autre code source qui gère de récupérer les données envoyées par les noeuds de température (se trouvant dans /puit_de_donnee)

Le code du noeud capteur de température lit la valeur de la température à intervalle régulier et l'envoie en UDP en multicast.
Inversement, le puit de donnée se contente d'écouter sur son port en UDP pour récupérer les valeurs.

## Améliorations

Le projet est très minimaliste et on peut imaginer énormément d'améliorations. On peut imaginer utiliser un protocole de communications plus adaptés entre les noeuds température et puit de donnée car une communication UDP n'est pas nécessaire ici.

On peut aussi cibler le destinataire des données plutôt que d'émettre la donnée en multicast par exemple, dans notre cas, en fixant l'adresse IPV6 du puit de donnée et de configurer la socket pour lui envoyer la donnée.

On peut aussi améliorer le projet en implémentant du routage ou du multi-saut entre les puits de données et d'autres noeuds puits de données généraux.

## Difficultés rencontrées

Beaucoup de difficultés rencontrées durant ce projet, les principes utilisés en IoT dans la communication ne sont pas si intuitifs même avec les cours en support, et nous nous sommes retranchés sur des principes que nous connaissions déjà (sockets UDP) plutôt que de tenter autre chose (LORA ou 6LowPan) plus porté sur l'IoT.

Il a été très difficile de se répérer dans la documentation pour pouvoir implémenter la capture de la température ou alors trouver les méthodes à utiliser pour gérer l'IpV6 ou alors sur comment on devait initialiser et utiliser les sockets. 