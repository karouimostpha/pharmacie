#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("PROJETCPP2A39");
db.setUserName("SYSTEM");//inserer nom de l'utilisateur
db.setPassword("esprit24");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::closeConnection()
{
    db.close();
}
