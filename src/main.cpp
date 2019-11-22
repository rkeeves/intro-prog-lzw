#include <iostream>	// cout and i/ostream
#include <fstream>	// file IO

#include "args.h"				// argument parsing helper
#include "sptree.h"	// for smart pointer based lzw binary tree
#include "sptreeaux.h" // auxiliary funcs
using namespace lzw;

void usage (void)
{
  std::cout << "Binary tree reader/writer for Lempel-Ziv-Welch algorithm" << std::endl;
  std::cout << "Usage: lzwtree [IN_FILE] -o [OUT_FILE]" << std::endl;
  std::cout << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  " << "-o,  output file to write (required)" << std::endl;
  std::cout << "  " << "-m,  max bytes to read" << std::endl;
  std::cout << "  " << "-b,  treat char '0' as a single true bit, else as a single false bit" << std::endl;
  std::cout << "  " << "-t,  traversal for print: 1 preorder, 2 postorder, else inorder" << std::endl;
}


class AppData{
public:
	AppData() : in_fname(""), out_fname(""), maxBytesToRead(-1), inputAsBitStream(true), printTraversalMode(0) {}
	
	void parse(int argc, char **argv){
		Args args(argc,argv);
		auto optPos = args[Args::DEFAULT_OPT];
		if(optPos.size() != 2){
			throw std::runtime_error("Input file was NOT specified!");
		}
		in_fname = optPos[1];
		if(!args.has_opt("-o")){
			throw std::runtime_error("Output file was NOT specified!");
		}
		auto optO = args["-o"];
		if(optO.size() != 1){
			throw std::runtime_error("Output file was NOT specified!");
		}
		out_fname= optO[0];
		
		if(args.has_opt("-m")){
			auto optBytes = args["-m"];
			if(optBytes.size() != 1){
				throw std::runtime_error("Bad maxbytes option!");
			}else{
				try{
					maxBytesToRead = std::stoi( optBytes[0] );
				}catch(...){
					throw std::runtime_error("Bad maxbytes option!");
				}
				if(maxBytesToRead < 1){
					throw std::runtime_error("Bad maxbytes option!");
				}
			}
		}
		if(args.has_opt("-b")){
			inputAsBitStream = false;
		}
		if(args.has_opt("-t")){
			auto optBytes = args["-t"];
			if(optBytes.size() != 1){
				throw std::runtime_error("Bad traversal option!");
			}else{
				try{
					printTraversalMode = std::stoi( optBytes[0] );
				}catch(...){
					throw std::runtime_error("Bad traversal option!");
				}
			}
		}
	}
	
public:
	std::string in_fname;
	std::string out_fname;
	int maxBytesToRead;
	bool inputAsBitStream;
	int printTraversalMode;
};


int main(int argc, char **argv){
	AppData appData;
  try{
    appData.parse(argc, argv);
  }catch(const std::exception &e){
    std::cerr << "[ARGUMENT_ERROR] " << e.what() << std::endl << std::endl;
    usage ();
    return -1;
  }catch(...){
    std::cerr << "[ARGUMENT_ERROR] " << "Unknown error during argument parsing!" << std::endl << std::endl;
    usage ();
    return -2;
  }
	try{
		std::cout << "Started..." << std::endl;
		std::fstream inFile(appData.in_fname, std::ios_base::in);
		if (!inFile){
				std::cerr << "[EXEC_ERROR]" << "Input file '" << appData.in_fname << "' does not exist!" << std::endl << std::endl;
				usage ();
				return -3;
		}
		SPTree tree;
		fill_tree(inFile, tree, appData.inputAsBitStream, appData.maxBytesToRead);
		inFile.close ();
		std::fstream outFile(appData.out_fname, std::ios_base::out);
		print_tree_traversal(outFile, tree, Traversal::Inorder);
		outFile.close ();
    std::cout << "Execution done!" << std::endl;
		
  }catch(const std::exception &e){
    std::cerr << "[EXEC_ERROR] " << e.what() << std::endl << std::endl;
    usage ();
    return -4;
  }catch(...){
    std::cerr << "[EXEC_ERROR] " << "Unknown error during execution!" << std::endl << std::endl;
    usage ();
    return -5;
  }
  return 0;
}