#include "../../inc/camera/camera.h"
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

void Camera::transform(const Dot &new_position, const Dot &scale, const Dot &rotate)
{
    move_x(new_position.get_x());
    move_y(new_position.get_y());
	this->rotate(rotate);//TODO::check this
}

void Camera::rotate(const Dot &rotate_val)
{
	rotate_camera(rotate_val.get_x(), rotate_val.get_y());
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

void Camera::move(const Dot &move_val)
{
	move_x(move_val.get_x());
	move_y(move_val.get_y());
}

void Camera::scale(const Dot& scale_val)
{
	std::cout<< "Camera cannot be scaled";
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
