#ifndef PATH_H
#define PATH_H

#include "Vector3.h"

class Path {
public:
	enum {
		START,
		END,
		NUM_POINTS,
	};

	Vector3 point[NUM_POINTS];
	Vector3 side;

	Path(void) {};
	Path(Vector3 start, Vector3 end, Vector3 side = Vector3(0, 0, 0)) {point[START] = start; point[END] = end; this->side = side;};
	~Path(void) {};

	Vector3 dir() const {return point[END] - point[START];};
	float length() {return dir().Length();};
	bool haveSide() {return (side == Vector3() ? false : true);};

	Path operator- (void) {return Path(this->point[END], this->point[START]);};
};

#endif