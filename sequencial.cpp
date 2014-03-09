#include "sequencial.h"

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

int Point::getX() const {
    return this->x;
}

int Point::getY() const {
    return this->y;
}

void Point::setPoint(const int x, const int y) {
    this->x = x;
    this->y = y;
}

Point& Sequencial::getDest(){
    return this->dest;
}

Point& Sequencial::getOrig(){
    return this->orig;
}


Sequencial::Sequencial() {
  this->orig = Point();
  this->dest = Point();
}

void Sequencial::addPoint(Point &p) {
    this->route.push_back(p);
}

Point& Sequencial::nextPoint(const double x, const double y) {
    Point new_p = this->route.at(this->route.size()-1);
    this->route.pop_back();
    this->orig.setPoint(x, y);
    this->dest.setPoint(new_p.getX(), new_p.getY());
    cout << "(orig_x, orig_y) to (dest_x, dest_y) ==> (";
    cout << this->orig.getX() << ", " << this->orig.getY() << ") to  (";
    cout <<  this->dest.getX() << ", " << this->dest.getY() << ")" << endl;
    this->dist = sqrt(pow(abs(this->dest.getX() - this->orig.getX()), 2) 
                      + pow (abs(this->dest.getY()- this->orig.getY()), 2));
    return this->dest;
}


/*
 * (x, y) és la posició actual del robot.
 */
double Sequencial::getPercent(const int x, const int y) {


  double dst = sqrt(pow(abs(this->orig.getX() - x), 2) 
                     + pow(abs(this->orig.getY() - y), 2));

  double st = (dst / this->dist);
  cout << "Percentatge " << st << endl;
  return st;



}

void Sequencial::printRoute() {
    for (unsigned int i = 0; i< route.size(); i++) {
        Point p = route.at(i);
    }
}


bool Sequencial::achivedMission(const int x, const int y) {
    double p = this->getPercent(x, y);
    return (p >= ACHIVED_ENVIRONMENT_LOW &&
           p < ACHIVED_ENVIRONMENT_UP);
}

ostream& operator<<(ostream& co, Point &p)
{
  co << "X => " << p.x << " Y => " << p.y << endl;
  return co;
}


ostream& operator<<(ostream& co, Sequencial &s)
{
  co << "Origen : " << s.orig;
  co << "Destí  : " << s.dest;
  return co;
}

