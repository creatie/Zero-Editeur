#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QWidget>
#include <QFormLayout>
#include <QMdiArea>
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QFontComboBox>
#include <QLabel>
#include <QDockWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QTabWidget>
#include <QFont>
#include <QTabBar>
#include <QStatusBar>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

#include "Editeur.h"


class FenPrincipale : public QMainWindow
{
    Q_OBJECT
public:
    FenPrincipale();

public slots:
    void addOnglet();
    void changerPolice(QFont police);
    void supprimerOnglet(int index);
    void montrerAbout();
    void changerCurrTab(int index);
    void marquerChangement(int index);
    void ouvrirPreferences();
    void sauvegarderFichier();

private:
    void creerMenu();
    void creerActions();
    void creerToolBars();
    void creerMdi();
    void creerStatusBar();

    // Menu ----------------
    QMenu* menuFichier;
    QMenu* menuEdition;
    QMenu* menuAffichage;
    QMenu* menuAide;

    // Actions -------------
    QAction* actionNouvelOnglet;
    QAction* actionOuvrir;
    QAction* actionSauvegarder;
    QAction* actionSauvegarderComme;
    QAction* actionQuitter;
    QAction* actionPreferences;
    QAction* actionAbout;

    // Toolbars ------------
    QToolBar* m_toolBarFichier;

    // Statusbar -----------
    QStatusBar* m_statusBar;


    QTabWidget* m_zoneCentrale;
    QTextEdit* m_currTextTab;
    QFontComboBox* m_toolBarChoixPolice;
    bool m_unsaved;
    int m_lastIndex;

};

#endif // FENPRINCIPALE_H
