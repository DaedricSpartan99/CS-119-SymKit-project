READ ME PLEASE

REPONSES AUX QUESTIONS POS�S DANS LES DIRECTIVES POUR LE RENDU

1 On retient d'avoir compl�t� le projet, ce qui �t� d�mand� � �t� fait compl�tement, 
  sauf pour un ou deux fichiers de test d�mand�s explicitement qu'on a "int�gr�" implicitement dans un subdir ALPHA
  qui vaut, pour nous, comme un grand test de l'openGL du programme.
  De plus on a implement� une interface graphique utilisateur (GUI) pour la g�stion interactive de la simulation.

2 On a une version Graphique, et on a utilis� la biblioth�que Qt5.

3 Nous estimons avoir travaill� environs 7,5 heures par semaine.
  Le chiffre est purement approximatif, et nous tenons � pr�ciser que 
  au moins 2 heures de plus par semaine sur le projet ont �t� pass�es par ANCAROLA RAFFAELE, 
  pour l'optimisation du projet (optimisation temporelle et spatiale).
  Il y tenait particuli�rement.

	
	INFOS POUR L'UTILISATEUR
	
ATTENTION, il est important d'utiliser au moins Qt5 pour la compilation du programme!

BUILD DE L'EXECUTABLE

M�thode principale (linux terminal):

	Tu trouve le fichier build.sh dans le dossier principal (attention, le dossier doit forcement �tre nomm� symkit).
	Pour executer ce fichier ouvrir un terminal, naviguer dans la directory symkit et executer les commandes suivantes:

		chmod +x build.sh
		./build.sh
	
	La compilation va �tre g�ner�e dans la directory build.
	Observation: assure toi d'avoir bien install� qt5 parce que sinon le fichier build.sh 
				 va retourner un erreur de version.

M�thode alternative: 
	
	Ouvrir qtCreator, configurer le build kit selon son propre syst�me operatif et executer build->"build project symkit"

LANCER LA SIMULATION

M�thode principale (linux terminal):

	Une fois que la directory build a �t� g�n�r�e,
	naviguer dans build, tu y trouvera deux executable dans les parcours (relatifs) suivants:

		alpha/bin/alpha 		(execution du test alpha)
		beta/bin/beta 			(execution du test beta)

M�thode alternative (par qt):

	Pour lancer la simulation, lorsque le programme a �t� compil�, et une fois ouvert le projet symkit avec Qt, 
	il suffit de choisir quelle executable executer, en cliquant sur l'icone repr�sentant l'�cran d'un pc, 
	et ensuite cliquer sur le bouton vert play, ou sur Compiler->Executer.
	
AU LANCEMENT
	
	- Au lancement de Alpha, s'ouvrira tout simplement une f�netre OpenGL, contenant les simulations graphiques 
	 des 4 premiers pendules par nous cr�es et test�s. Alpha representant juste un test de notre implementation graphique,
	 il n'est donc pas possible de modifier les objets simul�s en runtime (on peut le faire seulement avant compilation).
	- Au lancement de Beta, deux f�netres OpenGL s'ouvriront, une contenant la simulation graphique 3D des oscillateurs cr��s,
	 l'autre contenant une interface utilisateur graphique (GUI).
	 Au lancement les oscillateurs disponibles dans l'espace 3D seront 4, plus une autre particule, representante un objet physique 
	 autre qu'un oscillateur.
	 Tous les oscillateur seront initialis� � leur forme de defaut, et il pourront �tre modifi�s � travers leur propre pannel de contr�le
	 dans la GUI. Le fonctionnement de la GUI est expliqu� ici de suite.
	Dans la f�netre 3D est possible de se d�placer et int�ragir avec diff�rentes commandes clavier, ces commandes seront explicit� dans une prochaine s�ction.
	
	
GUI

	L'interface utilisateur est compos�e d'un panel de contr�le pour chaqu'un des quatres oscillateurs implement�s dans la simulation.
	Il est possible de visualiser un panel � la fois, et de le choisir par une liste situ�e � gauche dans la GUI.
	Le panel recouvre la presque enti�ret� de la fen�tre, et continent plusieurs champs de textes, boutons et case � cocher, 
	et notamment l'espace des phases de l'oscillateur concern�.
	Le dessin sur le graphe de l'espace des phases doit �tre lanc� par l'utilisateur � travers le bouton START. 
	Le panel est aussi fourni d'un bouton STOP et CLEAR pour l'arr�t et l'effacement du dessin.
	Pour se d�placer dans le graphe il est n�cessaire de cliquer sur ce d�rnier et d'utiliser les commandes clavier 
	donn�e en l�gende sur le panel.
	Les cases � cocher permettent � l'utilisateur de choisir si les diff�rentes sp�cificit�s des particules seront habilit�es ou non, 
	comme dessinnable et evoluable. On peut donc par cela choisir si l'oscillateur doit �tre dessin�, positionn�, color�, 
	ou s'il doit �voluer, et tout cela en temps r�el.
	Les champs de texte affichent les param�tres caract�risant l'oscillateur en temps r�el, 
	et permettent de les modifier, en temps r�el. Les modifications apport�es provoqueront un changement imm�diat 
	dans l'affichage de l'�space des phases et dans le monde de simulation 3D.
	Pour les oscillateur coupl�s, un panel est compos� de plusieurs onglets, un par particule et un pour l'�space des phases.

