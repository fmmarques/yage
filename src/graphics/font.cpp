#include <iostream>
# include <yage/graphics/font.hpp> // for deleters;

namespace yage {
namespace graphics {
namespace interface1 {
	
void __font_deleter_wrapper_t::operator()(TTF_Font *font)
{
	std::string fn{ std::string(__PRETTY_FUNCTION__) + std::string(": ") };
	std::cout << fn << "deleting font at " << std::hex << font << std::dec << std::endl;
}

font::font(const std::string& name, const std::shared_ptr<TTF_Font>& ptr):
  n{name}
, f{ptr}
, t{nullptr}
, ss{}
{}

font::font(font&& other):
  n{std::move(other.n)}
, f{std::move(other.f)}
, t{nullptr}
, ss{std::move(other.ss)}
{}

font::font(const font& other) :
  n{other.n}
, f{ other.f }
, t{nullptr}
, ss{other.ss.str()}
{}

font::~font()
{
	yage::graphics::font_manager::instance().on_release(n);
}

font& font::operator=(font&& other)
{
	n = std::move(other.n);
	f = std::move(other.f);
	t = nullptr;
	ss.str();
	ss << other.ss.str();
}

font& font::operator=(const font& other)
{
	n = std::move(other.n);
	f = std::move(other.f);
	t = nullptr;
	ss.str();
	ss << other.ss.str();
}

font& font::operator<<(const std::string& t)
{
	ss << t;
}

