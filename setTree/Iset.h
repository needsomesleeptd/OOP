#ifndef ISET_H_
#define ISET_H_

template<typename T>
class ISet
{
 public:
	virtual  ~ISet() = default;
	virtual void clear() = 0;
	virtual bool add(const T& data) = 0;
	virtual bool remove(const T& key) = 0;
	virtual bool isIn(const T& key) = 0;


	virtual void set_union(ISet* other) = 0;
	virtual void set_symmDifference(ISet* other) = 0;
	virtual void set_intersection(ISet* other) = 0;

};

#endif //ISET_H_
