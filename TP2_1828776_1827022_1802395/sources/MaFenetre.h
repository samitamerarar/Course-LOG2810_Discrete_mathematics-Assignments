/*
Fichier: MaFenetre.h
Auteur(s): Tamer Arar, Eric Chao et Guy-Frank
Date de creation: 27 mars 2017
Description: L'interface globale du programme, elle contient la fenetre dans laquelle,
                au fur et a mesure que l'on ecrit du texte,
                il y a presence de suggestions de mots et/ou d'autocorrection.
*/

#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include "Automate.h"

class MaFenetre : public QWidget
{
    Q_OBJECT

    public:
    MaFenetre();
    void compteur(QString mot);

    public slots:
    void remplirSuggestion(std::vector<std::string> vec); //remplissage de mots suggerés
                                                          //dans la fenetre
    void genererAutomate();
    void retour();

    void ecrireDuTexte(bool correctionOnly);
    void fonctionnalite1();
    void fonctionnalite2();
    void fonctionnalite3();
    void fSuggestion();
    void fCorrection();
    void fSuggestionEtCorrection();

    signals:
    void suggestionTab(std::vector<std::string>);

    private:
    QTextEdit *textEdit;
    Automate *automate;
    QListWidget *list;
    QLabel *suggestion;
    int temp_=0, preTemp_=0, compteur_=0;
    bool moreThanOne = false;

    QPushButton* bGenererAutomate;
    QPushButton* bSuggestion;
    QPushButton* bCorrection;
    QPushButton* bSuggestionCorrection;
    QPushButton* bRetour;
    QPushButton* bQuitter;

    QVBoxLayout* mainLayout;
    QHBoxLayout* textEditLayout;
    QVBoxLayout* textLayout;
    QVBoxLayout* suggestionLayout;
};

#endif
