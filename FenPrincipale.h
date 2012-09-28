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
    void deleteOnglet(int index);
    void montrerAbout();
    void changerCurrTab(int index);
    void marquerChangement();

private:
    QTabWidget* m_zoneCentrale;

    QTextEdit* m_currTextTab;
    QFontComboBox* m_toolBarChoixPolice;
    QToolBar* m_toolBarFichier;

    int m_tabCount; // compte le nombre d'onglets ouverts
    bool m_unsaved;

    // actions

};

#endif // FENPRINCIPALE_H
