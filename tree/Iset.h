#ifndef ISET_H_
#define ISET_H_

template<typename T>
class ISet
{
 public:
	virtual  ~ISet() = default;
	virtual void clear() = 0;
	virtual void add(const T& data) = 0;
	virtual void remove(const T& key) = 0;
	virtual void find(const T& key) = 0;

	virtual ISet* set_union(ISet* other) = 0;
	virtual ISet* set_SymmDifference(ISet* other) = 0;
	virtual ISet* set_Intersection(ISet* other) = 0;

};

#endif //ISET_H_
