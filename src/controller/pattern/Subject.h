#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>
#include "Observer.h"

namespace controller
{
	namespace util
	{

		// Forward declare wegen circular dependency
		class Observer;

		class Subject
		{
		private:
			std::list<Observer*> observer;
		protected:
			void notifyObservers();
		public:
			Subject(void);
			virtual ~Subject(void);			
			void addObserver(Observer *obs);
			void removeObserver(Observer *obs);
		};

	}

}

#endif