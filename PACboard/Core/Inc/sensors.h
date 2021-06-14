#ifndef __SENSORS_H
 #define __SENSORS_H

extern float pressure, temperature, humidity;

void sensorsInit(void);
void TASK_SensorHandler(void);

#endif
