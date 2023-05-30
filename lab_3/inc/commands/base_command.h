#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include <string>
#include "memory"
#include "scene_manager.h"
#include "transform_manager.h"
#include "load_manager.h"
#include "model.h"

using namespace  std;

class Command
{
public:
    Command() = default;
    virtual ~Command() = default;

    virtual void exec() = 0;
};

template<typename Reseiver>
class BaseCommand: public Command
{
	using Action = void(Reseiver::*)();
	using Pair = pair<shared_ptr<Reseiver>, Action>;

 protected:
	Pair call;

 public:
	BaseCommand(shared_ptr<Reseiver> r, Action a) : call(r, a) {};

	void exec() override { ((*call.first).*call.second)(); };
};




template <typename Receiver>
class CameraBaseCommand : public BaseCommand<Receiver> { };

template <typename Receiver>
class ModelBaseCommand : public BaseCommand<Receiver> { };

template <typename Receiver>
class TransformBaseCommand : public BaseCommand<Receiver> { };



#endif
