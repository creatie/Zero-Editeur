#ifndef EDITEUR_H
#define EDITEUR_H

#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>

class Editeur : public QWidget
{
    Q_OBJECT
public:
    Editeur();
    explicit Editeur(QWidget* parent = 0);
    
signals:
    
public slots:
    
private:
    void changerLargeurCompteur();


    QHBoxLayout* m_layout_editeur;
    QTextEdit* m_box_compteur;
    QTextEdit* m_box_editeur;
    int curr_last_line;
};

#endif // EDITEUR_H
