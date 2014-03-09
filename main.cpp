
#include "Aria.h"
#include "robot.h"
#include "bitmap.h"
#include <iostream>
#include <time.h>


int main(int argc, char **argv) {

  Robot robot3;

  Aria::init();
  ArSimpleConnector connector(&argc, argv);

  if (!connector.parseArgs() || argc > 1) {
    connector.logOptions();
    exit(1);
  }

  if (!connector.connectRobot(&robot3)) {
    printf("Could not connect to robot... exiting\n");
    Aria::shutdown();
    return 1;
  }

  robot3.comInt(ArCommands::SOUNDTOG, 1);
  robot3.comInt(ArCommands::ENABLE, 1); 
  robot3.runAsync(false);
  
  ArFunctor *pf;
  ArFunctorC<Robot> af(robot3, &Robot::makeMap);
  pf = &af;
  new ArThread(pf);

  int n = 0;
  double wd, wo;
  double next_x, next_y, w;

  robot3.resetFinished();
  while (!robot3.getFinished()) {
    cout << "1) Passa número" << n << endl;
//    robot3.setVel(0);
    ArPose o = robot3.avoidColision();
    ArPose d = robot3.getDestination();
    if (robot3.getDangerous()) {
      wo = robot3.cnf.W_OBJECTS_DANGER;
      wd = robot3.cnf.W_DESTINATION_DANGER;
      cout << "SITUACIÓ ALERTA!" << endl;
    } else {
      if (Robot::isArPoseValid(o)){
         wo = robot3.cnf.W_OBJECTS;
         wd = robot3.cnf.W_DESTINATION;
      }
      else{
        wd = 10;
        wo = 0;
      }
    }

    cout << "Objecte " << o.getX() << " " << o.getY() << endl;
    cout << "Destí   " << d.getX() << " " << d.getY() << endl;

    next_x = (wd * d.getX()) + (wo * o.getX());
    next_y = (wd * d.getY()) + (wo * o.getY());

    w = ArMath::atan2(next_y, next_x);

    robot3.setHeading(w);
    while(!robot3.isHeadingDone(10)) {
      robot3.setVel(0);
    }
    if (robot3.getDangerous()){
       robot3.setVel(robot3.cnf.VEL_MIN);
       robot3.resetDangerous();
    }
    else{
      if (Robot::isArPoseValid(o)) {
         robot3.setVel(robot3.cnf.VEL_WITH_OBJECTS);

      }
      else{
        robot3.setVelToDest();
      }
    }
    n++;
    ArUtil::sleep(robot3.cnf.SLEEP);
  }
  robot3.setVel(0);
  bitmap::hashMapToBitMap(robot3, "mapa.bmp");
  robot3.stopRunning();
  Aria::shutdown();
  return 0;
}

