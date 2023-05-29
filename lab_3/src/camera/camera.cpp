#include "../../inc/camera/camera.h"

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
	//this->rotate(rotate.get_x(),rotate.get_y());
}

void Camera::rotate(float x_offset, float y_offset)
{
	Yaw   += x_offset;
	Pitch += y_offset;
	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;
	updateCameraVectors();
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
