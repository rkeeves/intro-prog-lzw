#ifndef ARGS_H
#define ARGS_H

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
	
public:
	Args(int argc, char **argv);
	
	~Args();
	
private:

	Args (const Args &);
	
	Args & operator= (const Args &);
	
// PUBLIC FUNCS
public: 

	const std::string DEFAULT_OPT_KEY = "";

	int count() const;
	
	const std::string operator[](int i) const;

	bool hasOpt(const std::string &opt) const;

	const std::vector<std::string> &getOpt() const;
	
	const std::vector<std::string> & operator[](const std::string &opt) const;

// PRIVATE FUNCS
private:

	void parse();

	bool isOpt(const std::string &s) const;
// PRIVATE FIELDS
private:

	int argc;

	char **argv_head;

	std::map<std::string,std::vector<std::string>> optvals;
};

} /* end of namespace lzw */
#endif // ARGS_H