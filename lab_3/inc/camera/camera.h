#ifndef CAMERA_H
#define CAMERA_H

#include "../object/object.h"
#include "../managers/draw/draw_manager.h"
#include "../math/glm_wrapper.h"


class Camera : public InvisibleObject
{
    friend Dot DrawManager::get_dot_proection(const Dot &dot);

public:
    Camera() = default;
    explicit Camera(const Dot &position) : _position(position) { };
    ~Camera() override = default;

    void transform(const Dot &new_position, const Dot &scale, const Dot &rotate) override;
	void rotate(const Dot &rotate_val) override;
	void scale(const Dot &scale_val) override;
	void move(const Dot &move_val) override;


    void accept(std::shared_ptr<Visitor> visitor) override;
	void rotate_cam_view(float x_offset, float y_offset);

 protected:
	void updateCameraVectors();
private:
	Vector3 Front{};
	Vector3 Up{};
	Vector3 Right{};
	Vector3 WorldUp{};
	float Yaw;
	float Pitch;
	float aspect = 1.0f;
	float zNear = 0.1f;
	float zFar = 100.0f;
    void move_x(const double &dx);
    void move_y(const double &dy);
    void move_z(const double &dz);



    Dot _position;
};

#endif
