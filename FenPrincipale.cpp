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
    m_currTextTab(0),
    m_tabCount(0)
{
    this->resize(600, 480);
    this->setAnimated(true);

    /// Création des menus --------------------------------------------
    QMenu* menuFichier = menuBar()->addMenu("&Fichier");///           |
    QMenu* menuEdition = menuBar()->addMenu("&Edition");///           |
    QMenu* menuAffichage = menuBar()->addMenu("&Affichage");///       |
    QMenu* menuAide = menuBar()->addMenu("&Aide");///                 |
    /// ---------------------------------------------------------------


    /// Ajoute actions -----------------------------------------------
    QAction* actionNewTab = menuFichier->addAction("&Nouvel onglet");
    actionNewTab->setShortcut(QKeySequence("Ctrl+shift+N"));
    actionNewTab->setIcon(QIcon("tab-new.png"));

    QAction* actionQuitter = menuFichier->addAction("&Quitter");
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    actionQuitter->setIcon(QIcon("quitter.png"));

    QAction* actionAbout = menuAide->addAction("About");
    //actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    //actionQuitter->setIcon(QIcon("quitter.png"));
    /// ---------------------------------------------------------------


    /// Création de la barre d'outils ---------------------------------
    m_toolBarFichier = addToolBar("Fichier"); // Ajoute une nouvelle barre d'outil

    // ajoute les boutons à la barre d'outil
    m_toolBarFichier->addAction(actionQuitter);
    m_toolBarFichier->addAction(actionNewTab);
    m_toolBarFichier->addSeparator();
    m_toolBarChoixPolice = new QFontComboBox;
    m_toolBarFichier->addWidget(m_toolBarChoixPolice);
    /// ---------------------------------------------------------------


    /// Création de la zone centrale
    m_zoneCentrale->setMovable(true);
    this->setCentralWidget(m_zoneCentrale);


    /// Faire les connections ----------------------------------------
    connect(actionNewTab, SIGNAL(triggered()), this, SLOT(addOnglet()));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(montrerAbout()));

    connect(m_zoneCentrale, SIGNAL(currentChanged(int)), this, SLOT(changerCurrTab(int)));
    connect(m_zoneCentrale, SIGNAL(tabCloseRequested(int)), this, SLOT(deleteOnglet(int)));

    connect(m_currTextTab, SIGNAL(textChanged()), this, SLOT(marquerChangement()));

    connect(m_toolBarChoixPolice, SIGNAL(currentFontChanged(QFont)), this, SLOT(changerPolice(QFont)));
    /// --------------------------------------------------------------
}



// Ce SLOT cree un nouvel onglet
void FenPrincipale::addOnglet()
{
    //m_zoneCentrale->addTab(new QTextEdit, QString("Onglet ") + QString::number(++m_tabCount));
    m_zoneCentrale->addTab(new QTextEdit(m_zoneCentrale), QString("Nouvel onglet"));
    if( (! m_zoneCentrale->tabsClosable()) && (m_zoneCentrale->count() > 1) ){
        m_zoneCentrale->setTabsClosable(true);
    }
    //m_zoneCentrale->setCornerWidget(m_zoneCentrale->currentWidget(), Qt::TopRightCorner);
}


// Ce SLOT change la police du widget actif
void FenPrincipale::changerPolice(QFont police)
{
    for(int i=0; i < m_zoneCentrale->count(); ++i){
        m_zoneCentrale->widget(i)->setFont(police);
    }

    // 2° Methode pour changer la police individuellement
    //m_zoneCentrale->currentWidget()->setFont(police);
}


// Ce SLOT supprime un onglet
void FenPrincipale::deleteOnglet(int index)
{
    m_zoneCentrale->removeTab(index);

    // diminue le counteur de tabs
    //m_tabCount = m_zoneCentrale->count();

    // renommer les onglets après la supprimée
    /*for(int i=index; i < m_tabCount; ++i){
        m_zoneCentrale->setTabText(i, QString("Onglet ") + QString::number(i+1));
    }*/

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
    m_zoneCentrale->setTabText(m_zoneCentrale->indexOf(m_currTextTab),
                               QString("*"));
    //m_zoneCentrale->currentWidget();
}















