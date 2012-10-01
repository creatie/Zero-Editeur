#include "Editeur.h"



Editeur::Editeur()
{
}



Editeur::Editeur(QWidget *parent) :
    QWidget(parent),
    m_layout_editeur(new QHBoxLayout),
    m_box_compteur(new QTextEdit(this)),
    m_box_editeur(new QTextEdit(this)),
    curr_last_line(1)
{

    m_layout_editeur->addWidget(m_box_compteur);
    m_layout_editeur->addWidget(m_box_editeur);




    this->setLayout(m_layout_editeur);
}


