#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "employee.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked(); // Bouton pour ajouter un employé

    void on_pushButton_2_clicked();//Bouton pour modifier un employé

    void on_pushButton_3_clicked();// Bouton pour supprimer un employé

    void on_tableView_2_activated(const QModelIndex &index);// Activation d'une ligne dans le tableau des employés

    void on_pushButton_8_clicked(); // Autre bouton d'action

    void on_rechercher_clicked();

    void on_trier_clicked(); // pour le tri

private:
    Ui::MainWindow *ui;
    Employee e;
};
#endif // MAINWINDOW_H