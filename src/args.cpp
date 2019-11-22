#include "args.h"

namespace lzw{

const std::string Args::DEFAULT_OPT = "";


Args::Args(int argc, char **argv) : argc(argc), argv_head(argv)
{
	parse();
}

int Args::argcount() const { return argc; }


const std::string Args::operator[](int i) const
{
	if(i < argc){
		return std::string(*(argv_head+i));
	}else{
		throw std::runtime_error("Specified argument index was out of bounds");
	}
}
	
	
bool Args::has_opt(const std::string &opt) const
{
	return optvals.find(opt) != optvals.end();
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
	optvals[DEFAULT_OPT] = std::vector<std::string>();
	char **cur_arg_ptr = argv_head;
	std::string lastGroup = DEFAULT_OPT;
	for(int i = 0; i < argc; ++i){
		std::string s(*cur_arg_ptr);
		if(is_opt(s)){
			optvals[s] = std::vector<std::string>();
			lastGroup = s;
		}else{
			optvals[lastGroup].push_back(s);
		}
		cur_arg_ptr++;
	}
}


bool Args::is_opt(const std::string &s) const
{
	return (s.size() > 1 && s[0] == '-');
}

} /* end of namespace lzw */