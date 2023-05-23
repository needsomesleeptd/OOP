//
// Created by Андрей on 23.05.2023.
//

#ifndef INC_3_LAB_LAB_03_3_LAB_FIGURE_FIGURE_H_
#define INC_3_LAB_LAB_03_3_LAB_FIGURE_FIGURE_H_

#include <vector>

#include "Edge/Edge.h"
#include "Point/Point.h"


class Figure
{
 private:
	std::vector<Point> _points;
	std::vector<Edge> _edges;
	Point _center;

 public:
	Figure() = default;
	Figure(std::vector<Point> &points, std::vector<Edge> &edges);
	Figure(std::vector<Point> &points, std::vector<Edge> &edges, Point &center);
	Figure(const Figure & other) = default;
	~Figure() = default;

	const std::vector<Point> &getPoints() const;
	const std::vector<Edge> &getEdges() const;
	const Point getCenter() const;

	void addPoint(const Point &point);
	void addEdge(const Edge &edge);
	void updateCenter();

	void moveVertexesToOrigin(const Point &center);
	void movePointsToCenter(const Point &center);
	void transformPoints(const Matrix<double> &mtr);
	void transform(const Matrix<double> &mtr, const Point &center);
};

#endif //INC_3_LAB_LAB_03_3_LAB_FIGURE_FIGURE_H_
