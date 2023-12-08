#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP

#include "drawable_block.hpp"

#include <fstream>
#include <vector>


class gamemap {
protected:
	std::pair<unsigned, unsigned> _size;
	std::pair<unsigned, unsigned> _spawn;
	std::vector<std::pair<unsigned, unsigned>> _walls;

public:
	gamemap();
	gamemap(const std::pair<unsigned, unsigned>& size, const std::pair<unsigned, unsigned>& spawn, const std::vector<std::pair<unsigned, unsigned>>& walls);
	gamemap(const gamemap& other);
	const std::pair<unsigned, unsigned>& getSize() const;
	static gamemap* load(std::ifstream& stream);
};

#endif