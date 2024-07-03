#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "materiaux.h"
#include<QMessageBox>
#include <QMessageBox>
#include <QIntValidator>
#include <QDate>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlQuery>
#include<QTableView>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgGenerator>
#include "notification.h"
#include "notificationmanager.h"
#include <QApplication>
#include <QScreen>

#include <QThread>
#include <QTimer>
#include <QTextCursor>
#include "Result.h"
#include "Operation.h"
#include <QToolTip>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   Materiaux M;

    ui->setupUi(this);
    ui->tableView->setModel(M.afficherMateriaux());
    ui->le_id->setValidator(new QIntValidator(0, 9999999, this));

    ui->le_quantite->setValidator(new QIntValidator(0, 9999999, this));
    //ui->le_quantite_2->setValidator(new QIntValidator(0, 9999999, this));

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_ajouter_clicked()
{

    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString localisation=ui->le_localisation->text();
    QString categorie = ui->le_categorie->currentText();
    int quantite=ui->le_quantite->text().toInt();
    QDate dateAjouter = QDate::currentDate(); // Pas besoin de utiliser setDate() ici
    Materiaux M(id,nom, localisation, categorie, quantite, dateAjouter);
    bool test=M.ajouterMateriaux();
    if(test)
   {
        ui->tableView->setModel(M.afficherMateriaux());

      QMessageBox::information(nullptr, QObject::tr("ok"),
      QObject::tr("ajout effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);

     ui->le_id->clear();
     ui->le_nom->clear();
     ui->le_localisation->clear();
     ui->le_categorie->setCurrentIndex(0);
     ui->le_quantite->clear();
     ui->le_dateAjouter->clear();

     QFile file("C:/Users/ismae/OneDrive/Bureau/SIWAR/kiné/img/historique.txt");
     if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
         qDebug() << "Erreur lors de l'ouverture du fichier historique.txt";
         return;
     }

     QTextStream cout(&file);
     QString d_info = QDateTime::currentDateTime().toString();
     QString idAsString = QString::number(id); // Conversion de l'id en QString
     QString message2 = d_info + " Une materiel a été ajoutée avec l'ID  " + idAsString + "\n";
     cout << message2;

         on_pushButton_success_clicked();

   }
    else
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("ajout non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);
}
#include "NotificationWidget.h"
#include "notificationlayout.h"
void MainWindow::on_pushButton_success_clicked()
{

    NotificationParams params;
    params.title = "materiel a été ajoutée avec succées";
    params.message = Operation::DoSomething(Result::RESULT_SUCCESS);
    params.detailsButtonText = "Try again";
    notificationLayout.AddNotificationWidget(this, params);
}
void MainWindow::on_pushButtonModifier_success_clicked()
{

    NotificationParams params;
    params.title = "materiel a été modifiée avec succées";
    params.message = Operation::DoSomething(Result::RESULT_SUCCESS);
    params.detailsButtonText = "Try again";
    notificationLayout.AddNotificationWidget(this, params);
}
void MainWindow::on_pushButtonSupprimer_success_clicked()
{

    NotificationParams params;
    params.title = "materiel a été supprimée avec succées";
    params.message = Operation::DoSomething(Result::RESULT_SUCCESS);
    params.detailsButtonText = "Try again";
    notificationLayout.AddNotificationWidget(this, params);
}

void MainWindow::on_modifier_clicked()
{


        int id = ui->le_id->text().toInt();
        QString nom = ui->le_nom->text();
        QString localisation = ui->le_localisation->text();
        QString categorie = ui->le_categorie->currentText();
        int quantite = ui->le_quantite->text().toInt();
        QDate dateAjouter = ui->le_dateAjouter->date();

        Materiaux M(id, nom, localisation, categorie, quantite, dateAjouter);

        bool test = M.modifierMateriaux(id);
        if (test) {
            // Rafraîchir le modèle de TableView pour refléter les modifications
            ui->tableView->setModel(M.afficherMateriaux());
            QMessageBox::information(this, tr("Modification réussie"),
                                     tr("La ligne a été modifiée avec succès."),
                                     QMessageBox::Ok);


            QFile file("C:/Users/ismae/OneDrive/Bureau/SIWAR/kiné/img/historique.txt");
            if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                qDebug() << "Erreur lors de l'ouverture du fichier historique.txt";
                return;
            }

            QTextStream cout(&file);
            QString d_info = QDateTime::currentDateTime().toString();
            QString idAsString = QString::number(id); // Conversion de l'id en QString
            QString message2 = d_info + " -Un matriel a été modifier avec l'ID " + idAsString + "\n";
            cout << message2;
on_pushButtonModifier_success_clicked();
        } else {
            QMessageBox::critical(this, tr("Erreur de modification"),
                                  tr("La modification de la ligne a échoué."),
                                  QMessageBox::Ok);
        }

        // Effacer les champs après la modification
        ui->le_id->clear();
        ui->le_nom->clear();
        ui->le_localisation->clear();
        ui->le_categorie->setCurrentIndex(0); // Réinitialiser la sélection de la catégorie
        ui->le_quantite->clear();
        ui->le_dateAjouter->setDate(QDate::currentDate()); // Réinitialiser la date
    }


void MainWindow::on_supprimer_clicked()
{


   QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, tr("Aucune ligne sélectionnée"),
                             tr("Veuillez sélectionner une ligne à supprimer."),
                             QMessageBox::Ok);
        return;
    }


    int id = selectedRows.at(0).data().toInt();
   Materiaux M;

   bool test=M.supprimerMateriaux(id);
   if(test)
  {
      ui->tableView->setModel(M.selectMateriauxById(id));//refresh
     QMessageBox::information(nullptr, QObject::tr("ok"),
     QObject::tr("suppression effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);
ui->tableView->setModel(M.selectMateriauxById(id));//refresh


QFile file("C:/Users/ismae/OneDrive/Bureau/SIWAR/kiné/img/historique.txt");
if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
    qDebug() << "Erreur lors de l'ouverture du fichier historique.txt";
    return;
}
QTextStream cout(&file);
QString d_info = QDateTime::currentDateTime().toString();
QString idAsString = QString::number(id); // Conversion de l'id en QString
QString message2 = d_info + " - Un matériel a été supprimé avec l'ID " + idAsString + "\n";
cout << message2;
on_pushButtonSupprimer_success_clicked();

  }
   else
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("suppression non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_4_clicked()
{
    Materiaux M;
    ui->tableView->setModel(M.afficherMateriaux());//refresh

}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{


       // Get data from the selected index
        int id = index.sibling(index.row(), 0).data().toInt(); // Column 4 (quantite)
        QString nom = index.sibling(index.row(), 1).data().toString(); // Column 1 (nom)
        QString localisation = index.sibling(index.row(), 2).data().toString(); // Column 2 (localisation)
        QString categorie = index.sibling(index.row(), 3).data().toString(); // Column 3 (categorie)
        int quantite = index.sibling(index.row(), 4).data().toInt(); // Column 4 (quantite)
        QDate dateAjouter = index.sibling(index.row(), 5).data().toDate(); // Column 5 (dateAjouter)

        // Populate line edit fields with the retrieved data
        ui->le_id->setText(QString::number(id));
        ui->le_nom->setText(nom);
        ui->le_localisation->setText(localisation);
        ui->le_categorie->setCurrentText(categorie);
        ui->le_quantite->setText(QString::number(quantite));
        ui->le_dateAjouter->setDate(dateAjouter);
}



//Recherche multicritère
void MainWindow::on_pushButton_recherchepar_2_clicked() {
    Materiaux M;

    int index = ui->comboBox_rech_2->currentIndex();
    QString wh;
    QSqlQueryModel* model = new QSqlQueryModel();
    QString k = ui->lineEdit_rech_2->text().trimmed(); // Trimmed to remove leading and trailing whitespace

    if (k.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Empty field.\nClick Cancel to exit."), QMessageBox::Cancel);
        return;
    }

    if (index == 0) {
        if (!M.idDisponible(k.toInt())) {
            QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("ID unavailable.\nClick Cancel to exit."), QMessageBox::Cancel);
            return;
        }
        wh = "ID=" + k;
    } else if (index == 1) {
        wh = "NOM='" + k + "'";
    } else if (index == 2) {
        wh = "CATEGORIE='" + k + "'";
    }
    if (M.rech(wh)) {
        QMessageBox::information(nullptr, QObject::tr("Success"), QObject::tr("Search performed.\nClick Cancel to exit."), QMessageBox::Cancel);
        model->setQuery("SELECT * FROM Materiaux WHERE " + wh);
        ui->tableView->setModel(model);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Search failed.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_pushButton_tir_2_clicked()
{Materiaux M;
    int index=ui->comboBox_trier_2->currentIndex();
       QString orderByClause;
       QSqlQueryModel* model=new QSqlQueryModel();
       if (index == 0) {
                   orderByClause = " ORDER BY ID DESC";
               } else if (index == 1) {
                   orderByClause = " ORDER BY QUANTITE ASC";
               } else if (index == 2) {
                   orderByClause = " ORDER BY CATEGORIE ASC";
               }

       if (M.tri(orderByClause)) {
           QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Tri effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
            model->setQuery("SELECT *  FROM Materiaux"+orderByClause);
           ui->tableView->setModel(model);
       } else {
          QMessageBox::critical(nullptr,QObject::tr(" not ok"),QObject::tr("tri non effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
       }

   }
void MainWindow::on_statistique_clicked()
{
    // Créez un modèle pour exécuter les requêtes SQL
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT COUNT(*) FROM Materiaux WHERE CATEGORIE='k'");
    int dispo1 = model->data(model->index(0, 0)).toInt();

    model->setQuery("SELECT COUNT(*) FROM Materiaux WHERE CATEGORIE='e'");
    int dispo2 = model->data(model->index(0, 0)).toInt();

    model->setQuery("SELECT COUNT(*) FROM Materiaux WHERE CATEGORIE='n'");
    int dispo3 = model->data(model->index(0, 0)).toInt();

    int total = dispo1 + dispo2 + dispo3;

    // Créez une série de diagramme circulaire (Pie Chart)
    QPieSeries *series = new QPieSeries();
    if (dispo1 > 0)
        series->append("k", dispo1);
    if (dispo2 > 0)
        series->append("e", dispo2);
    if (dispo3 > 0)
        series->append("n", dispo3);

    // Configurez les étiquettes pour les tranches avec des données
    for (QPieSlice *slice : series->slices())
    {
        slice->setLabelVisible();
    }
    // Créez un graphique et configurez-le
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des CATEGORIE dES Materiaux");
    // Créez une vue de graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 500);
    chartView->show();
}


void MainWindow::on_PDF_clicked()
{
    QPdfWriter pdf("C:/Users/ismae/OneDrive/Bureau/SIWAR/kiné/list-materiaux.pdf");

        QPainter painter(&pdf);
               int i = 4000;
               painter.setPen(Qt::black);
               painter.setFont(QFont("Book Script", 20, QFont::Bold));
               painter.drawText(2500, 1400, "LISTE DES MATERIAUX");
               painter.setPen(Qt::darkGreen);
               painter.setFont(QFont("Time New Roman", 10));
               painter.drawRect(100, 100, 9200, 2700); // dimension ta3 rectangle
               painter.drawRect(100, 3000, 9200, 500);

               painter.drawText(300,3300,"ID");
               painter.drawText(1000,3300,"NOM");
               painter.drawText(2500,3300,"LOCALISATION");
               painter.drawText(4500,3300,"CATEGORIE");
               painter.drawText(6000,3300,"QUANTITE");
               painter.drawText(7500,3300,"DATE D'AJOUT");
               QImage image("C:/Users/ismae/OneDrive/Bureau/SIWAR/kiné/img/logoEsprit.png");
               painter.drawImage(QRectF(200, 200, 2000, 2000), image);
               QImage image1("C:/Users/ismae/OneDrive/Bureau/SIWAR/kiné/img/FlexTrack.png");
               painter.drawImage(QRectF(7000, 200, 2000, 2000), image1);
               painter.drawRect(100, 3700, 9200, 9000);
               QSqlQuery query;
               query.prepare("select * from MATERIAUX");
               query.exec();
               while (query.next())
               {
                   painter.drawText(300, i, query.value(0).toString());
                   painter.drawText(1000, i, query.value(1).toString());
                   painter.drawText(2500, i, query.value(2).toString());
                   painter.drawText(4500, i, query.value(3).toString());
                   painter.drawText(6000, i, query.value(4).toString());
                   painter.drawText(7500, i, query.value(5).toString());
                   i = i + 350;
               }
               QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                   QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_historique_clicked()
{
    QFile file("C:/Users/ismae/OneDrive/Bureau/SIWAR/kiné/img/historique.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString text = in.readAll();
        file.close();
        // Affichez le texte dans le QTextBrowser
        ui->histo->setPlainText(text); // Remplacez "textBrowser" par le nom de votre QTextBrowser
    } else {
        qDebug() << "Impossible d'ouvrir le fichier.";
    }
}
