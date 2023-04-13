READ ME PLEASE

REPONSES AUX QUESTIONS POSÉS DANS LES DIRECTIVES POUR LE RENDU

1 On retient d'avoir complété le projet, ce qui été démandé à été fait complétement, 
  sauf pour un ou deux fichiers de test démandés explicitement qu'on a "intégré" implicitement dans un subdir ALPHA
  qui vaut, pour nous, comme un grand test de l'openGL du programme.
  De plus on a implementé une interface graphique utilisateur (GUI) pour la géstion interactive de la simulation.

2 On a une version Graphique, et on a utilisé la bibliothèque Qt5.

3 Nous estimons avoir travaillé environs 7,5 heures par semaine.
  Le chiffre est purement approximatif, et nous tenons à préciser que 
  au moins 2 heures de plus par semaine sur le projet ont été passées par ANCAROLA RAFFAELE, 
  pour l'optimisation du projet (optimisation temporelle et spatiale).
  Il y tenait particulièrement.

	
	INFOS POUR L'UTILISATEUR
	
ATTENTION, il est important d'utiliser au moins Qt5 pour la compilation du programme!

BUILD DE L'EXECUTABLE

Méthode principale (linux terminal):

	Tu trouve le fichier build.sh dans le dossier principal (attention, le dossier doit forcement être nommé symkit).
	Pour executer ce fichier ouvrir un terminal, naviguer dans la directory symkit et executer les commandes suivantes:

		chmod +x build.sh
		./build.sh
	
	La compilation va être génerée dans la directory build.
	Observation: assure toi d'avoir bien installé qt5 parce que sinon le fichier build.sh 
				 va retourner un erreur de version.

Méthode alternative: 
	
	Ouvrir qtCreator, configurer le build kit selon son propre système operatif et executer build->"build project symkit"

LANCER LA SIMULATION

Méthode principale (linux terminal):

	Une fois que la directory build a été générée,
	naviguer dans build, tu y trouvera deux executable dans les parcours (relatifs) suivants:

		alpha/bin/alpha 		(execution du test alpha)
		beta/bin/beta 			(execution du test beta)

Méthode alternative (par qt):

	Pour lancer la simulation, lorsque le programme a été compilé, et une fois ouvert le projet symkit avec Qt, 
	il suffit de choisir quelle executable executer, en cliquant sur l'icone représentant l'écran d'un pc, 
	et ensuite cliquer sur le bouton vert play, ou sur Compiler->Executer.
	
AU LANCEMENT
	
	- Au lancement de Alpha, s'ouvrira tout simplement une fênetre OpenGL, contenant les simulations graphiques 
	 des 4 premiers pendules par nous crées et testés. Alpha representant juste un test de notre implementation graphique,
	 il n'est donc pas possible de modifier les objets simulés en runtime (on peut le faire seulement avant compilation).
	- Au lancement de Beta, deux fênetres OpenGL s'ouvriront, une contenant la simulation graphique 3D des oscillateurs créés,
	 l'autre contenant une interface utilisateur graphique (GUI).
	 Au lancement les oscillateurs disponibles dans l'espace 3D seront 4, plus une autre particule, representante un objet physique 
	 autre qu'un oscillateur.
	 Tous les oscillateur seront initialisé à leur forme de defaut, et il pourront être modifiés à travers leur propre pannel de contrôle
	 dans la GUI. Le fonctionnement de la GUI est expliqué ici de suite.
	Dans la fênetre 3D est possible de se déplacer et intéragir avec différentes commandes clavier, ces commandes seront explicité dans une prochaine séction.
	
	
GUI

	L'interface utilisateur est composée d'un panel de contrôle pour chaqu'un des quatres oscillateurs implementés dans la simulation.
	Il est possible de visualiser un panel à la fois, et de le choisir par une liste située à gauche dans la GUI.
	Le panel recouvre la presque entièreté de la fenêtre, et continent plusieurs champs de textes, boutons et case à cocher, 
	et notamment l'espace des phases de l'oscillateur concerné.
	Le dessin sur le graphe de l'espace des phases doit être lancé par l'utilisateur à travers le bouton START. 
	Le panel est aussi fourni d'un bouton STOP et CLEAR pour l'arrêt et l'effacement du dessin.
	Pour se déplacer dans le graphe il est nécessaire de cliquer sur ce dérnier et d'utiliser les commandes clavier 
	donnée en légende sur le panel.
	Les cases à cocher permettent à l'utilisateur de choisir si les différentes spécificités des particules seront habilitées ou non, 
	comme dessinnable et evoluable. On peut donc par cela choisir si l'oscillateur doit être dessiné, positionné, coloré, 
	ou s'il doit évoluer, et tout cela en temps réel.
	Les champs de texte affichent les paramètres caractérisant l'oscillateur en temps réel, 
	et permettent de les modifier, en temps réel. Les modifications apportées provoqueront un changement immédiat 
	dans l'affichage de l'éspace des phases et dans le monde de simulation 3D.
	Pour les oscillateur couplés, un panel est composé de plusieurs onglets, un par particule et un pour l'éspace des phases.