COMMANDES CLAVIER (Utilisable sur la f�netre du monde 3D)

Attention, il est important de se trouver sur la f�netre de simulation graphique 3D pour utiliser ces commandes.
Ouvrir donc cette f�netre et cliquer dessus si la f�netre ne reponds pas aux input clavier.
Pas toutes les commandes ici de suitr ont �t� implement�s dans ALPHA.

	Translation de la Camera
	
		W,S,A,D : devant, derriere, gauche, droite (selon l'orientation des axes X/Y/Z)
		J,K : bas, haut
	 
	Rotation de la camera
		
		Up,Down,Left,Right : haut, bas, gauche, droite
	
	P : Mettre en pause les simulations
	Attention, si tu n'arrive pas � mettre en pause c'est parce que le programme prends un input pour chaque pas de temps
	Un nombre de pas de temps pair pendant lequel la commande a �t� mantenue se traduit donc dans pas de pause
	
	ESCAPE : Fermer la f�netre
	
	SPACE : Repulser la NewtonParticle (une sorte de Pendule-ressort)
			La repulsion est inversement proportionnelle � la distance entre Camera et Particule
			
	Simulations texte sur terminale Qt (en appuyant le bouton lorsqu'on se trouve dans la f�netre)
		
		1 : Pendule simple
		2 : Ressort
		3 : Pendule-Charriot
		4 : Pendule double
	
	
	
	INFOS POUR CELUI QUI EVALUE

Le Makefile d�mand� a �t� substitu� par un qmakefile "symkit.pro", vu la difficult� de programmer un makefile qui fonctionne sur windows et sur linux simultan�ement.

DOCUMENTS TEXTE

	Les document texte demand�s, JOURNAL, REPONSES et CONCEPTION se trouvent dans le dossier "doc".
	README, JOURNAL et REPONSES ont �t�s �crit avec Notepad++, donc si ouverts avec d'autres programmes de lecture texte 
	la mise en page pourrait apparaitre pas tout affait correcte.
	CONCEPTION est un pdf �crit en Latex, cela ne devrait donc pas causer ce type de probl�mes.

CODE INT�GR�

	Le code est divis� en 6 subdirs r�li�s dans le m�me projet par le qmakefile "symkit.pro".
	Pour chaque subdirs on a un .pro pour le qmake.

	Biblioth�ques base:

		-SYMATH: - il contient le code qui g�re la partie math�matique du projet, c'est � dire vecteurs, 
				 integrateurs et descriptors (code pour la description differentielle du mouvement d'objets physiques)
				 - il contient aussi une structure utile pour la gestion d'erreur.
		 
		-SYMGRAPH: il contient le code qui s'occupe de la cr�ation et de la g�stion d'un monde graphique 3D, plus g�n�ralment, de la gestion de f�netres OpenGL.

		-SYMPLOT: il contient le code qui g�re le dessin de graphes, notamment le dessin des espaces des phases

		-SYMVIEWER: - il contient le code qui g�re l'interface utilisateur,
					pour le contr�le interactif de la scene et des valeur affich�s � l'�cran
					- des limites aux valeur que l'utilisateur peut assigner aux diff�rents param�tres ont �t�es fix�es
					ceci pour �viter la plupart des divergences de calcul du au calcul de valeurs trop grandes.
					- il permet aussi l'implementation d'une version alternative d'affichage en mode texte.
			
		Biblioth�ques executables:

		-ALPHA: - il contient la pr�mi�re implementation faite du programme executable: 
				ouverture d'une f�netre OpenGL pour simulation des premiers oscillateurs implement�s, 
				dont une implementation abandonn�e et am�lior�e conceptuellement dans le projet finale.
				- il est fourni en guise de temoignage de l'�volution du code, et comme grand "file" test 
				comme ceux demand�s pour le rendu finale.
				- le code a �t� n�anmoins modifi� un minimum vers la fin du sem�stre, 
				pour qu'il compile, dans le but de rendre aussi un t�moignage visuel de la viellie impl�mentation.
		
		-BETA: - il s'appelle BETA mais il representel'implementation d�finitive pour le rendu.
			   - il contient code executable qui cr�e des simulations graphique et ouvre les f�netres du monde 3D, 
			   de l'espace des phase, et de l'interface utilisateur.
			   - c'est aussi le code qui fait le lien concret entre les 4 biblioth�ques base constituant le programme.
	   
	   
FICHIERS DE TEST

	Les fichiers de test demand�s se trouvent dans le dossier "templates".
	Les test li�s � l'implementation graphique ne sont pas pr�sent dans templates 
	car on consid�re le code prensent dans ALPHA comme un grand  "test" sur le monde graphique qu'on a cr��.
	
DIRECTIVES

	Le fichier DIRECTIVES.txt contient le r�sum� de l'objectif du projet et les directives qu'on a suivit pour le codage du projet.
	

	
	

