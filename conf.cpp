#include "conf.h"

using namespace std;

void config::loadConf(config::Config &cf)
{

    /* Funció per llegir les variables 
     * de confiuracio.
     */
    ifstream file("robot.conf");
    string line;
    string name;
    string value;

    int posEqual;
    while (std::getline(file,line)) {
        if (! line.length()) 
           continue;
        if (line[0] == '#') 
          continue;
        else {
          posEqual=line.find('=');
          name  = line.substr(0, posEqual);
          value = line.substr(posEqual + 1);

          if (name == "W_OBJECTS") 
            cf.W_OBJECTS = atof(value.c_str());
          else if (name == "W_DESTINATION") 
            cf.W_DESTINATION = atof(value.c_str());
          else if (name == "W_OBJECTS_DANGER") 
            cf.W_OBJECTS_DANGER = atof(value.c_str());
          else if (name == "W_DESTINATION_DANGER") 
            cf.W_DESTINATION_DANGER = atof(value.c_str());
          else if (name == "VEL_WITH_OBJECTS")
            cf.VEL_WITH_OBJECTS = atof(value.c_str());
          else if (name == "DIST_MIN") 
            cf.DIST_MIN = atoi(value.c_str());
          else if (name == "DIST_MAX")
            cf.DIST_MAX = atoi(value.c_str());
          else if (name == "VEL_MAX")
            cf.VEL_MAX = atoi(value.c_str());
          else if (name == "VEL_MIN")
            cf.VEL_MIN = atoi(value.c_str());
          else if (name == "OBJECT_THRESHOLD") 
            cf.OBJECT_THRESHOLD = atoi(value.c_str());
          else if (name == "MIN_APROX_OBJECT") 
            cf.MIN_APROX_OBJECT = atoi(value.c_str());
          else if (name == "SLEEP") 
            cf.SLEEP = atoi(value.c_str());
          else if (name == "W_SENSOR_PRIORITY") 
            cf.W_SENSOR_PRIORITY = atoi(value.c_str());
          else if (name == "W_SENSOR_NORMAL") 
            cf.W_SENSOR_NORMAL = atoi(value.c_str());
        }
    }

    cout << "W_OBJECTS " << cf.W_OBJECTS << endl;
    cout << "W_DESTINATION " << cf.W_DESTINATION << endl;
    cout << "W_OBJECTS_DANGER " << cf.W_OBJECTS_DANGER << endl;
    cout << "W_DESTINATION_DANGER " << cf.W_DESTINATION_DANGER << endl;
    cout << "VEL_WITH_OBJECTS " << cf.VEL_WITH_OBJECTS << endl;
    cout << "DIST_MIN " << cf.DIST_MIN << endl;
    cout << "DIST_MAX " << cf.DIST_MAX << endl;
    cout << "VEL_MAX " << cf.VEL_MAX << endl;
    cout << "VEL_MIN " << cf.VEL_MIN << endl;
    cout << "OBJECT_THRESHOLD " << cf.OBJECT_THRESHOLD << endl;
    cout << "MIN_APROX_OBJECT " << cf.MIN_APROX_OBJECT << endl;
    cout << "SLEEP " << cf.SLEEP << endl;
    cout << "W_SENSOR_PRIORITY " << cf.W_SENSOR_PRIORITY << endl;
    cout << "W_SENSOR_NORMAL " << cf.W_SENSOR_NORMAL << endl;
}
        

void config::loadRoute(Sequencial &seq) 
{
    /* Funcio per llegit la ruta a seguir
     * pel robot.
     */
    int o1, c1, t1;
    ifstream file("route.conf");
    string line;
    string cx;
    string cy;


    while (std::getline(file,line)) {
        if (! line.length()) continue;
        else {
            o1=line.find('(');
            c1=line.find(',');
            t1=line.find(')');
            cx = line.substr(o1+1,c1-1);
            cy = line.substr(c1+1, t1-1);
            cout << "Punt: (" << cx << ", "<< cy << ")" << endl;
            Point p(atoi(cx.c_str()), atoi(cy.c_str()));
            seq.addPoint(p);
        }
    }
}

 
