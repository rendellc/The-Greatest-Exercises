#ifndef MY_CAMERA_HPP
#define MY_CAMERA_HPP

class MyCamera {
public:
    float x=0,  // right
          y=0,  // up
          z=0,  // into the screen
          pitch=0, // around x-axis
          yaw=0; // around y-axis
    
public:
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }
    void setZ(float newZ) { z = newZ; }
    void setPitch(float newPitch) { pitch = newPitch; }
    void setYaw(float newYaw) { yaw = newYaw; }

    void moveX(float step) { x += step; }
    void moveY(float step) { y += step; }
    void moveZ(float step) { z += step; }
    void changePitch(float step) { pitch += step; }
    void changeYaw(float step) { yaw += step; }
};

#endif // MY_CAMERA_HPP

