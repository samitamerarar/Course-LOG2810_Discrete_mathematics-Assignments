#include "MaFenetre.h"
#include <QFileDialog>
#include <QMessageBox>

MaFenetre::MaFenetre() : QWidget()
{
    mainLayout = new QVBoxLayout(this);

    bGenererAutomate = new QPushButton("Générer Automate");
    bSuggestion = new QPushButton("Suggestion");
    bCorrection = new QPushButton("Correction");
    bSuggestionCorrection = new QPushButton("Suggestion + Correction");
    bRetour = new QPushButton("Retour");
    bQuitter = new QPushButton("Quitter");

    bSuggestion->hide();
    bCorrection->hide();
    bSuggestionCorrection->hide();
    bRetour->hide();

    mainLayout->addWidget(bGenererAutomate);
    mainLayout->addWidget(bSuggestion);
    mainLayout->addWidget(bCorrection);
    mainLayout->addWidget(bSuggestionCorrection);
    mainLayout->addWidget(bRetour);
    mainLayout->addWidget(bQuitter);

    QObject::connect(bGenererAutomate, SIGNAL(released()), this, SLOT(genererAutomate()));
    QObject::connect(bSuggestion, SIGNAL(released()), this, SLOT(fonctionnalite1()));
    QObject::connect(bCorrection, SIGNAL(released()), this, SLOT(fonctionnalite2()));
    QObject::connect(bSuggestionCorrection, SIGNAL(released()), this, SLOT(fonctionnalite3()));
    QObject::connect(bRetour, SIGNAL(released()), this, SLOT(retour()));
    QObject::connect(bQuitter, SIGNAL(released()), this, SLOT(close()));
}

/**
Demande a l'usager le nom du fichier et genere l'automate a l'aide de ce nom du fichier.

@return void.
*/
void MaFenetre::genererAutomate()
{
    QString nom = QFileDialog::getOpenFileName(
                this,
                tr("Choisir lexique"),
                "C://",
                "Fichiers textes (*.txt);; Tous les fichiers (*.*)");

    automate = new Automate();
    if (automate->lireLexique(nom.toStdString()) == true) {
        automate->creerAutomate();
        bSuggestion->show();
        bCorrection->show();
        bSuggestionCorrection->show();
        QMessageBox::information(this, "Succès!", "Le lexique a été chargé!");
    }
    else {
        QMessageBox::warning(this, "Erreur!", "Erreur du fichier!");
        bSuggestion->hide();
        bCorrection->hide();
        bSuggestionCorrection->hide();
    }

    adjustSize();
}

/**
Retour au menu principal.

@return void.
*/
void MaFenetre::retour()
{
    //supprime le layer de la saisie du texte
    QLayoutItem* enfant;

    while ((enfant = textLayout->takeAt(0)) != 0) {
        enfant->widget()->deleteLater();
        delete enfant;
    }

    while ((enfant = suggestionLayout->takeAt(0)) != 0) {
        enfant->widget()->deleteLater();
        delete enfant;
    }

    while ((enfant = textEditLayout->takeAt(0)) != 0) {
        enfant->widget()->deleteLater();
        delete enfant;
    }

    bGenererAutomate->show();
    bSuggestion->show();
    bCorrection->show();
    bSuggestionCorrection->show();
    bRetour->hide();

    adjustSize();
}

/**
Prepare l'interface pour laisser de la place a la saisie du texte.

@return void.
*/
void MaFenetre::ecrireDuTexte(bool correctionOnly)
{
    textEditLayout = new QHBoxLayout(this);
    suggestionLayout = new QVBoxLayout(this);
    textLayout = new QVBoxLayout(this);

    textEdit = new QTextEdit(this);
    textEdit->setFixedSize(370, 180);

    list = new QListWidget(this);
    list->setFixedSize(130, 180);

    textLayout->addWidget(new QLabel("Éditeur de texte:"));
    textLayout->addWidget(textEdit);

    textEditLayout->addLayout(textLayout);

    if(!correctionOnly) {
        suggestionLayout->addWidget(new QLabel("Suggestions de mots:", this));
        suggestionLayout->addWidget(list);
        textEditLayout->addLayout(suggestionLayout);
    }

    mainLayout->addLayout(textEditLayout);
}

