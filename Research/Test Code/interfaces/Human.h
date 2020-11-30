#ifndef __HUMAN
#define __HUMAN

#include "IAnimal.h"

class Human : public IAnimal {

public:
	void Speak() override;

};

#endif
