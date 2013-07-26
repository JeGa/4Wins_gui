#include "Subject.h"

namespace controller
{

	namespace util
	{

		Subject::Subject(void)
		{
		}

		Subject::~Subject(void)
		{
		}

		void Subject::addObserver(Observer *obs)
		{
			observer.push_back(obs);
		}

		void Subject::removeObserver(Observer *obs)
		{
			observer.remove(obs);
		}

		void Subject::notifyObservers()
		{
			for (std::list<Observer*>::iterator it = observer.begin();
				it != observer.end(); it++) {
				Subject *ptr = this;
				(*it)->notify(ptr);
			}
		}

	}

}
