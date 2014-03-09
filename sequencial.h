#ifndef __SECUENCIAL__
#define __SECUENCIAL__
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <list>
#include <map>
#include <utility>
#include <vector>

#define ACHIVED_ENVIRONMENT_LOW 1.00
#define ACHIVED_ENVIRONMENT_UP  1.03

using namespace std;

class Point {
    private:
        int x;
        int y;
    public:
        int getX(void) const;
        int getY(void) const;
        void setPoint(const int x, const int y);
        Point();
        Point(const int x, const int y);
        friend ostream& operator<<(ostream&, Point&);
        
};

class Sequencial { 
    
    private:
        vector<Point> route;
        Point dest;
        Point orig;
        double dist;
    public:
        Sequencial();
        void addPoint(Point &p);
        Point& nextPoint(const double x, const double y);
        void printRoute();
        Point& getDest(void);
        Point& getOrig(void);
        bool achivedMission(const int x, const int y);
        double getPercent(const int x, const int y);
        friend ostream& operator<<(ostream&, Sequencial&);
};

#endif
