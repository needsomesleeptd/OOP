#ifndef VISITOR_H
#define VISITOR_H

class Model;
class Camera;
class Composite;

class Visitor
{
public:
    Visitor() = default;
    ~Visitor() = default;

    virtual void visit(Model &model) = 0;
    virtual void visit(Camera &viewer) = 0;
    virtual void visit(Composite &composite) = 0;
};

#endif
