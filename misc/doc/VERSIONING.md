Gestionnaire de version (hg/hg-git/github)
==========================================

Linux (apt)
-----------

* Installer

    sudo apt-get install mercurial
    sudo easy_install hg-git

* Configurer

Dans ~/.hgrc :

    [ui]
    username = Prénom NOM <adresse@email.fr>
    
    [extensions]
    hgext.bookmarks =
    hggit =

* Récupérer le code

    hg clone git+ssh://git@github.com:ramnes/Babel.git

* Propager le code

    hg add
    hg commit -m "Message en francais, clair et concis"
    hg push
    hg push kscm

* Mettre à jour

    hg pull

* Plus ?

    hg help

Windows
-------

[hg-git sous Windows (EN)](http://candidcode.com/2010/01/12/a-guide-to-converting-from-mercurial-hg-to-git-on-a-windows-client/)