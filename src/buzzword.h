#ifndef _BUZZWORD_H
#define _BUZZWORD_H

class Buzzword {
public:
	virtual ~Buzzword() = default;
	
	virtual bool get(unsigned) const = 0;
	virtual const char *name() const = 0;
	virtual const char *desc() const = 0;
};

#endif
