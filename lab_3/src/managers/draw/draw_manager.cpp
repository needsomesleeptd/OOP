#include "draw_manager.h"
#include "model.h"
#include "camera.h"
#include <glm/gtx/string_cast.hpp>

#include "iostream"

#define GLM_ENABLE_EXPERIMENTAL
Vector4 dot_to_vec(const Dot dot)
{
	return  Vector4(dot.get_x(),dot.get_y(),dot.get_z(),0);
}

void DrawManager::set_camera(std::shared_ptr<Camera> camera)
{
    _camera = camera;
}

void DrawManager::set_drawer(std::shared_ptr<AbstractDrawer> drawer)
{
    _drawer = drawer;
}

Dot DrawManager::get_dot_proection(const Dot &dot)
{
    Dot proection = dot;

    proection.set_x(proection.get_x() + _camera->_position.get_x());
    proection.set_y(proection.get_y() + _camera->_position.get_y());

    return proection;
}

void DrawManager::visit(Model &model)
{
    auto dots   = model._modelStructure->get_dots();
    auto links  = model._modelStructure->get_links();
    auto center = model._modelStructure->get_center();
	Matrix4 view_matrix = _camera->get_view_matrix();
	Matrix4 projection_matrix = _camera->get_projection_matrix();
	Matrix4 matrix_changes = projection_matrix * (view_matrix * (Matrix4(1)));
	//std::cout<<glm::to_string(view_matrix) << std::endl;
    for (auto link : links)
    {

		Vector4 vec_from = matrix_changes  * dot_to_vec(dots.at(link.get_dot1_index()));
	    Vector4 vec_to = matrix_changes  * dot_to_vec(dots.at(link.get_dot2_index()));
		Dot dot_from = Dot{vec_from[0],vec_from[1],vec_from[2]}.with_center(center);
	    Dot dot_to = Dot{vec_to[0],vec_to[1],vec_to[2]}.with_center(center);




        _drawer->draw_line(dot_from,dot_to);
    }
}
