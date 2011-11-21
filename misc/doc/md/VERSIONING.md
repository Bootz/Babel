Gestionnaire de version (hg/hg-git/github)
==========================================

Linux (apt)
-----------

Installer mercurial et hg-git

    sudo apt-get install mercurial
    sudo easy_install hg-git

Dans le fichier de configuration ~/.hgrc :

    [ui]
    username = Prénom NOM <adresse@email.fr>
    
    [extensions]
    hgext.bookmarks =
    hggit =

Récupérer une copie du dépot GitHub

    hg clone git+ssh://git@github.com:ramnes/Babel.git

Dans le fichier de configuration Babel/.hg/hgrc :

    [paths]
    default = git+ssh://git@github.com:ramnes/Babel.git
    kscm = ssh://kscm@koala-rendus.epitech.net/babel-2014-adau_m

Propager le code sur GitHub, puis kscm

    hg add
    hg commit -m "Message en francais, clair et concis"
    hg push
    hg push kscm

Mettre à jour la version locale

    hg pull

Besoin de plus d'aide ?

    hg help

Windows
-------

[hg-git sous Windows (EN)](http://candidcode.com/2010/01/12/a-guide-to-converting-from-mercurial-hg-to-git-on-a-windows-client/)
