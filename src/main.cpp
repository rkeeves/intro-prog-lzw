#include <iostream>	// cout and i/ostream
#include <fstream>	// file IO
#include <chrono>		// for clocking

#include "args.h"				// argument parsing helper
#include "lzwsptree.h"	// for smart pointer based lzw binary tree

typedef std::chrono::high_resolution_clock Clock;

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
		auto optPos = args[""];
		if(optPos.size() != 2){
			throw std::runtime_error("Input file was NOT specified!");
		}
		in_fname = optPos[1];
		if(!args.hasOpt("-o")){
			throw std::runtime_error("Output file was NOT specified!");
		}
		auto optO = args["-o"];
		if(optO.size() != 1){
			throw std::runtime_error("Output file was NOT specified!");
		}
		out_fname= optO[0];
		
		if(args.hasOpt("-m")){
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
		if(args.hasOpt("-b")){
			inputAsBitStream = false;
		}
		if(args.hasOpt("-t")){
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

void fill_tree(std::istream &is, LzwSPTree &tree, bool inputAsBitStream, int maxBytesToRead){
	char b;
	while (is.read ((char *) &b, sizeof (unsigned char))){
		if (b == '\n') break;
	}
	int byteCounter = 0;
	bool inComment = false;
	while (is.read ((char *) &b, sizeof (unsigned char)))
	{
			if (b == '>'){
					inComment = true;
					continue;
			}
			if (b == '\n'){
					inComment = false;
					continue;
			}
			if (inComment || b == 'N'){
				continue;
			}
			if(byteCounter > maxBytesToRead && maxBytesToRead > 0){
				break;
			}
			if(! inputAsBitStream){
				if (b == '0'){ 
					tree << false;
				}else{
					tree << true;
				}
			}else{
				for (int i = 0; i < 8; ++i)
				{
						if (b & 0b10000000){ 
							tree << true;
						}else{
							tree << false;
						}
						b <<= 1;
				}
			}
			byteCounter++;
	}
}

void print_tree(std::ostream &os, LzwSPTree& tree, int mode)
{ 
	auto printer = [&os](bool n_isrhs, bool n_isleaf, int depth)
										{ 
											os 
												<< std::string(3*(depth+1),'-')
												<< ( (depth==0) ? '/' : ( (n_isrhs) ? '1' : '0' ) ) 
												<< '('  << depth << ')' 
												<< ( (n_isleaf) ? '*' : ' ' ) 
												<< std::endl;
										};
									
	if(mode == 1){
		tree.traverse_preorder(printer);
	}else if( mode == 2){
		tree.traverse_postorder(printer);
	}else{
		tree.traverse_inorder(printer);
	}
	int leafs = 0;
	int maxDepth = 0;
	double meanDepth = 0.0;
	double varDepth = 0.0;
	tree.get_leafCount_maxDepth(leafs,maxDepth);
	tree.get_meanDepth(leafs,meanDepth);
	tree.get_varDepth(leafs,meanDepth,varDepth);
	os << "melyseg="<< maxDepth << std::endl;
	// This typo was historically done in the original too
	os << "altag="<< meanDepth << std::endl;
	os << "szoras="<< varDepth << std::endl;
}
	
int main(int argc, char **argv){
	// ARG HANDLING PHASE
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
  // EXECUTION PHASE
	try{
		std::cout << "Started..." << std::endl;
		std::fstream inFile(appData.in_fname, std::ios_base::in);
		if (!inFile){
				std::cerr << "[EXEC_ERROR]" << "Input file '" << appData.in_fname << "' does not exist!" << std::endl << std::endl;
				usage ();
				return -3;
		}
		LzwSPTree tree;
		auto tstart = Clock::now();
		fill_tree(inFile, tree, appData.inputAsBitStream, appData.maxBytesToRead);
		inFile.close ();
		std::fstream outFile(appData.out_fname, std::ios_base::out);
		print_tree( outFile, tree, appData.printTraversalMode);
		outFile.close ();
		auto tend = Clock::now();
    std::cout 
			<< "Execution done!" << std::endl
			<< std::chrono::duration_cast<std::chrono::seconds>(tend - tstart).count() << " seconds" << std::endl
			<< std::chrono::duration_cast<std::chrono::milliseconds>(tend - tstart).count() << " milliseconds" << std::endl;
		
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