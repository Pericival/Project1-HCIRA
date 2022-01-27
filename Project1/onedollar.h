#ifndef ONEDOLLAR_H
#define ONEDOLLAR_H
#include <vector>
#include "point.h"
#include "point.cpp"
#include <string>
class OneDollar
{
public:
    OneDollar();
    std::vector <Point> Resample(std::vector <Point> points,int n);
    float PathLength(std::vector <Point> points);
    float Distance (Point p1, Point p2);
    float Indicative_Angle(std::vector<Point> points);
    Point Centroid(std::vector <Point> points);
    std::vector <Point> Rotate_By(std::vector <Point> points, float w);
    std::vector <Point> Scale_To(std::vector <Point> points,int size);
    std::vector <Point> Transalte_To(std::vector <Point> points, Point k);



};
class Unistroke:OneDollar
   {
   public:
       Unistroke(std::string name, std::vector <Point> points);
       std::string name;
       std::vector <Point> Points;
       float radians;

   };

#endif // ONEDOLLAR_H
