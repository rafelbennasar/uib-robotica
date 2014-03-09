#ifndef __ROBOT__
#define __ROBOT__ 0
#include "Aria.h"
#include <iostream>
#include <time.h>
#include "hash.h"
#include <stdint.h>
#include "ArThread.h"
#include "ArFunctor.h"
#include <cmath>
#include "ariaUtil.h"
#include "conf.h"
#include "sequencial.h"

using namespace std;



class Robot : public ArRobot {

    private:
        bool dangerous;
        bool finished;
        ArSensorReading *ar;
        ArPose arp;
        HashMap hm;
        Sequencial seq;

    public:
        config::Config cnf;

        Robot();
        ~Robot();
        ArPose& avoidColision(void);
        ArPose& getDestination(void);

        bool getFinished(void);
        void resetFinished(void);
        bool getDangerous(void) const;
        void resetDangerous(void);
        Sequencial& getSeq(void);
        void setVelToDest(void);
        void makeMap();
        HashMap& getHash(void);
        friend ostream& operator<<(ostream&, const Robot&);
        static bool isArPoseValid(ArPose&);
};

#endif
