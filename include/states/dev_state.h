#ifndef DEV_STATE_H
#define DEV_STATE_H


typedef struct DevState {
} DevState;


void DevState_Init(void* state);
void DevState_Main(void* state);
void DevState_Destroy(void* state);

#endif
