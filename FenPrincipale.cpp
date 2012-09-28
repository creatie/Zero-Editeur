/* Création des docks
QDockWidget *dock = new QDockWidget("Palette", this);
addDockWidget(Qt::LeftDockWidgetArea, dock);

QWidget *contenuDock = new QWidget;
dock->setWidget(contenuDock);

QPushButton *crayon = new QPushButton("Crayon");
QPushButton *pinceau = new QPushButton("Pinceau");
QPushButton *feutre = new QPushButton("Feutre");
QLabel *labelEpaisseur = new QLabel("Epaisseur :");
QSpinBox *epaisseur = new QSpinBox;

QVBoxLayout *dockLayout = new QVBoxLayout;
dockLayout->addWidget(crayon);
dockLayout->addWidget(pinceau);
dockLayout->addWidget(feutre);
dockLayout->addWidget(labelEpaisseur);
dockLayout->addWidget(epaisseur);

contenuDock->setLayout(dockLayout);*/

#include "FenPrincipale.h"



FenPrincipale::FenPrincipale() :
    QMainWindow(),
    m_zoneCentrale(new QTabWidget(this)),
    m_currTextTab(0)
{
    this->resize(600, 480);
    this->setAnimated(true);

    // Création des menus --------------------------------------------
    this->creerMenu();

    // Ajoute actions ------------------------------------------------
    this->creerActions();

    // Création de la barre d'outils ---------------------------------
    this->creerToolBars();

    // Création de la zone centrale ----------------------------------
    this->creerMdi();

    // Création de la barre de status --------------------------------
    this->creerStatusBar();


    /// Faire les connections ----------------------------------------
    connect(actionNouvelOnglet, SIGNAL(triggered()), this, SLOT(addOnglet()));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(montrerAbout()));

    connect(m_zoneCentrale, SIGNAL(currentChanged(int)), this, SLOT(changerCurrTab(int)));
    connect(m_zoneCentrale, SIGNAL(tabCloseRequested(int)), this, SLOT(supprimerOnglet(int)));

    connect(m_currTextTab, SIGNAL(textChanged()), this, SLOT(marquerChangement()));

    //connect(m_toolBarChoixPolice, SIGNAL(currentFontChanged(QFont)), this, SLOT(changerPolice(QFont)));
    /// --------------------------------------------------------------
}


void FenPrincipale::creerActions()
{
    // Menu fichier --------------------------------------------------
    actionNouvelOnglet = menuFichier->addAction("&Nouvel onglet");
    actionNouvelOnglet->setShortcut(QKeySequence("Ctrl+shift+N"));
    actionNouvelOnglet->setIcon(QIcon("tab-new.png"));

    actionQuitter = menuFichier->addAction("&Quitter");
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    actionQuitter->setIcon(QIcon("quitter.png"));

    // Menu edition --------------------------------------------------


    // Menu aide -----------------------------------------------------
    actionAbout = menuAide->addAction("About");
}


void FenPrincipale::creerToolBars()
{
    m_toolBarFichier = addToolBar("Fichier"); // Ajoute une nouvelle barre d'outil

    // ajoute les boutons à la barre d'outil "Fichier"
    //m_toolBarFichier->addAction(actionQuitter);
    m_toolBarFichier->addAction(actionNouvelOnglet);
    m_toolBarFichier->addSeparator();
    //m_toolBarFichier->addWidget(m_toolBarChoixPolice);
}


void FenPrincipale::creerMdi()
{
    m_zoneCentrale->setMovable(true);
    this->setCentralWidget(m_zoneCentrale);
}


void FenPrincipale::creerStatusBar()
{
}




/// SLOTS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// Ce SLOT cree un nouvel onglet
void FenPrincipale::addOnglet()
{
    m_zoneCentrale->addTab(new QTextEdit(m_zoneCentrale), QString("Nouvel onglet"));
    if( (! m_zoneCentrale->tabsClosable()) && (m_zoneCentrale->count() > 1) ){
        m_zoneCentrale->setTabsClosable(true);
    }
}


// Ce SLOT change la police du widget actif
void FenPrincipale::changerPolice(QFont police)
{
    for(int i=0; i < m_zoneCentrale->count(); ++i){
        m_zoneCentrale->widget(i)->setFont(police);
    }
}


// Ce SLOT supprime un onglet
void FenPrincipale::supprimerOnglet(int index)
{
    m_zoneCentrale->removeTab(index);

    // Si il y a une seule tab, enlever la possibiliter de fermer les tabs individualement
    if(m_zoneCentrale->count() == 1) m_zoneCentrale->setTabsClosable(false);
}


/// @todo
void FenPrincipale::montrerAbout()
{
}


// Change le pointeur du onglet actif
void FenPrincipale::changerCurrTab(int index)
{
    m_zoneCentrale->widget(index);
}


//
void FenPrincipale::marquerChangement()
{
    m_zoneCentrale->setTabText(m_zoneCentrale->indexOf(m_currTextTab), QString("*"));
}

void FenPrincipale::creerMenu()
{
    menuFichier = menuBar()->addMenu("&Fichier");
    menuEdition = menuBar()->addMenu("&Edition");
    menuAffichage = menuBar()->addMenu("&Affichage");
    menuAide = menuBar()->addMenu("&Aide");
}
















