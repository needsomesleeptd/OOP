#ifndef MODEL_STRUCTURE_H
#define MODEL_STRUCTURE_H

#include <vector>
#include "../../inc/utils/Scaler.h"
#include "../../inc/utils/Rotator.h"
#include "../../inc/utils/Mover.h"

#include "dot.h"
#include "link.h"

class ModelStructure
{
public:
    ModelStructure() = default;
    ModelStructure(std::vector<Dot> &dots, std::vector<Link> &links);
    ModelStructure(std::vector<Dot> &dots, std::vector<Link> &links, Dot center);
    ~ModelStructure() = default;

    const std::vector<Dot>  &get_dots()   const;
    const std::vector<Link> &get_links()  const;
    const Dot               &get_center() const;

    void add_dot  (const Dot  &dot);
    void add_link (const Link &link);
    void transform(const Mover  &move, const Scaler& scale, const Rotator& rotate);

private:
    Dot _center;
    std::vector<Dot>  _dots;
    std::vector<Link> _links;
};

#endif
