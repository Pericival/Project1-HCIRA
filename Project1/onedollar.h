#ifndef ONEDOLLAR_H
#define ONEDOLLAR_H
#include <vector>

#include <string>
#include <math.h>

struct Point
{
    int X;
    int Y;
    Point(int x, int y)
    {
        X = x;
        Y = y;
    }

};

class OneDollar
{
public:
    OneDollar();

    struct Rectangle{

        float width;
        float height;
        Rectangle(int x, int y)
        {
            width = x;
            height = y;
        }
    };

    std::vector <Point> Resample(std::vector <Point> points,int n);
    float PathLength(std::vector <Point> points);
    float Distance (Point p1, Point p2);
    float Indicative_Angle(std::vector<Point> points);
    Point Centroid(std::vector <Point> points);
    std::vector <Point> Rotate_By(std::vector <Point> points, float w);
    std::vector <Point> Scale_To(std::vector <Point> points,int size);
    std::vector <Point> Transalte_To(std::vector <Point> points, Point k);
    Rectangle Box(std::vector <Point> points);


};

class Unistroke:OneDollar
   {

    float φ = 0.5*(-1.0 + std::sqrt(5.0));
    float θΔ = 2;
    float θ = 45;
   public:
       Unistroke();
       Unistroke(std::string name, std::vector <Point> points);
       std::string name;
       std::vector <Point> Points;
       float radians;
       float Path_Distance(std::vector <Point> A, std::vector <Point> B);
       float Distance_At_Angle(std::vector <Point> points, Unistroke T, int θ);
       float Distance_At_Best_Angle(std::vector <Point> points, Unistroke T, int θa,int θb,int θΔ);
       std::pair<Unistroke,float> Recognize(std::vector <Point> points,std::vector <Unistroke> templates);
};



#endif // ONEDOLLAR_H
