#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QDebug>
#include <QSqlQueryModel>
class Employee
{
public:
    Employee();
    Employee(QString, QString, QString, QString, double, int);

    int getId_E() const;
    void setId_E(int val);
    QString getNom() const;
    void setNom(QString val);
    QString getPrenom() const;
    void setPrenom(QString val);
    QString getPoste() const;
    void setPoste(QString val);
    QString getSexe() const;
    void setSexe(QString val);
    double getSalaire() const;
    void setSalaire(double val);
    int getCodePin() const;
    void setCodePin(int val);

    ///////////// CRUD Operations /////////////////
    bool add();
    bool update(int, QString, QString, QString, QString, double, int);
    bool remove(int id);
    QSqlQueryModel* display();
    QSqlQueryModel* rechercher(int ID_E);
    QSqlQueryModel* tri_id_E();
private:
    int id_E;
    QString nom;
    QString prenom;
    QString poste;
    QString sexe;
    double salaire;
    int codePin;
};

#endif // EMPLOYEE_H
