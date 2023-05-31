//
// Created by Андрей on 30.05.2023.
//
#include "compound_command.h"

CompoundCommand::CompoundCommand(initializer_list<shared_ptr<BaseCommand>> lt)
{
	for (auto&& elem : lt)
		vec.push_back(elem);
}

void CompoundCommand::execute()
{
	for (auto com : vec)
		com->execute();
}