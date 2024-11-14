#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include <QMessageBox>
#include <QDebug>
#include <QMessageBox>
#include<QSystemTrayIcon>
#include <QRegularExpression>
#include "connection.h"
#include <QFileDialog>
#include <QRegularExpressionValidator>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->tableView_2->setModel(e.display());
    // cs //
    ui->codepin->setValidator(new QIntValidator(0,999999,this));
    ui->salaire->setValidator(new QIntValidator(0,999999,this));

    QRegularExpression rx("[a-zA-Z]+");  // Adjust regex as needed
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->nom->setValidator(validator);
    ui->prenom->setValidator(validator);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//ajouter
void MainWindow::on_pushButton_clicked()
{
    QString nom =ui->nom->text();
    QString prenom =ui->prenom->text();
    QString poste =ui->poste->text();
    int salaire =ui->salaire->text().toInt();
    int codepin =ui->codepin->text().toInt();
    QString sexe =ui->comboBox->currentText();
    Employee e(nom,prenom,poste,sexe,salaire,codepin);
    bool test=e.add();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("ajoute \n"
                                             "click to cancel"), QMessageBox::Cancel);
        ui->nom->clear();
        ui->prenom->clear();
        ui->poste->clear();
        ui->salaire->clear();
        ui->codepin->clear();
        ui->tableView_2->setModel(e.display());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok") , QObject::tr("non effecue"),QMessageBox::Cancel);
}
//modifier
void MainWindow::on_pushButton_2_clicked()
{
    int id = ui->id->text().toInt();
    QString nom =ui->nom->text();
    QString prenom =ui->prenom->text();
    QString poste =ui->poste->text();
    int salaire =ui->salaire->text().toInt();
    int codepin =ui->codepin->text().toInt();
    QString sexe =ui->comboBox->currentText();
    bool test=e.update(id ,nom,prenom,poste,sexe,salaire,codepin);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("modifié \n"
                                             "click to cancel"), QMessageBox::Cancel);
        ui->nom->clear();
        ui->prenom->clear();
        ui->poste->clear();
        ui->salaire->clear();
        ui->codepin->clear();
        ui->tableView_2->setModel(e.display());
    }
else
    QMessageBox::critical(nullptr,QObject::tr("not ok"),
                          QObject::tr("modification non effectué"),QMessageBox::Cancel);
}
// supprimer
void MainWindow::on_pushButton_3_clicked()
{
    int id =ui->id->text().toUInt();
    bool test=e.remove(id);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Supprimé \n"
                                             "click to cancel"), QMessageBox::Cancel);
        ui->id->clear();
        ui->tableView_2->setModel(e.display());
    }
    else
    QMessageBox::critical(nullptr,QObject::tr("not ok"),
                          QObject::tr("suppression non effectué"),QMessageBox::Cancel);
}
// remplissage auto
void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{
    QString val=ui->tableView_2->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from Employee  where ID_E='"+val+"' or nom='"+val+"' or prenom='"+val+"' or salaire='"+val+"' or codepin='"+val+"'");
    if (qry.exec())
    { while (qry.next())
        {
            //update
            //id
            ui->id->setText(qry.value(0).toString());
            ui->nom->setText(qry.value(1).toString());
            ui->prenom->setText(qry.value(2).toString());
            ui->poste->setText(qry.value(3).toString());
            ui->salaire->setText(qry.value(5).toString());
            ui->codepin->setText(qry.value(6).toString());
            //delete
            //id
            ui->id->setText(qry.value(0).toString());
        }
    }
}
// actualiser
void MainWindow::on_pushButton_8_clicked()
{
    ui->tableView_2->setModel(e.display());
}


void MainWindow::on_rechercher_clicked() {
    int id = ui->recherche->text().toInt(); // Supposons que 'recherche' est le champ de saisie pour l'ID

    qDebug() << "ID_E recherché :" << id;
    QSqlQueryModel* model = e.rechercher(id);

    if (model && model->rowCount() > 0) {
        ui->tableView_2->setModel(model);
    } else {
        QMessageBox::information(this, "Recherche", "Aucun employé trouvé avec cet ID.");
    }
}

void MainWindow::on_trier_clicked() {
    QSqlQueryModel *model = e.tri_id_E();
    ui->tableView_2->setModel(model);
}


