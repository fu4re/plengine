template <typename T>
std::string toString(const T& input)
{
	std::stringstream stream;
	stream << input;
	return stream.str();
}
