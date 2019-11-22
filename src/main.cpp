#include <iostream>     // cout and streams
#include <fstream>	    // file IO


#include "args.h"	      // argument parsing helper
#include "sptree.h"     // for smart pointer based lzw binary tree
#include "sptreeaux.h"  // auxiliary funcs

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

struct AppData{
	AppData() : in_fname(""), out_fname(""), maxBytesToRead(-1), inputAsBitStream(true), trav(Traversal::Inorder) {}
	
	std::string in_fname;
	
	std::string out_fname;
	
	int maxBytesToRead;
	
	bool inputAsBitStream;
	
	Traversal trav;
};


void parse_app_data(int argc, char **argv, AppData& appData);


int main(int argc, char **argv){
	AppData appData;
  try{
    parse_app_data(argc, argv,appData);
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
		print_tree_traversal(outFile, tree, appData.trav);
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


void parse_app_data(int argc, char **argv, AppData& appData)
{
	Args args(argc,argv);
	// pos1
	// (in_fname)
	auto optPos = args[Args::DEFAULT_OPT];
	if(optPos.size() < 2){throw std::runtime_error("Input file was NOT specified!");}
	if(optPos.size() > 2){throw std::runtime_error("Too many positional arguments! Did you forget an option before any arg?");}
	appData.in_fname = optPos[1];
	// -o
	// (out_fname)
	if(!args.has_opt("-o")){throw std::runtime_error("Output file was NOT specified!");}
	auto optO = args["-o"];
	if(optO.size() != 1){throw std::runtime_error("Output file was NOT specified!");}
	appData.out_fname= optO[0];
	// -m
	// (maxBytesToRead)
	if(args.has_opt("-m")){
		auto optBytes = args["-m"];
		if(optBytes.size() != 1){
			throw std::runtime_error("Bad maxbytes option!");
		}else{
			try{
				appData.maxBytesToRead = std::stoi( optBytes[0] );
			}catch(...){
				throw std::runtime_error("Bad maxbytes option!");
			}
			if(appData.maxBytesToRead < 1){
				throw std::runtime_error("Bad maxbytes option!");
			}
		}
	}
	// -b
	// (inputAsBitStream)
	if(args.has_opt("-b")){appData.inputAsBitStream = false;}
	// -t
	// (trav)
	if(args.has_opt("-t")){
		auto optBytes = args["-t"];
		if(optBytes.size() != 1){
			throw std::runtime_error("Bad traversal option!");
		}else{
			try{
				int val = std::stoi( optBytes[0] );
				if(val==1){
					appData.trav = Traversal::Preorder;
				}else if(val==2){
					appData.trav = Traversal::Postorder;
				}else{
					appData.trav = Traversal::Inorder;
				}
				
			}catch(...){
				throw std::runtime_error("Bad traversal option!");
			}
		}
	}
}