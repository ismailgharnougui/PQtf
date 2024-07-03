#ifndef MATERIAUX_H
#define MATERIAUX_H
#include<QString>
#include<QSqlQueryModel>
#include<QDate>
#include <QtCharts>
class Materiaux
{
 public:
    Materiaux();
    //constructeurs paramétrés
    Materiaux(int,QString,QString,QString,int,QDate);
    int get_id();
    int get_quantite();
    QString get_nom();
    QString get_localisation();
    QString get_categorie();
    QDate get_dateAjout();


    void set_id(int);
    void set_nom(QString);
    void set_quantite(int);
    void set_localisation(QString);
    void set_categorie(QString);
    void set_dateAjout(QDate);

    bool ajouterMateriaux();
    bool supprimerMateriaux(int id);
    bool modifierMateriaux(int id);
    QSqlQueryModel* selectMateriauxById(int id);
    QSqlQueryModel*  afficherMateriaux();
    bool idDisponible(int);
    bool nomDisponible(QString);
bool CategorieDisponible(QString);
bool rech(QString);
bool tri(QString);
QtCharts::QChartView* statistique();
private:
    int id,quantite;
    QString nom, localisation,categorie;
    QDate dateAjouter;
};

#endif // MATERIAUX_H
