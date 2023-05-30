#include "facade.h"

void Facade::exec(Command &command)
{
    command.execute();
}
