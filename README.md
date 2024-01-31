# TP Système d'Exploitation
# Partie 1: Système de Fichiers ext2 et Forensic Data Analysis
# Objectif et Méthodologie

L'objectif était d'analyser un hexdump d'un système de fichiers ext2, en utilisant la commande od pour explorer sa structure. Mon travail consistait à identifier la taille des blocs, le nombre d'i-noeuds, et diverses métadonnées associées aux fichiers et répertoires.

# Réalisations

    Analyse de la Structure: J'ai pu déterminer la taille des blocs et le nombre d'i-noeuds, ce qui m'a offert un aperçu précis de la gestion de l'espace dans ext2.
    Extraction de Métadonnées: En explorant l'arborescence, j'ai extrait des informations détaillées telles que les droits d'accès, le propriétaire des fichiers et leur taille.
    Découverte d'Informations Cachées: Grâce à une analyse minutieuse, j'ai réussi à retrouver des dates spécifiques et des valeurs aléatoires stockées dans des fichiers, démontrant ainsi ma capacité à effectuer une analyse forensique approfondie.

# Partie 2: Processus
# Objectif et Méthodologie

Cette partie portait sur la compréhension et la manipulation des piles d'appels (CALLSTACK) et sur l'implémentation de l'algorithme du crible d'Eratosthène en utilisant la programmation multi-processus.

# Réalisations

    Manipulation du CALLSTACK: J'ai modifié une fonction variadique pour qu'elle additionne tous ses paramètres, démontrant ainsi ma compréhension de la gestion des paramètres indéfinis en C.
    Crible d'Eratosthène Multi-Processus: En créant une chaîne de processus filtrant successivement les multiples de nombres premiers, j'ai mis en œuvre un algorithme efficace pour générer des nombres premiers.

# Partie 3: Threads
# Objectif et Méthodologie

L'objectif était de manipuler des threads pour réaliser des tâches parallèles, notamment un système producteur-consommateur et le calcul du produit scalaire de deux vecteurs.

# Réalisations

    Gestion de Threads: J'ai créé plusieurs threads pour afficher leur identifiant unique et pour réaliser des calculs partagés, en utilisant des opérations atomiques pour éviter les conditions de course.
    Système Producteur-Consommateur: J'ai corrigé les problèmes de synchronisation dans un modèle producteur-consommateur, assurant que chaque consommateur traite une ressource unique.
    Calcul du Produit Scalaire: Mon programme multi-thread calcule le produit scalaire de deux vecteurs, optimisant l'utilisation du CPU et démontrant une augmentation significative des performances avec l'augmentation du nombre de threads.

# Conclusion

À travers ces travaux pratiques, j'ai acquis une compréhension profonde des systèmes d'exploitation, depuis la structure des systèmes de fichiers jusqu'à la programmation concurrentielle. Ces expériences m'ont non seulement permis de développer mes compétences techniques en programmation système, mais aussi de comprendre les défis liés à l'optimisation et à la sécurité des systèmes informatiques modernes. Ces connaissances seront indéniablement précieuses pour ma future carrière dans le domaine de l'informatique.
