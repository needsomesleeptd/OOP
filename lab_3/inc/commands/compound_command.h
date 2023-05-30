//
// Created by Андрей on 30.05.2023.
//

#ifndef INC_3_INC_COMMANDS_COMPOUND_COMMAND_H_
#define INC_3_INC_COMMANDS_COMPOUND_COMMAND_H_

#include "base_command.h"
#include "vector"

using namespace std;

class CompoundCommand : public Command
{
	using VectorCommand = vector<shared_ptr<Command>>;

 private:
	VectorCommand vec;

 public:
	CompoundCommand(initializer_list<shared_ptr<Command>> lt);

	virtual void execute() override;
};
#endif //INC_3_INC_COMMANDS_COMPOUND_COMMAND_H_
