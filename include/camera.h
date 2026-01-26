#ifndef CAMERA_H
#define CAMERA_H

#include <lib/types.h>
#include "t3d/t3d.h"

#define CAMERA_DEFAULT_NEAR 5
#define CAMERA_DEFAULT_FAR  80
#define CAMERA_DEFAULT_UP (Vec3){{0, 1, 0}}
#define CAMERA_MAX_PITCH   0x3FFF
#define CAMERA_MIN_PITCH  -0x3FFF

// some pre-computed values
#define CAMERA_DEFAULT_FOV  0x2AAB  // 60° in BINANG

typedef struct Camera {
  T3DViewport viewport;
  binang fov;
  Vec3 pos;
  Vec3 at; // position to look at
  Vec3 up;
  binang yaw;
  binang pitch;
} Camera;


void Camera_Spawn(Camera* camera, Vec3 pos, binang yaw, binang pitch, Vec3 at, binang fov);
void Camera_LookAt(Camera* camera, Vec3* at);
void Camera_Attach(Camera* camera);
void Camera_SetFOV(Camera* camera, binang newFov);
void Camera_SetAspectRatio(Camera* camera, float aspectRatio);
float Camera_GetAspectRatio(Camera* camera);

void Camera_Translate(Camera* camera, Vec3* towards);
void Camera_TranslateFree(Camera* camera, Vec3* towards);

void Camera_RotateYaw(Camera* camera, binang yaw);
void Camera_RotatePitch(Camera* camera, binang pitch);
void Camera_Rotate(Camera* camera, binang yaw, binang pitch);

void Camera_SetPos(Camera* camera, Vec3* pos);
void Camera_SetYaw(Camera* camera, binang yaw);
void Camera_SetPitch(Camera* camera, binang pitch);
void Camera_SetRotation(Camera* camera, binang yaw, binang pitch);

void Camera_RotateAroundPointXZ(Camera* camera, Vec3* target, u16 dist);

#endif
