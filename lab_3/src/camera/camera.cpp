#include "../../inc/camera/camera.h"
#include "transform.h"
#include <iostream>
void Camera::move_x(const double &dx)
{
    _position.set_x(_position.get_x() + dx);
}

void Camera::move_y(const double &dy)
{
    _position.set_y(_position.get_y() + dy);
}

void Camera::move_z(const double &dz)
{
    _position.set_z(_position.get_z() + dz);
}

void Camera::move_camera(const Dot& move_params)
{
	move_x(move_params.get_x());
	move_y(move_params.get_y());
	move_z(move_params.get_z());

}

void Camera::transform(const TransformParams& transform_params)
{

	auto rotate_params = transform_params.getRotateParams();
	this->rotate_camera(rotate_params.get_x(),rotate_params.get_y());

	auto move_params = transform_params.getMoveParams();
	move_camera(transform_params.getMoveParams());
}

void Camera::rotate_camera(float x_offset, float y_offset)
{
	std::cout<<"YAW " << Yaw<< std::endl;
	std::cout<<"Pitch " << Pitch<< std::endl;
	Yaw   += x_offset;
	Pitch += y_offset;
	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;
	if (Yaw > 89.0f)
		Yaw = 89.0f;
	if (Yaw < -89.0f)
		Yaw = -89.0f;
	updateCameraVectors();
}

Matrix4 Camera::get_view_matrix()
{

	Vector3 position = Vector3{_position.get_x(),_position.get_y(),_position.get_z()};
	Matrix4 view = glm::lookAt(position, position + Front, Up);
	return view;
}

Matrix4 Camera::get_projection_matrix() const
{
	return perspective(glm::radians(90.0f), aspect, zNear, zFar);
}

void Camera::updateCameraVectors()
{
	Vector3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = normalize(front);
	Right = normalize(cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up    = normalize(cross(Right, Front));
}

void Camera::accept(std::shared_ptr<Visitor> visitor)
{
    visitor->visit(*this);
}
