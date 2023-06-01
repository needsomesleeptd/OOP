#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <utility>

#include "model.h"
#include "dot.h"
#include "link.h"
#include "model_struct.h"
#include "visitor.h"
#include "draw_manager.h"
#include "transform_manager.h"



class Model : public VisibleObject
{
    friend void DrawManager::visit(Model &model);


public:
    Model() : _modelStructure(new ModelStructure) { }
    Model(const Model &model);
    explicit Model(const std::shared_ptr<ModelStructure> &modelStructure) : _modelStructure(modelStructure) {}
    ~Model() override = default;

    void transform(const TransformParams& transform_params) override;

	void accept(std::shared_ptr<Visitor> visitor) override;

protected:
    std::shared_ptr<ModelStructure> _modelStructure;
};

#endif
