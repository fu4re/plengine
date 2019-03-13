#include "Common.h"

enum e_type
{
	Error,
	Warning,
	Info,
	Service,
	Closed
};

template <typename ...Arg>
std::string format(const std::string& format, Arg&& ...t_arg)  //... - additional argument is possible(supports sprintf)
{
	auto size = std::snprintf(nullptr, 0, format.c_str(), std::forward<Arg>(t_arg)...); //c_str returns a pointer to an array of characters
	std::string output(size, '\0');	
	sprintf(&output[0], format.c_str(), std::forward<Arg>(t_arg)...);
	return output;
}

template <typename ...Arg>
void Log(int type, std::string path, std::string message, std::string file, Arg&& ...t_arg)
{
	//listFile = listFiles("D:/GameDev/Log/Log");
	//foundFile = find(listFile.begin(), listFile.end(), file);

	std::string t_type;
	switch (type)
	{
	case e_type::Error:
	{
		t_type = "Error";
		break;
	}
	case e_type::Warning:
	{
		t_type = "Warning";
		break;
	}
	case e_type::Info:
	{
		t_type = "Info";
		break;
	}
	case e_type::Service:
	{
		t_type = "Service";
		break;
	}
	case e_type::Closed:
	{
		t_type = "Closed";
		break;
	}
	default:
		t_type = "Unknown";
		break;
	}
	
	std::string out = format("Log: (%s, %s) -> %s", t_type.c_str(), path.c_str(), format(message, t_arg...).c_str());
	
	std::ofstream ofs;
	ofs.open("C:/Log/log.txt", std::ios::app); //file path

	if (t_type == "Closed")
	{
		std::string c_out = format(("Log: (%s, %s) -> %s", t_type.c_str(), path.c_str(), format(message, t_arg...).c_str());
		ofs << out.c_str() << std::endl;
		ofs.close();
		std::cout << "file closed" << std::endl;
	}
	else
	{
		ofs << out.c_str() << std::endl;
	}

	printf("%s\n", out.c_str()); //for console
}