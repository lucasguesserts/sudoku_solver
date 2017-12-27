#ifndef POSITION_H
#define POSITION_H

#include <utility>

struct Position: public std::pair<unsigned,unsigned>
{
	public:
		Position(const unsigned row = 0, const unsigned column = 0);
		void set(const unsigned row, const unsigned column);

		unsigned & row = this->first;
		unsigned & column = this->second;
};

#endif
