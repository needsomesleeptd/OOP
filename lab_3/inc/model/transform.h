//
// Created by Андрей on 31.05.2023.
//

#ifndef INC_3_INC_MODEL_TRANSFORM_H_
#define INC_3_INC_MODEL_TRANSFORM_H_



#include "dot.h"

class TransformParams {
 public:
	TransformParams()
	{
		_moveParams = Dot{0,0,0};
		_scaleParams = Dot{1,1,1};
		_rotateParams = Dot{0,0,0};

	}
	TransformParams(const Dot &moveParams, const Dot &scaleParams, const Dot &rotateParams)
		: _moveParams(moveParams), _scaleParams(scaleParams), _rotateParams(rotateParams) {};
	TransformParams(const TransformParams &transform) = default;
	~TransformParams() = default;

	[[nodiscard]] Dot getMoveParams() const noexcept { return _moveParams; };
	[[nodiscard]] Dot getScaleParams() const noexcept { return _scaleParams; };
	[[nodiscard]] Dot getRotateParams() const noexcept { return _rotateParams; };

	void setMoveParams(Dot &moveParams) { _moveParams = moveParams; };
	void setScaleParams(Dot &scaleParams) { _scaleParams = scaleParams; };
	void setRotateParams(Dot &rotateParams) { _rotateParams = rotateParams; };

 private:
	Dot _moveParams;
	Dot _scaleParams;
	Dot _rotateParams;
};

#endif //INC_3_INC_MODEL_TRANSFORM_H_
