#ifndef _INERTIALNAV_H
#define	_INERTIALNAV_H

#include "board.h"
 
#define INTERTIALNAV_GRAVITY 972.665f  //972.665f 843.665f

struct _z_efdata
			 {
				 float correction;
				 float increase;
				 float base;
       };
struct _z_ef
			 {
				 struct _z_efdata accz;
				 struct _z_efdata velz;
         struct _z_efdata posz;
			 };
			 
extern struct _z_ef z_ef;

void Update_Velocities_Positions_Z(float T);
void Push_baroAlt(void);

#endif
