#ifndef LZW_ARGS_H
#define LZW_ARGS_H

#include <exception> 	// for exception throwing
#include <string>			// string handling		
#include <vector>			// for storing "lists" of values 
#include <map>				// for storing by keys

namespace lzw{
  // Dumb command line arg handler.
  //
  // Command line args are categorized into:
  //  - argopt : Any string starting with '-'
  //  - argvalue : Any string not starting with '-'
  //
  // Argvalues are associated to argopts by the following rules:
  //  - if an argvalue's predecessor in the arg array was an argopt,
  //    the argvalue will become an element of the argopt
  //  - if an argvalue's predecessor was an element of an argopt,
  //    then the current argvalue will become an element of that argopt
  //  - otherwise the argvalue will become an element of the default argopt.
  //    This default argopt is referred as ""
  // 
  // Example:
  // a b -c d -e f g -h
  // Opt    Elements
  // ""     {"a","b"}
  // "-c"   {"d"}  
  // "-e"   {"f","g"}
  // "-h"   {}
  //
class Args{
// [LIFECYCLE]
public:
	Args(int argc, char **argv);
	
	~Args() = default;

	Args (const Args &) = delete;
	
	Args& operator= (const Args&) = delete;
	
	Args (Args&&) noexcept = delete;
	
	Args& operator= (Args&&) = delete;
	
// [ACCESSORS]
public: 

	static const std::string DEFAULT_OPT;
	
	int argcount() const;
	
	const std::string operator[](int i) const;

	bool has_opt(const std::string &opt) const;

	const std::vector<std::string> &get_default_opt() const;
	
	const std::vector<std::string> & operator[](const std::string &opt) const;

// [INTERNALS]
private:

	void parse();

	bool is_opt(const std::string &s) const;
	
// [STATE]	
	int argc;
	
	char **argv_head;
	
	std::map<std::string,std::vector<std::string>> optvals;
};

} /* end of namespace lzw */
#endif // LZW_ARGS_H