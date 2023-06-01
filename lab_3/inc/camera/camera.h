#ifndef CAMERA_H
#define CAMERA_H

#include "../object/object.h"
#include "../managers/draw/draw_manager.h"
#include "../math/glm_wrapper.h"
#include "transform_manager.h"


class Camera : public InvisibleObject
{
    friend Dot DrawManager::get_dot_proection(const Dot &dot);


public:
    Camera() = default;
    explicit Camera(const Dot &position) : _position(position) { };
    ~Camera() override = default;

    void transform(const TransformParams& transform_params) override;

	void accept(std::shared_ptr<Visitor> visitor) override;
	Matrix4 get_view_matrix();
	Matrix4 get_projection_matrix() const;


 protected:
	void updateCameraVectors();
private:
	Vector3 Front{0.0f, 0.0f, -1.0f};
	Vector3 Up{0,1,0};
	Vector3 Right{0,0,1};
	Vector3 WorldUp{0,1,0};
	float Yaw = -90;
	float Pitch = 0;
	float aspect = 1.0f;
	float zNear = 0.1f;
	float zFar = 100.0f;
    void move_x(const double &dx);
    void move_y(const double &dy);
    void move_z(const double &dz);
	void rotate_camera(float x_offset, float y_offset);
	void move_camera(const Dot& move_params);



    Dot _position;
};

#endif
