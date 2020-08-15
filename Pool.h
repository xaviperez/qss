#pragma once
#include <vector>
#include "GameObject.h"

class Pool {
	
public:

	void Add(GameObject* object);
	GameObject* Get();

private:
	std::vector<GameObject*> _objects = {};
	int _length = 0;
	int _current = 0;
};