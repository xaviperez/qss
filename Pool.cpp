#include "Pool.h"

void Pool::Add(GameObject* object) {
	_objects.push_back(object);
	_length++;
}

GameObject* Pool::Get() {
	GameObject* object = _objects.at(_current);
	_current++;

	if (_current >= _length) {
		_current = 0;
	}

	return object;
}