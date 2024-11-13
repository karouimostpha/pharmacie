#include "employee.h"
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QSqlError>

// Constructeur par défaut : initialise les valeurs par défaut
Employee::Employee()
    : id_E(0), salaire(0.0), codePin(0) {}
// Constructeur avec paramètres
Employee::Employee(QString nom, QString prenom, QString poste, QString sexe, double salaire, int codePin)
    : nom(nom), prenom(prenom), poste(poste), sexe(sexe), salaire(salaire), codePin(codePin) {}

int Employee::getId_E() const { return id_E; }
void Employee::setId_E(int val) { id_E = val; }
QString Employee::getNom() const { return nom; }
void Employee::setNom(QString val) { nom = val; }
QString Employee::getPrenom() const { return prenom; }
void Employee::setPrenom(QString val) { prenom = val; }
QString Employee::getPoste() const { return poste; }
void Employee::setPoste(QString val) { poste = val; }
QString Employee::getSexe() const { return sexe; }
void Employee::setSexe(QString val) { sexe = val; }
double Employee::getSalaire() const { return salaire; }
void Employee::setSalaire(double val) { salaire = val; }
int Employee::getCodePin() const { return codePin; }
void Employee::setCodePin(int val) { codePin = val; }


 // Préparation de la requête SQL pour insérer un nouvel employé
bool Employee::add()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Employee (NOM, PRENOM, POSTE, SEXE, SALAIRE, CODEPIN) "
                  "VALUES ( :nom, :prenom, :poste, :sexe, :salaire, :codePin)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":sexe", sexe);
    query.bindValue(":salaire", salaire);
    query.bindValue(":codePin", codePin);
    return query.exec();// Exécution de la requête
}

QSqlQueryModel* Employee::display()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Employee");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_E"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("POSTE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("CODEPIN"));
    return model;
}


bool Employee::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Employee WHERE ID_E = :id");// Requête pour supprimer un employé par ID
    query.bindValue(":id", id);
    return query.exec();
}
//modifier
bool Employee::update(int id, QString nom, QString prenom, QString poste, QString sexe, double salaire, int codePin)
{
    QSqlQuery query;
    query.prepare("UPDATE Employee SET NOM = :nom, PRENOM = :prenom, POSTE = :poste, SEXE = :sexe, SALAIRE = :salaire, CODEPIN = :codePin WHERE ID_E = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":sexe", sexe);
    query.bindValue(":salaire", salaire);
    query.bindValue(":codePin", codePin);
    return query.exec();
}


QSqlQueryModel* Employee::rechercher(int ID_E) {
    // Création d'un modèle de requête
    QSqlQueryModel* model = new QSqlQueryModel();

    // Préparation de la requête SQL pour rechercher par ID_E
    QSqlQuery query;
    query.prepare("SELECT ID_E, NOM, PRENOM, POSTE, SEXE, SALAIRE, CODEPIN FROM Employee WHERE ID_E = :ID_E");
    query.bindValue(":ID_E", ID_E);

    // Exécution de la requête et gestion des erreurs potentielles
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError();
        return nullptr; // Retourne nullptr en cas d'erreur
    }

    // Affecte la requête au modèle seulement si elle réussit
    model->setQuery(std::move(query));
    if (model->rowCount() == 0) {
        qDebug() << "Aucun employé trouvé avec cet ID_E";
    }

    return model;
}

QSqlQueryModel* Employee::tri_id_E() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYEE ORDER BY ID ASC");
    return model;
}
