#ifndef __ROBOTCONF__
#define __ROBOTCONF__ 0

#include "sequencial.h"
#include <fstream>

namespace config{

  /* Variables de configuració 
   * juntament amb les funcions per llegir
   * les variables del fitxer i la ruta 
   * a seguir pel robot.
   */
  typedef struct {
  
    float W_OBJECTS;
    float W_DESTINATION;
    float W_OBJECTS_DANGER;
    float W_DESTINATION_DANGER;
    unsigned int VEL_WITH_OBJECTS;
    unsigned int DIST_MIN;
    unsigned int DIST_MAX;
    unsigned int VEL_MAX;
    unsigned int VEL_MIN;
    unsigned int MIN_APROX_OBJECT;
    unsigned int OBJECT_THRESHOLD;
    unsigned int SLEEP;
    unsigned int W_SENSOR_NORMAL;
    unsigned int W_SENSOR_PRIORITY;

  }Config;


  void loadConf(Config &);
  void loadRoute(Sequencial &); 

}

#endif

