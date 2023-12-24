#include "../../include/obj/gamemap.hpp"

#include "../../external/nlohmann/json.hpp"


gamemap::gamemap():
	_size(0, 0), _spawn1p(0, 0), _spawn2p(0, 0), _walls({}) { }

gamemap::gamemap(const std::pair<unsigned, unsigned>& size, const std::pair<unsigned, unsigned>& spawn1p, const std::pair<unsigned, unsigned>& spawn2p, const std::vector<std::pair<unsigned, unsigned>>& walls):
	_size(size), _spawn1p(spawn1p), _spawn2p(spawn2p), _walls(walls) { }

gamemap::gamemap(const gamemap& other):
	_size(other._size), _spawn1p(other._spawn1p), _spawn2p(other._spawn2p), _walls(other._walls) { };

const std::pair<unsigned, unsigned>& gamemap::getSize() const { return _size; }

gamemap* gamemap::load(std::ifstream& stream) {
	nlohmann::json json = nlohmann::json::parse(stream);

	return new gamemap(json["map"]["size"], json["snake"]["origin1p"], json["snake"]["origin2p"], json["map"]["walls"]);
}