COMMANDES CLAVIER (Utilisable sur la fênetre du monde 3D)

Attention, il est important de se trouver sur la fênetre de simulation graphique 3D pour utiliser ces commandes.
Ouvrir donc cette fênetre et cliquer dessus si la fênetre ne reponds pas aux input clavier.
Pas toutes les commandes ici de suitr ont été implementés dans ALPHA.

	Translation de la Camera
	
		W,S,A,D : devant, derriere, gauche, droite (selon l'orientation des axes X/Y/Z)
		J,K : bas, haut
	 
	Rotation de la camera
		
		Up,Down,Left,Right : haut, bas, gauche, droite
	
	P : Mettre en pause les simulations
	Attention, si tu n'arrive pas à mettre en pause c'est parce que le programme prends un input pour chaque pas de temps
	Un nombre de pas de temps pair pendant lequel la commande a été mantenue se traduit donc dans pas de pause
	
	ESCAPE : Fermer la fênetre
	
	SPACE : Repulser la NewtonParticle (une sorte de Pendule-ressort)
			La repulsion est inversement proportionnelle à la distance entre Camera et Particule
			
	Simulations texte sur terminale Qt (en appuyant le bouton lorsqu'on se trouve dans la fênetre)
		
		1 : Pendule simple
		2 : Ressort
		3 : Pendule-Charriot
		4 : Pendule double
	
	
	
	INFOS POUR CELUI QUI EVALUE

Le Makefile démandé a été substitué par un qmakefile "symkit.pro", vu la difficulté de programmer un makefile qui fonctionne sur windows et sur linux simultanéement.

DOCUMENTS TEXTE

	Les document texte demandés, JOURNAL, REPONSES et CONCEPTION se trouvent dans le dossier "doc".
	README, JOURNAL et REPONSES ont étés écrit avec Notepad++, donc si ouverts avec d'autres programmes de lecture texte 
	la mise en page pourrait apparaitre pas tout affait correcte.
	CONCEPTION est un pdf écrit en Latex, cela ne devrait donc pas causer ce type de problèmes.

CODE INTÉGRÉ

	Le code est divisé en 6 subdirs réliés dans le même projet par le qmakefile "symkit.pro".
	Pour chaque subdirs on a un .pro pour le qmake.

	Bibliothèques base:

		-SYMATH: - il contient le code qui gère la partie mathématique du projet, c'est à dire vecteurs, 
				 integrateurs et descriptors (code pour la description differentielle du mouvement d'objets physiques)
				 - il contient aussi une structure utile pour la gestion d'erreur.
		 
		-SYMGRAPH: il contient le code qui s'occupe de la création et de la géstion d'un monde graphique 3D, plus généralment, de la gestion de fênetres OpenGL.

		-SYMPLOT: il contient le code qui gère le dessin de graphes, notamment le dessin des espaces des phases

		-SYMVIEWER: - il contient le code qui gère l'interface utilisateur,
					pour le contrôle interactif de la scene et des valeur affichés à l'écran
					- des limites aux valeur que l'utilisateur peut assigner aux différents paramètres ont étées fixées
					ceci pour éviter la plupart des divergences de calcul du au calcul de valeurs trop grandes.
					- il permet aussi l'implementation d'une version alternative d'affichage en mode texte.
			
		Bibliothèques executables:

		-ALPHA: - il contient la prémière implementation faite du programme executable: 
				ouverture d'une fênetre OpenGL pour simulation des premiers oscillateurs implementés, 
				dont une implementation abandonnée et améliorée conceptuellement dans le projet finale.
				- il est fourni en guise de temoignage de l'évolution du code, et comme grand "file" test 
				comme ceux demandés pour le rendu finale.
				- le code a été néanmoins modifié un minimum vers la fin du semèstre, 
				pour qu'il compile, dans le but de rendre aussi un témoignage visuel de la viellie implémentation.
		
		-BETA: - il s'appelle BETA mais il representel'implementation définitive pour le rendu.
			   - il contient code executable qui crée des simulations graphique et ouvre les fênetres du monde 3D, 
			   de l'espace des phase, et de l'interface utilisateur.
			   - c'est aussi le code qui fait le lien concret entre les 4 bibliothèques base constituant le programme.
	   
	   
FICHIERS DE TEST

	Les fichiers de test demandés se trouvent dans le dossier "templates".
	Les test liés à l'implementation graphique ne sont pas présent dans templates 
	car on considère le code prensent dans ALPHA comme un grand  "test" sur le monde graphique qu'on a créé.
	
DIRECTIVES

	Le fichier DIRECTIVES.txt contient le résumé de l'objectif du projet et les directives qu'on a suivit pour le codage du projet.
	

	
	

