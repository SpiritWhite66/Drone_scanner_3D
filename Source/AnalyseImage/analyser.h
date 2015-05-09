#ifndef ANALYSER_H
#define ANALYSER_H

#include <QApplication>
#include <QtGui>

class Analyser
{
    public:
        Analyser();
        void initGL();
        void updateGL();
        int frameAnalyse(QString filename);
        int addPoint(int x, int y, int z);
        void loop();

    private:
       QImage m_frame;
       float m_etalon;

};

#endif // ANALYSER_H
