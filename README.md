# OS_Temps_Reel


Procédure de lancement du projet : 

Mettre le programme sur le robot en ftp :
— upload.sh permet d’envoyer sur la cible votre exécutable. La ligne de commande est :
./upload.sh <numéro de la machine> <chemin et nom de l’exécutable> 

Se connecter sur le robot en ftp :
— connect.sh permet de se connecter à la cible : La ligne de commande est :
   ./connect.sh <numéro de la machine>
   
Lancer l'executable sur le shuttle :
  ./robot

Lancer l'interface graphique : 
  java -jar Moniteur.jar
Faire attention à mettre IP adress avec le nom du robot
