#include "onedollar.h"
#include <vector>
#include <math.h>
#include <limits>

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
    }
    return newPoints;
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
    int distanceY = p2.Y - p1.Y;
    return std::sqrt(std::pow(distanceX,2) + std::pow(distanceY,2));

}

float OneDollar::Indicative_Angle(std::vector<Point> points)
{
    Point c = Centroid(points);
    float cx = c.X;
    float s =  std::atan2(c.Y-points[0].Y, c.X - points[0].X);
    return s;
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

OneDollar::Rectangle OneDollar::Box(std::vector <Point> points)
{
    int xMax = 0;
    int yMax = 0;
    int xMin = 0;
    int yMin = 0;
    for(unsigned int i = 1; i < points.size(); i++)
    {
       if(points[i-1].X < points[i].X)
       {
           xMin = points[i-1].X;
       }
       if(points[i-1].X > points[i].X)
       {
           xMax = points[i-1].X;
       }
       if(points[i-1].Y < points[i].Y)
       {
           yMin = points[i-1].Y;
       }
       if(points[i-1].Y > points[i].Y)
       {
           yMax = points[i-1].Y;
       }
    }
    return Rectangle(xMax-xMin,yMax-yMin);
}

std::vector <Point> OneDollar::Scale_To(std::vector<Point> points, int size)
{
    Rectangle B = Box(points);
    std::vector <Point> newPoints;
    for(Point P: points)
    {
        float qx = P.X * size/B.width;
        float qy = P.Y * size/B.height;
        newPoints.push_back(Point(qx,qy));
    }
    return newPoints;
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

Unistroke::Unistroke()
{

}
Unistroke::Unistroke(std::string name, std::vector <Point> points)
{
    this->name = name;
    Points = Resample(points,64);
    radians = Indicative_Angle(Points);
    Points = Rotate_By(points, -radians);
    Points = Scale_To(points, 250);
    Points = Transalte_To(points, Point(0,0));
}

float Unistroke::Path_Distance(std::vector <Point> A, std::vector <Point> B)
{
    float d = 0.0;
    for(unsigned int i =0; i < A.size(); i++)
    {
        d = d + Distance(A[i],B[i]);
    }
    return d;
}

float Unistroke::Distance_At_Angle(std::vector<Point> points, Unistroke T, int θ)
{
    std::vector <Point> newPoints = Rotate_By(points,θ);
    float d = Path_Distance(newPoints,T.Points);
    return d;
}

float Unistroke::Distance_At_Best_Angle(std::vector<Point> points, Unistroke T, int θa, int θb, int θΔ)
{
    float x1 = φ*θa + (1-φ)*θb;
    float f1 = Distance_At_Angle(points, T,x1);
    float x2 = (1-φ)*θa + φ*θb;
    float f2 = Distance_At_Angle(points, T,x2);

    while(std::abs(θb-θa) >θΔ)
    {
        if(f1 < f2)
        {
            θb = x2;
            x2 = x1;
            f2 = f1;
            x1 = φ*θa + (1-φ)*θb;
            f1 = Distance_At_Angle(points, T, x1);
        }
        else
        {
            θa = x2;
            x1 = x2;
            f1 = f2;
            x2 = (1-φ)*θa + φ*θb;
            f2 = Distance_At_Angle(points, T, x2);
        }
    }
    return std::min(f1,f2);
}

std::pair<Unistroke,float> Unistroke::Recognize(std::vector<Point> points, std::vector<Unistroke> templates)
{
    float b = std::numeric_limits<float>::infinity();
    Unistroke TT;
    for(const Unistroke &T:templates)
    {
        float d =Distance_At_Best_Angle(points, T,-θ,+θ,θΔ);
        if (d < b)
        {
            b = d;
            TT = T;
        }
    }
    float score = 1 - b/0.5 * std::sqrt(pow(250,2)+pow(250,2));

    return std::make_pair(TT,score);
}
