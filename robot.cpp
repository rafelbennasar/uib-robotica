#include "robot.h"


bool Robot::isArPoseValid(ArPose &p)
{
  /* Si el vector d'obstacles es o no buit */

  return (p.getX() != 0 && p.getY() != 0);
}


Sequencial& Robot::getSeq(void) 
{
    return this->seq;
}


HashMap& Robot::getHash(void)
{

  return this->hm;
}

Robot::Robot():ArRobot()
{
    config::loadConf(this->cnf);
    this->dangerous = false;

    config::loadRoute(this->seq);

    Point next_point = seq.nextPoint(0, 0);
    seq.getOrig().setPoint(0, 0);
    seq.getDest().setPoint(next_point.getX(), next_point.getY());

}



Robot::~Robot(){}

bool Robot::getDangerous(void) const 
{
    /* Si hi ha perill de colisio */

    return this->dangerous;
}

void Robot::resetDangerous(void) 
{
    this->dangerous = false;
}


bool Robot::getFinished(void) 
{
    /* Si ha acabat tota la ruta
     * del secuenciador 
     */
    return this->finished;
}

void Robot::resetFinished(void) 
{
    this->finished = false;
}

ArPose& Robot::avoidColision(void) 
{

    /* Rutina la qual evita els obstacles.
     */
    double next_x = 0; 
    double next_y = 0;
    double dist = 0;
    double r_x, r_y;
    int alpha = 0;
 
    r_x = this->getX();
    r_y = this->getY();
    for (int i = 0; i < this->getNumSonar(); i++){
      ar = this->getSonarReading(i);
      dist = ar->getRange();
      if (dist > 0 && dist < this->cnf.MIN_APROX_OBJECT){
        if (dist < this->cnf.DIST_MIN) {
          dangerous = true;
        }
        if (i < this->getNumSonar() / 2) 
          alpha = this->cnf.W_SENSOR_PRIORITY;
        else
          alpha = this->cnf.W_SENSOR_NORMAL;

  
        next_x -= ((ar->getX() - r_x) * alpha);
        next_y -= ((ar->getY() - r_y) * alpha);
      }
    }

    if (next_y == 0 && next_x == 0){
      this->arp.setX(0);
      this->arp.setY(0);
      return arp;
    }


    double modul = sqrt(pow(next_x, 2) + pow(next_y, 2));
    this->arp.setX((next_x / modul));
    this->arp.setY((next_y / modul));
    return arp;
    

}

ostream& operator<<(ostream &co, const Robot& r)
{
  co << "Posició del robot: X=> " << r.getX();
  co << " Y=> " << r.getY() << endl;
  return co;
}

ArPose& Robot::getDestination(void) 
{

    /* Rutina per el calcul del vector
     * de desti.
     */
    double r_x, r_y;
    double next_x = 0; 
    double next_y = 0;
    cout << *this;
    Point dest = this->seq.getDest();
    cout << "Valor Desti " << this->hm.getValue(dest.getX()/10, dest.getY()/10) << endl;
    if ((this->hm.getValue(dest.getX()/10, dest.getY()/10)) > this->cnf.OBJECT_THRESHOLD){
      cout << "Impossible cobrir missió" << endl;
      try {
        Point next_point = seq.nextPoint(this->getX(),
                                         this->getY());
        this->seq.getDest().setPoint(next_point.getX(), 
                                     next_point.getY());        

        this->hm.setValue(this->seq.getDest().getX() / 10,
                          this->seq.getDest().getY() / 10);
      } catch (exception &e) {
        this->finished=true;
      }
    }
    else{
      if (this->seq.achivedMission(this->getX(), 
                                   this->getY())){
        cout << "Missio completada!" << endl; 
        try {
          Point next_point = seq.nextPoint(this->getX(),
                                           this->getY());
          this->seq.getDest().setPoint(next_point.getX(), 
                                       next_point.getY());
          this->hm.setValue(this->seq.getDest().getX() / 10,
                            this->seq.getDest().getY() / 10);

        } catch (exception &e) {
          this->finished=true;
        }
      }
    }

    r_x = this->getX();
    r_y = this->getY();
    cout << this->seq;
    next_x += (this->seq.getDest().getX() - r_x) ;      
    next_y += (this->seq.getDest().getY() - r_y) ;


    double modul = sqrt(pow(next_x, 2) + pow(next_y, 2));
    this->arp.setX(next_x / modul);
    this->arp.setY(next_y / modul);
    return this->arp;


}

void Robot::setVelToDest(void) 
{

  /* Rutina per el calcul de la velocitat 
   * en funcio del percentatge realitzat de la 
   * submissio
   */
  double perct = this->seq.getPercent(this->getX(), 
                                      this->getY());
  if (perct < 0.8)
    this->setVel(this->cnf.VEL_MAX);
  else{
    cout << "Vel " << abs((1 - perct) * this->cnf.VEL_MAX) + 100 << endl;
    this->setVel(abs((1 - perct) * this->cnf.VEL_MAX) + 100);
  }
}



void Robot::makeMap() 
{
    /* Fa el mapa de l'entorn.
     * Aquesta rutina es llancada amb un fil al
     * main
     */    
    double r_x, r_y;
    int x, y;
    r_x = this->getX();
    r_y = this->getY();
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            if ((i % 10) == 0)
                this->hm.put(i, j);
            if ((j % 10) == 0)
                this->hm.put(i, j);
        }
    }

    while (!this->finished) {
      for (int i = 0; i < this->getNumSonar(); i++){
        ar = this->getSonarReading(i);
        if (ar->getRange() > 0 && ar->getRange() < 3000){
          x = (ar->getX() / 10);
          y = (ar->getY() / 10);

          for (int k=-10; k < 10; k++) {
            for (int l=-10; l < 10; l++) {
              this->hm.put(x+k, y+l);
            }
          }

        }
      }
        ArUtil::sleep(100);
    }

}


