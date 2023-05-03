#ifndef ISET_H_
#define ISET_H_

template<typename T>
class ISet
{
 public:
	virtual  ~ISet() = default;
	virtual void clear() = 0;


};

#endif //ISET_H_
