#include "onedollar.h"
#include <vector>
#include <math.h>
OneDollar::OneDollar()
{

}

std::vector <Point> OneDollar::Resample(std::vector <Point> points, int n)
{
    float I = PathLength(points) / (n-1);
    float D = 0.0;
    std::vector <Point> newPoints;
    for(unsigned int i = 1; i < points.size();i++)
    {
        float d = Distance(points[i-1],points[i]);
        if((D+d) >= I)
        {
            float qx = points[i-1].X + ((I-D) / d) * (points[i].X-points[i-1].X);
            float qy = points[i-1].Y + ((I-D) / d) * (points[i].Y-points[i-1].Y);
            Point q(qx,qy);
            newPoints.push_back(q);
            points.insert(points.begin()+i,q);
            D =0.0;
        }
        else{
            D = D+d;
        }
        return newPoints;
    }
}

float OneDollar::PathLength(std::vector <Point> points)
{
    float d = 0.0;
    for(unsigned int i = 1;  i < points.size(); i++)
    {
        d += Distance(points[i-1],points[i]);
    }
    return d;
}

float OneDollar::Distance(Point p1, Point p2)
{
    int distanceX = p2.X - p1.X;
    int distanceY = p2.X - p1.Y;
    return std::sqrt(distanceX * distanceX + distanceY* distanceY);

}

float OneDollar::Indicative_Angle(std::vector<Point> points)
{
    Point c = Centroid(points);
    return std::atan2(c.Y-points[0].Y, c.X - points[0].X);
}

std::vector <Point> OneDollar::Rotate_By(std::vector <Point> points, float w)
{
    Point c = Centroid(points);
    std:: vector <Point> newPoints;
    for(Point P : points)
    {
        float qx = (P.X -c.X) * cos(w) - (P.Y-c.Y)* sin(w)+ c.X;
        float qy = (P.X -c.X) * sin(w) - (P.Y-c.Y)* cos(w)+ c.Y;
        newPoints.push_back(Point(qx,qy));
    }
    return newPoints;
}

Point OneDollar::Centroid(std::vector<Point> points)
{
    float x= 0.0,y = 0.0;

    for (unsigned int i =0; i< points.size(); i++)
    {
        x += points[i].X;
        y += points[i].Y;
    }

    x /= points.size();
    y /= points.size();
    Point s(x,y);
    return s;
}

std::vector <Point> OneDollar::Scale_To(std::vector<Point> points, int size)
{
    B
}
std::vector <Point> OneDollar::Transalte_To(std::vector<Point> points, Point k)
{
    Point c = Centroid(points);
    std::vector <Point> newPoints;
    for (Point P: points)
    {
        float qx = P.X + k.X - c.X;
        float qy = P.X + k.X - c.X;
        newPoints.push_back(Point(qx,qy));
    }
    return newPoints;
}

Unistroke::Unistroke::Unistroke(std::string name, std::vector <Point> points)
{
    this->name = name;
    Points = Resample(Points,64);
    radians = Indicative_Angle(Points);
    Points = Rotate_By(points, -radians);
    Points = Scale_To(points, 250);
    Points = Transalte_To(points, Point(0,0));
}
