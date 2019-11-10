#include "lzwsptree.h"

#include <cmath> // sqrt

namespace lzw{
	
	
LzwSPTree::LzwSPTree() : SPTree() , last_(root()){ }


LzwSPTree::~LzwSPTree (){ }


LzwSPTree& LzwSPTree::operator<< (bool rhs)
{ 
	auto child = get(last_,rhs);
	if(child){
		last_ = child;
	}else{
		set(last_,rhs);
		last_ = root();
	}
	return *this;
}


// Count leafs and max of all leaf depths
void LzwSPTree::get_leafCount_maxDepth(int &leafCount, int &maxDepth)
{
	leafCount = 0;
	maxDepth = 0;
	auto leafDepthCounter = [&leafCount,&maxDepth](bool n_isrhs, int depth)
													{ 
														leafCount++;
														if(maxDepth < depth) { maxDepth = depth;}
													};
	traverse_leafs(leafDepthCounter);
}


// Calculate mean of depths
void LzwSPTree::get_meanDepth(int leafCount, double &meanDepth)
{
	meanDepth = 0.0;
	if(leafCount == 0) return;
	auto meanDepthCounter =[leafCount,&meanDepth](bool n_isrhs, int depth)
													{ 
														meanDepth += static_cast<double>(depth)/leafCount;
													};
	traverse_leafs(meanDepthCounter);
}


// Calculate variance of depths
void LzwSPTree::get_varDepth(int leafCount, double meanDepth, double &varDepth)
{
	varDepth= 0.0;
	if(leafCount == 0) return;
	auto varDepthCounter = [meanDepth,&varDepth](bool n_isrhs, int depth)
													{ 
														double t = static_cast<double>(depth) - meanDepth;
														varDepth += ( t * t);
													};
	traverse_leafs(varDepthCounter);
	if (leafCount - 1 > 0)
		varDepth = std::sqrt (varDepth / (leafCount - 1));
	else
		varDepth = std::sqrt (varDepth);
}
} /* end of namespace lzw */