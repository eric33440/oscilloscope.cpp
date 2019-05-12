#include "mycanvas.h"
#include <QPainter>
#include <QColor>
#include <QtMath>
#include <cmath>
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>
#include <QSlider>
#include <QPixmap>
#include <QFile>
#include "serialcapture.h"
#include <QDebug>



// genere l'unite du graphique et possibilité de zoom
QPointF MyCanvas::coo(int x , int y)
{
    return QPointF((x*m_unite*m_zoom)/100,(y*m_unite*m_zoom)/100);
}


// fonction test qui genere une fonction cosinus
double MyCanvas::f(double x)
{
    return m_amplitude*(cos(11*x*m_periode+m_phase));
}

// fonction test qui genere une fonction sinus
double MyCanvas::g(double x)
{
    return m_amplitude*(sin(x*m_periode+m_phase));
}

// la fenetre genere pour le graphique sera fixe en hauteur et largeur
MyCanvas::MyCanvas(QWidget *parent)
{
    setFixedSize(m_largeur+2,m_hauteur+2);
}

// fonction qui dessinnera la courbe et le graphique  et les axes

void MyCanvas::paintEvent(QPaintEvent *)
{
    SerialCapture m_data; // imporatation d'une autre classe les données recues 
    signed i;
    int y=10;
    QPainter feuille(this);
    // 1) Sauvegarde du système de coordonnées
    feuille.save();
    // 2) Translation, rotation dou changement de coordonnées
    feuille.translate(m_largeur/2,m_hauteur/2);
    feuille.scale(1,-1);
    //dessin


    //écriture dans un fichier
    /*QFile file{"courbe.dat"};
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream flux(&file);
    flux.setCodec("UTF-8");
    for (double t=0;t<=4*M_PI; t+=0.01)
    {
        //flux<<"f(cos(t)="<<(cos(t))<<endl;
        flux<<(sin(t))<<endl;
    }*/



    /* lecture du fichier contenant les point d'échantillonage */
    /*QFile file{"courbe.dat"};
    if(!file.open(QIODevice::ReadOnly))
    {
        //cerr<<"Fichier non trouve !"<<endl;
    }
    QTextStream flux(&file);
    //QString all = flux.readAll();
    flux.setCodec("UTF-8");
    //QString ligne;
     lecture du fichier ligne par ligne
    while(! flux.atEnd())
    {
        m_ech.append(flux.readLine().toDouble());


        //traitement de la ligne
    }*/

    //cout<<QObject::tr("%1 échantillons trouvés !").arg(m_ech.size())<<endl;
    //file.close();


    // On choisit le codec correspondant au jeu de caractères que l'on souhaite ; ici, UTF-8


    // Écriture des différentes lignes dans le fichier

    //grille horizontale
    feuille.setPen(Qt::gray);
    for (i=-m_largeur/10;i<m_largeur/10;i+=y)
    {
        feuille.drawLine(coo(i,m_largeur/10),coo(i,-m_largeur/10));
        feuille.drawLine(coo(m_largeur/10,i),coo(-m_largeur/10,i));
    }
    feuille.drawLine(coo(-m_largeur/10,-m_largeur/10),coo(m_largeur/10,-m_largeur/10));
    feuille.drawLine(coo(m_largeur/10,-m_largeur/10),coo(m_largeur/10,m_largeur/10));
    feuille.drawLine(coo(-m_largeur/10,m_largeur/10),coo(m_largeur/10,m_largeur/10));
    /*feuille.drawLine(coo(-49,-49),coo(49,-49));
    feuille.drawLine(coo(49,49),coo(49,-49));*/


    // dessiner dans le pixmap off-screen
    //restauration du systeme de coo
    // ordonnées et abscisse
    feuille.setPen(Qt::blue);
    feuille.drawLine(coo(0,-m_largeur/10),coo(0,m_largeur/10));
    feuille.drawLine(coo(-m_largeur/10,0),coo(m_largeur/10,0));

    //représentation des points envoyer par la stm32
    feuille.setPen(Qt::red);
    for (double var = -100; var < 100; var+=0.5)
    {
        for (unsigned long i=0 ;i<sizeof (m_data);i++)
        {
            feuille.drawLine(coo((double)var,m_amplitude*((double)m_data[i]*m_periode+m_phase)),
                             coo((double)var++,m_amplitude*((double)m_data[i++]*m_periode+m_phase)));
        }


    }
    //feuille.drawLine(coo(10,10),coo(40,20));
    for (double var = -100; var < 100; var+=0.00005)
    {
        feuille.setPen(Qt::red);
        feuille.drawLine(coo(var,f((double)var/1000.0)),
                         coo(var+=((double)m_echantillonage/(double)500000.0),f((var+=((double)m_echantillonage/(double)500000.0))/(double)1000.0)));
        feuille.setPen(Qt::black);
        //feuille.drawLine(coo(var,g((double)var/1000.0)),
       //                coo(var+=((double)m_echantillonage/(double)500000.0),g((var+=((double)m_echantillonage/(double)500000))/(double)1000.0)));
    }

    //file.close();
    feuille.restore();

}


//ajout de ce que l'on reçoit dans le QList qui sera utilisé pour la représentation
void MyCanvas::receivedata(QList<double>a)
{
    SerialCapture m_data;
    m_datarx.append(a);
}

// Sliders permettant l'adaptation du zoom de la fenêtre
void MyCanvas::zoomchanged(int z)
{
    m_zoom=z;
    repaint();
}

//Sliders, Modifie l'amplitude du signal
void MyCanvas::amplitudeChanged(int amp)
{
    m_amplitude=amp;
    repaint();
}

//Sliders,Modifie la période du signal
void MyCanvas::periodeChanged(int t)
{
    m_periode=t;
    repaint();
}

// slider, modifie la phase du signal
void MyCanvas::phaseChanged(int alpha)
{
    m_phase=alpha;
    repaint();
}

// ajout ou suppressiond'echantillon au signal
void MyCanvas::echantillonageChanged(int echantillon)
{
    m_echantillonage=echantillon;
    repaint();
}
