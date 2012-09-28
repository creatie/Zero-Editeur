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
    void marquerChangement();

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
    QAction* actionQuitter;
    QAction* actionPreferences;
    QAction* actionAbout;

    // Toolbars ------------
    QToolBar* m_toolBarFichier;


    QTabWidget* m_zoneCentrale;
    QTextEdit* m_currTextTab;
    QFontComboBox* m_toolBarChoixPolice;
    bool m_unsaved;

};

#endif // FENPRINCIPALE_H
