#ifndef OBSERVER_H
#define OBSERVER_H

#include "Subject.h"

namespace controller
{
	namespace util
	{
		
		// Forward declare wegen circular dependency
		class Subject;

		class Observer
		{
		public:
			Observer(void);
			virtual ~Observer(void);
			virtual void notify(Subject *sub) = 0;
		};

	}

}

#endif