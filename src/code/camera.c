#include <globals.h>
#include <lib/utils.h>
#include <lib/dzmath.h>
#include "t3d/t3d.h"
#include "t3d/t3dmath.h"
#include <camera.h>

void Camera_Spawn(Camera* camera, Vec3 pos, binang yaw, binang pitch, Vec3 at, binang fov) {
  camera->viewport = t3d_viewport_create_buffered(FB_COUNT);
  camera->pos = pos;
  camera->at = at;
  camera->up = CAMERA_DEFAULT_UP;
  camera->fov = fov;

  t3d_viewport_set_projection(&camera->viewport, fov, CAMERA_DEFAULT_NEAR, CAMERA_DEFAULT_FAR);

  Camera_Rotate(camera, yaw, pitch);
  Camera_LookAt(camera, &camera->at);
  Camera_Attach(camera);
}

void Camera_LookAt(Camera* camera, Vec3* at) {
  camera->at = *at;
  t3d_viewport_look_at(&camera->viewport, &camera->pos, &camera->at, &camera->up);
}

void Camera_Translate(Camera* camera, Vec3 towards) {
  t3d_vec3_add(&camera->pos, &camera->pos, &towards);
  Camera_LookAt(camera, &camera->at);
}

/*
 * Translates camera position and its `at`
 * */
void Camera_TranslateFree(Camera* camera, Vec3 towards) {
  t3d_vec3_add(&camera->at, &camera->at, &towards);
  Camera_Translate(camera, towards);
}


// Camera ROTATION funcs

void Camera_SetYaw(Camera* camera, binang yaw) {
  Camera_SetRotation(camera, yaw, camera->pitch);
}

void Camera_SetPitch(Camera* camera, binang pitch) {
  Camera_SetRotation(camera, camera->yaw, pitch);
}

void Camera_RotateYaw(Camera* camera, binang yaw) {
  Camera_Rotate(camera, yaw, 0);
}

void Camera_RotatePitch(Camera* camera, binang pitch) {
  Camera_Rotate(camera, 0, pitch);
}

void Camera_Rotate(Camera* camera, binang yaw, binang pitch) {
  camera->yaw += yaw;
  camera->pitch += pitch;

  Camera_SetRotation(camera, camera->yaw, camera->pitch);
}

void Camera_RotateAroundPointXZ(Camera* camera, Vec3* target, u16 dist) {
  // @TODO: do dis
}

void Camera_SetRotation(Camera* camera, binang yaw, binang pitch) {
  float yaw_cos = dz_cos(camera->yaw);
  float yaw_sin = dz_sin(camera->yaw);
  float pitch_cos = dz_cos(camera->pitch);
  float pitch_sin = dz_sin(camera->pitch);

  camera->at.x = camera->pos.x + yaw_sin * pitch_cos;
  camera->at.y = camera->pos.y + pitch_sin;
  camera->at.z = camera->pos.z - yaw_cos * pitch_cos;

  Camera_LookAt(camera, &camera->at);
}

void Camera_SetPos(Camera* camera, Vec3 pos) {
  camera->pos = pos;
  Camera_LookAt(camera, &camera->at);
}

void Camera_Attach(Camera* camera) {
  t3d_viewport_attach(&camera->viewport);
}

/*
 * Changes camera's FOV to `newFov` which should be in radians.
 * This should be and probably MUST be the only way
 * used to change the camera's FOV, as the `fov`
 * value in the Camera struct is just to keep track
 * of it. And it can be correct only if this function
 * has been used to change the cam's fov.
 * (Calling it once is enough to change fov)
 * */
void Camera_SetFOV(Camera* camera, binang newFov) {
  // changing fov like Tiny3D would
  float tanHalfFov = dz_tan(newFov >> 1);
  float aspectRatio = Camera_GetAspectRatio(camera);

  camera->viewport.matProj.m[0][0] = 1.0f / (aspectRatio * tanHalfFov);
  camera->viewport.matProj.m[1][1] = 1.0f / tanHalfFov;

  camera->fov = newFov;
}

float Camera_GetAspectRatio(Camera* camera) {
  return (float) camera->viewport.size[0] / (float) camera->viewport.size[1];
}
