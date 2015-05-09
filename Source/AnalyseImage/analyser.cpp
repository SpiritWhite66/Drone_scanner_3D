#include "analyser.h"

Analyser::Analyser()
{
    m_etalon = 700;
    QImage m_frame;
}

int Analyser::frameAnalyse(QString filename)
{
    m_frame.load(filename);
    int i,j,xmax,ymax,value,count;
    double x,y;
    QRgb color;
    i=j=x=y=value=count=0;
    ymax=m_frame.height();
    xmax=m_frame.width();

    while (i < xmax)
    {
        j = value = count = 0;
        finalValue = 0.0;
        while (j < ymax)
        {
            color = m_frame.pixel(i,j);

            if (qRed(color) > 210 && qGreen(color) <= 210 && qBlue(color) <= 210)
            {
                value += j;
                count++;
            }
        }
        if (count > 0) {
            y = (double)value/(double)count;
            x = (double)i;
        }
        i++;
    }
    return 1;

}
