#include <TyActor.h>

class InheritedActor : public ITyActor
{
public:
	InheritedActor() : ITyActor(0) { }
	~InheritedActor() { }
};