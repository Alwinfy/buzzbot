#ifndef _ALL_H
#define _ALL_H

#include <memory>

#include "buzz.h"
#include "bang.h"
#include "crash.h"
#include "fibbi.h"
#include "pop.h"
#include "prod.h"
#include "squawk.h"
#include "whizz.h"
#include "whirr.h"
#include "zip.h"
#include "zoob.h"
#include "sump.h"
#include "cackle.h"
#include "prod.h"
#include "zoob.h"
#include "whirr.h"

const std::initializer_list<std::unique_ptr<Buzzword>> ALL_WORDS = {
	std::unique_ptr<Buzzword>(new Buzz),
	std::unique_ptr<Buzzword>(new Bang),
	std::unique_ptr<Buzzword>(new Crash),
	std::unique_ptr<Buzzword>(new Fibbi),
	std::unique_ptr<Buzzword>(new Pop),
	std::unique_ptr<Buzzword>(new Squawk),
	std::unique_ptr<Buzzword>(new Whizz),
	std::unique_ptr<Buzzword>(new Zip),
	std::unique_ptr<Buzzword>(new Sump),
	std::unique_ptr<Buzzword>(new Cackle),
	std::unique_ptr<Buzzword>(new Prod),
	std::unique_ptr<Buzzword>(new Zoob),
	std::unique_ptr<Buzzword>(new Whirr)
};

#endif
