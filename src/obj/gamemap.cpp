#include "../../include/obj/gamemap.hpp"

#include "../../external/nlohmann/json.hpp"


gamemap::gamemap():
	_size(0, 0), _spawn(0, 0), _walls({}) { }

gamemap::gamemap(const std::pair<unsigned, unsigned>& size, const std::pair<unsigned, unsigned>& spawn, const std::vector<std::pair<unsigned, unsigned>>& walls):
	_size(size), _spawn(spawn), _walls(walls) { }

gamemap::gamemap(const gamemap& other):
	_size(other._size), _spawn(other._spawn), _walls(other._walls) { };

const std::pair<unsigned, unsigned>& gamemap::getSize() const { return _size; }

gamemap* gamemap::load(std::ifstream& stream) {
	nlohmann::json json = nlohmann::json::parse(stream);

	return new gamemap(json["map"]["size"], json["snake"]["origin"], json["map"]["walls"]);
}