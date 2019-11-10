#include "args.h"

namespace lzw{

Args::Args(int argc, char **argv) : argc(argc), argv_head(argv)
{
	parse();
}

Args::~Args()
{
	
}

int Args::count() const
{
	return argc;
}

const std::string Args::operator[](int i) const
{
	if(i < argc){
		return std::string(*(argv_head+i));
	}else{
		throw std::runtime_error("Specified argument index was out of bounds");
	}
}
	
bool Args::hasOpt(const std::string &opt) const
{
	return optvals.find(opt) != optvals.end();
}

const std::vector<std::string> & Args::getOpt() const
{
	return optvals.find(DEFAULT_OPT_KEY)->second;
}

 const std::vector<std::string> & Args::operator[](const std::string &opt) const
{
	auto it = optvals.find(opt);
	if(it == optvals.end()){
		 throw std::runtime_error("Specified opt did not exist");
	}else{
		return it->second;
	}
}

void Args::parse()
{
	optvals[DEFAULT_OPT_KEY] = std::vector<std::string>();
	char **cur_arg_ptr = argv_head;
	std::string lastGroup = DEFAULT_OPT_KEY;
	for(int i = 0; i < argc; ++i){
		std::string s(*cur_arg_ptr);
		if(isOpt(s)){
			optvals[s] = std::vector<std::string>();
			lastGroup = s;
		}else{
			optvals[lastGroup].push_back(s);
		}
		cur_arg_ptr++;
	}
}
	
bool Args::isOpt(const std::string &s) const
{
	return (s.size() > 1 && s[0] == '-');
}

} /* end of namespace lzw */