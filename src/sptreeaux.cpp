#include "sptreeaux.h"

#include <iostream>	// for streams
#include <cmath> 		// for sqrt

namespace lzw{

void get_leaf_count_max_depth(SPTree& tree, int &leafCount, int &maxDepth)
{
	leafCount = 0;
	maxDepth = 0;
	auto leafDepthCounter = [&leafCount,&maxDepth](int depth)
	{ 
		leafCount++;
		if(maxDepth < depth) { maxDepth = depth;}
	};
	tree.traverse_leafs(leafDepthCounter);
}


void get_depth_mean(SPTree& tree, int leafCount, double &meanDepth)
{
	meanDepth = 0.0;
	if(leafCount == 0) return;
	auto meanDepthCounter =[leafCount,&meanDepth](int depth)
	{ 
		meanDepth += static_cast<double>(depth)/leafCount;
	};
	tree.traverse_leafs(meanDepthCounter);
}


void get_depth_variance(SPTree& tree, int leafCount, double meanDepth, double &varDepth)
{
	varDepth= 0.0;
	if(leafCount == 0) return;
	auto varDepthCounter = [meanDepth,&varDepth](int depth)
	{ 
		double t = static_cast<double>(depth) - meanDepth;
		varDepth += ( t * t);
	};
	tree.traverse_leafs(varDepthCounter);
	if (leafCount - 1 > 0)
		varDepth = std::sqrt (varDepth / (leafCount - 1));
	else
		varDepth = std::sqrt (varDepth);
}


void print_tree_traversal(std::ostream &os, SPTree& tree, Traversal mode)
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
	switch(mode)
	{
		case Traversal::Preorder:
		{ tree.traverse_preorder(printer); break;}
		case Traversal::Postorder:
		{ tree.traverse_postorder(printer); break;}
		default:
		{ tree.traverse_inorder(printer); break;}
	}			
	int leafs = 0;
	int maxDepth = 0;
	double meanDepth = 0.0;
	double varDepth = 0.0;
	get_leaf_count_max_depth(tree,leafs,maxDepth);
	get_depth_mean(tree,leafs,meanDepth);
	get_depth_variance(tree,leafs,meanDepth,varDepth);
	os << "melyseg="<< maxDepth << std::endl;
	// This typo was historically done in the original too
	os << "altag="<< meanDepth << std::endl;
	os << "szoras="<< varDepth << std::endl;
}


void fill_tree(std::istream &is, SPTree &tree, bool inputAsBitStream, int maxBytesToRead)
{
	SPTreeBuilder builder(tree);
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
			}else if (b == '\n'){
					inComment = false;
					continue;
			}else if (inComment || b == 'N'){
				continue;
			}
			
      if( ( maxBytesToRead > 0 ) && (byteCounter > maxBytesToRead) ){break;}
			
			if(! inputAsBitStream){
				builder << ((b == '0') ? false : true);
			}else{
				for (int i = 0; i < 8; ++i)
				{
						if (b & 0b10000000){ 
							builder << true;
						}else{
							builder << false;
						}
						b <<= 1;
				}
			}
			byteCounter++;
	}
}

} /* end of namespace lzw */