#include "IAnimal.h"
#ifndef __DOG
#define __DOG

class Dog : public IAnimal {
public:
	void Speak() override;
};

#endif
