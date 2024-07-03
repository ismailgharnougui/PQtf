#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#pragma once

#include "NotificationLayout.h"
#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();

    void on_modifier_clicked();

    void on_supprimer_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_recherchepar_2_clicked();

    void on_pushButton_tir_2_clicked();

    void on_statistique_clicked();

    void on_PDF_clicked();

    void on_historique_clicked();

    void on_pushButton_success_clicked();
void on_pushButtonModifier_success_clicked();
void on_pushButtonSupprimer_success_clicked();
private:
    Ui::MainWindow *ui;
    NotificationLayout notificationLayout;


};

#endif // MAINWINDOW_H
