#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP

#include "drawable_block.hpp"

#include <fstream>
#include <vector>


class gamemap {
protected:
	std::pair<unsigned, unsigned> _size;
	std::pair<unsigned, unsigned> _spawn1p;
	std::pair<unsigned, unsigned> _spawn2p;
	std::vector<std::pair<unsigned, unsigned>> _walls;

public:
	gamemap();
	gamemap(const std::pair<unsigned, unsigned>& size, const std::pair<unsigned, unsigned>& spawn1p, const std::pair<unsigned, unsigned>& spawn2p, const std::vector<std::pair<unsigned, unsigned>>& walls);
	gamemap(const gamemap& other);
	const std::pair<unsigned, unsigned>& getSize() const;
	static gamemap* load(std::ifstream& stream);
};

#endif