/**
Prepare l'interface et fait l'appel a la methode fSuggestion().

@return void.
*/
void MaFenetre::fonctionnalite1()
{
    bGenererAutomate->hide();
    bSuggestion->hide();
    bCorrection->hide();
    bSuggestionCorrection->hide();
    bRetour->show();
    ecrireDuTexte(false);

    QObject::connect(textEdit, SIGNAL(textChanged()), this, SLOT(fSuggestion()));
    QObject::connect(this, SIGNAL(suggestionTab(std::vector<std::string>)), this, SLOT(remplirSuggestion(std::vector<std::string>)));
}

/**
Prepare l'interface et fait l'appel a la methode fCorrection().

@return void.
*/
void MaFenetre::fonctionnalite2()
{
    bGenererAutomate->hide();
    bSuggestion->hide();
    bCorrection->hide();
    bSuggestionCorrection->hide();
    bRetour->show();
    ecrireDuTexte(true);

    QObject::connect(textEdit, SIGNAL(textChanged()), this, SLOT(fCorrection()));
    QObject::connect(this, SIGNAL(suggestionTab(std::vector<std::string>)), this, SLOT(remplirSuggestion(std::vector<std::string>)));
}

/**
Prepare l'interface et fait l'appel a la methode fSuggestionEtCorrection().

@return void.
*/
void MaFenetre::fonctionnalite3()
{
    bGenererAutomate->hide();
    bSuggestion->hide();
    bCorrection->hide();
    bSuggestionCorrection->hide();
    bRetour->show();
    ecrireDuTexte(false);

    QObject::connect(textEdit, SIGNAL(textChanged()), this, SLOT(fSuggestionEtCorrection()));
    QObject::connect(this, SIGNAL(suggestionTab(std::vector<std::string>)), this, SLOT(remplirSuggestion(std::vector<std::string>)));
}

/**
Methode appelé quand le texte en entrée se change
Elle genere la suggestion de mots.

@return void.
*/
void MaFenetre::fSuggestion()
{
    QString mot = textEdit->toPlainText(); //retourne le mot écrit

    compteur(mot); //On compte les espaces

    if (mot.length() >=2) {

        // S'il y a au moins un espace et que l'avant dernier caractère est un espace alors ily a plus d'un mot
        if(mot[mot.length()-2] == ' ' && compteur_ >= 1)
        {
            moreThanOne = true;
        }
        else if (compteur_ == 0)
        {
            moreThanOne = false;
        }
    }

    std::vector<std::string> vect;

    // S'il y a juste un mot ou que le dernier caractère est un espace
    if (moreThanOne == false || mot[mot.length()-1] == ' ') {
            vect = automate->retournerSuggestions(mot.toStdString());
        }
        // S'il y a plus d'un caractère et que le dernier caractère n'est pas un espace
        else if (moreThanOne && mot[mot.length()-1] != ' ') {
            // on sélectionne le dernier mot en particulier
            vect = automate->retournerSuggestions(mot.mid(temp_+1).toStdString());
        }

    emit suggestionTab(vect);
}

/**
Methode appelé quand le texte en entrée se change
Elle corrige automatiquement le mot entré à la suite d'un espace.

@return void.
*/
void MaFenetre::fCorrection()
{
    QString mot = textEdit->toPlainText(); //retourne le mot écrit

    compteur(mot); //On compte les espaces

    if (mot.length() >=2) {

        // S'il y a au moins un espace et que l'avant dernier caractère est un espace alors ily a plus d'un mot
        if(mot[mot.length()-2] == ' ' && compteur_ >= 1)
        {
            moreThanOne = true;
        }
        else if (compteur_ == 0)
        {
            moreThanOne = false;
        }
    }

    QString newWord; // mot sans espace
    QString newWordC; // mot sans espace corrigé

    if (moreThanOne == false) // S'il y a juste un mot
    {
        newWord = mot.mid(0, mot.length()-1);
        newWordC = QString::fromStdString(automate->corrigerLeMot(newWord.toStdString()));
    }
    else if (moreThanOne) // S'il y a plus d'un mot
    {
        newWord = mot.mid(preTemp_+1, temp_-preTemp_-1); // on le sélectionne particulièrement
        newWordC = QString::fromStdString(automate->corrigerLeMot(newWord.toStdString()));
    }

    int temp = temp_;
    int preTemp = preTemp_;

    //S'il y a juste un mot et qu'il est mal écrit on le supprime on le remplace par sa correction
    if (mot.length()-1 >= 1 && mot[mot.length()-1] == ' ' && newWord != newWordC && moreThanOne == false) {
        for(int i = 0; i < (temp-preTemp+1);i++) {
            // supression
            textEdit->textCursor().deletePreviousChar();
        }
        textEdit->textCursor().insertText(newWordC + " "); // remplacement plus d'un espace
    }
    // S'il y a plus d'un mot
    else if (mot.length()-1 >= 1 && mot[mot.length()-1] == ' ' && moreThanOne && newWord != newWordC) {
        for (int i = 0; i < newWordC.toStdString().length()+1; i++) {
            textEdit->textCursor().deletePreviousChar();
        }
        textEdit->textCursor().insertText(newWordC + " ");
    }
}

