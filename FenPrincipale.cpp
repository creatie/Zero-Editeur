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
    m_lastIndex(-1)
{
    this->resize(600, 480);
    this->setWindowTitle("Zero Editeur");
    this->setWindowIcon(QIcon("editor-icon.png"));
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
    connect(actionPreferences, SIGNAL(triggered()), this, SLOT(ouvrirPreferences()));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(montrerAbout()));
    connect(actionSauvegarder, SIGNAL(triggered()), this, SLOT(sauvegarderFichier()));

    connect(m_zoneCentrale, SIGNAL(currentChanged(int)), this, SLOT(changerCurrTab(int)));
    connect(m_zoneCentrale, SIGNAL(tabCloseRequested(int)), this, SLOT(supprimerOnglet(int)));

    //connect(m_zoneCentrale, SIGNAL(currentChanged(int)), this, SLOT(marquerChangement(int)));

    //connect(m_toolBarChoixPolice, SIGNAL(currentFontChanged(QFont)), this, SLOT(changerPolice(QFont)));
    /// --------------------------------------------------------------
}

void FenPrincipale::creerMenu()
{
    menuFichier = menuBar()->addMenu("&Fichier");
    menuEdition = menuBar()->addMenu("&Edition");
    menuAffichage = menuBar()->addMenu("&Affichage");
    menuAide = menuBar()->addMenu("&Aide");
}

void FenPrincipale::creerActions()
{
    // Menu fichier --------------------------------------------------
    actionNouvelOnglet = menuFichier->addAction("&Nouvel onglet");
    actionNouvelOnglet->setShortcut(QKeySequence("Ctrl+shift+N"));
    actionNouvelOnglet->setIcon(QIcon("tab-new.png"));

    actionSauvegarder = menuFichier->addAction("&Sauvegarder");
    actionSauvegarder->setShortcut(QKeySequence("Ctrl+S"));
    actionSauvegarder->setIcon(QIcon("document-save.png"));
    /// @todo actionSauvegarder->setDisabled(true);

    actionSauvegarderComme = menuFichier->addAction("Sauvegarder comme ...");
    actionSauvegarderComme->setShortcut(QKeySequence("Ctrl+shift+S"));
    actionSauvegarderComme->setIcon(QIcon("document-save-as.png"));
    /// @todo actionSauvegarderComme->setDisabled(true);

    actionQuitter = menuFichier->addAction("&Quitter");
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    actionQuitter->setIcon(QIcon("quitter.png"));

    // Menu edition --------------------------------------------------
    actionPreferences = menuEdition->addAction("&Preferences");
    actionPreferences->setShortcut(QKeySequence("Ctrl+P"));
    actionPreferences->setIcon(QIcon("preferences.png"));

    // Menu aide -----------------------------------------------------
    actionAbout = menuAide->addAction("About");
}


void FenPrincipale::creerToolBars()
{
    m_toolBarFichier = addToolBar("Fichier"); // Ajoute une nouvelle barre d'outil

    // ajoute les boutons à la barre d'outil "Fichier"
    //m_toolBarFichier->addAction(actionQuitter);
    m_toolBarFichier->addAction(actionNouvelOnglet);
    m_toolBarFichier->addAction(actionSauvegarder);
    m_toolBarFichier->addAction(actionSauvegarderComme);
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
    m_statusBar = new QStatusBar(this);
    this->setStatusBar(m_statusBar);
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
    qDebug() << QString("Changement du pointeur de currTab");
    if(m_zoneCentrale->widget(index)->isWindowModified()){ // if the current tab was modified
        actionSauvegarder->setEnabled(true);
        actionSauvegarderComme->setEnabled(true);
    }
    else{
        actionSauvegarder->setDisabled(true);
        actionSauvegarderComme->setDisabled(true);
    }
    m_currTextTab = dynamic_cast<QTextEdit*>( m_zoneCentrale->widget(index) );
}


//
void FenPrincipale::marquerChangement(int index)
{
    qDebug() << QString("Changement marqué\n");
    m_zoneCentrale->setTabText(index, QString("*"));
}


void FenPrincipale::ouvrirPreferences()
{

    QWidget optionsDialog;
    optionsDialog.setWindowTitle("Preferences");
    optionsDialog.setFixedSize(200, 300);
    optionsDialog.setWindowIcon(QIcon("preferences.png"));

    QPushButton boutonPolice(&optionsDialog);
    QPushButton boutonCouleur(&optionsDialog);
    QPushButton boutonOk(&optionsDialog);

    QVBoxLayout layout_root;
    layout_root.addWidget(&boutonPolice);
    layout_root.addWidget(&boutonCouleur);
    layout_root.addWidget(&boutonOk);

    optionsDialog.setLayout(&layout_root);

    optionsDialog.show();

}

void FenPrincipale::sauvegarderFichier()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Sauvegarder fichier"), "", tr("Texte (*.txt);;Tous formats (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }
        QTextStream out(&file);
        ///out.setVersion(QDataStream::Qt_4_5);
        QTextEdit* tempTextEdit = dynamic_cast<QTextEdit*> ( m_zoneCentrale->currentWidget() );
        QString str = tempTextEdit->toPlainText();
        out << tempTextEdit->toPlainText() ;
    }
}


















