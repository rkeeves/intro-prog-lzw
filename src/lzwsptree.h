#ifndef LZW_LZWSPTREE_H
#define LZW_LZWSPTREE_H

#include "sptree.h"

namespace lzw{
/**
 * LzwSPTree
 *
 *
 */
class LzwSPTree : public SPTree {
	public:
		
		LzwSPTree();
		
		~LzwSPTree ();
	
	private:
	
		LzwSPTree (const LzwSPTree &o);
		
		LzwSPTree& operator= (const LzwSPTree &o);
		
	public:
		
		LzwSPTree& operator<< (bool rhs);

	public:
		
		// Counts leafs and max of all leaf depths
		void get_leafCount_maxDepth(int &leafCount, int &maxDepth);
		
		// Calculates mean of depths
		void get_meanDepth(int leafCount, double &meanDepth);
		
		// Calculates variance of depths
		void get_varDepth(int leafCount, double meanDepth, double &varDepth);
		
	private:
		
		std::shared_ptr<SPNode> last_;
	}; /* LzwSPTree */
} /* end of namespace lzw */
#endif // LZW_LZWSPTREE_H