/**
Methode appelé quand le texte en entrée se change
Elle corrige automatiquement le mot entré à la suite d'un espace.
Et elle genere la suggestion de mots.

@return void.
*/
void MaFenetre::fSuggestionEtCorrection()
{

    QString mot = textEdit->toPlainText(); //retourne le mot écrit

    compteur(mot); //On compte les espaces

    if (mot.length() >=2) {

        // S'il y a au moins un espace et que l'avant dernier caractère est un espace alors ily a plus d'un mot
        if(mot[mot.length()-2] == ' ' && compteur_ >= 1) 
        {
            moreThanOne = true;
        }
        else if (compteur_ == 0)
        {
            moreThanOne = false;
        }
    }

    std::vector<std::string> vect;

    QString newWord; // mot sans espace
    QString newWordC; // mot sans espace corrigé

    if (moreThanOne == false) // S'il y a juste un mot
    {
        newWord = mot.mid(0, mot.length()-1);
        newWordC = QString::fromStdString(automate->corrigerLeMot(newWord.toStdString()));
    }
    else if (moreThanOne) // S'il y a plus d'un mot
    {
        newWord = mot.mid(preTemp_+1, temp_-preTemp_-1); // on le sélectionne particulièrement
        newWordC = QString::fromStdString(automate->corrigerLeMot(newWord.toStdString()));
    }

    int temp = temp_;
    int preTemp = preTemp_;

    //S'il y a juste un mot et qu'il est mal écrit on le supprime on le remplace par sa correction
    if (mot.length()-1 >= 1 && mot[mot.length()-1] == ' ' && newWord != newWordC && moreThanOne == false) {
        for(int i = 0; i < (temp-preTemp+1);i++) {
            // supression
            textEdit->textCursor().deletePreviousChar();
        }
        textEdit->textCursor().insertText(newWordC + " "); // remplacement plus d'un espace
    }
    // S'il y a plus d'un mot
    else if (mot.length()-1 >= 1 && mot[mot.length()-1] == ' ' && moreThanOne && newWord != newWordC) {
        for (int i = 0; i < newWordC.toStdString().length()+1; i++) {
            textEdit->textCursor().deletePreviousChar();
        }
        textEdit->textCursor().insertText(newWordC + " ");
    }

    // S'il y a juste un mot ou que le dernier caractère est un espace
    if (moreThanOne == false || mot[mot.length()-1] == ' ') {
            vect = automate->retournerSuggestions(mot.toStdString());
        }
        // S'il y a plus d'un caractère et que le dernier caractère n'est pas un espace
        else if (moreThanOne && mot[mot.length()-1] != ' ') {
            // on sélectionne le dernier mot en particulier
            vect = automate->retournerSuggestions(mot.mid(temp_+1).toStdString());
        }

    emit suggestionTab(vect);
}

/**
Prend le vecteur de mots suggeres, le decortique et l'affiche dans la fenetre
de suggestions.

@param vec Le vecteur contenant la liste de mots suggeres.
@return void.
*/
void MaFenetre::remplirSuggestion(std::vector<std::string> vec)
{
    list->clear();

    for (int  i = 0 ; i < vec.size(); i++)
    {
        QString temp = QString::fromStdString(vec[i]);
        list->addItem(temp);
    }
}

/**
compteur d'espaces qui affecte à temp la position de l'espace le plus récent
et à preTemp l'espace précédant.

@param mot Le mot tapé par l'utilisateur.
@return void.
*/
void MaFenetre::compteur(QString mot)
{
    int compteur=0, preTemp=0, temp=0;

    for (int i=0;i<mot.length();i++)
    {
        if (mot[i] == ' ')
        {
            if (compteur >= 1) // S'il y a deux espaces, on affecte preTemp la position précédante
            {
                preTemp = temp;
                temp = i;
            }
            else
            {
                temp = i;
                compteur++;
            }
        }
    }
    temp_ = temp;
    preTemp_ = preTemp;
    compteur_ = compteur;
}
