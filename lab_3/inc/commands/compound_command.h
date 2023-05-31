//
// Created by Андрей on 30.05.2023.
//

#ifndef INC_3_INC_COMMANDS_COMPOUND_COMMAND_H_
#define INC_3_INC_COMMANDS_COMPOUND_COMMAND_H_

#include "base_command.h"
#include "vector"
#include "memory"

using namespace std;

class CompoundCommand : public BaseCommand
{
	using VectorCommand = vector<shared_ptr<BaseCommand>>;

 private:
	VectorCommand vec;

 public:
	CompoundCommand(initializer_list<shared_ptr<BaseCommand>> lt);

	virtual void execute() override;
};
#endif //INC_3_INC_COMMANDS_COMPOUND_COMMAND_H_
