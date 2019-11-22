#ifndef LZW_SPTREEAUX_H
#define LZW_SPTREEAUX_H

#include "sptree.h" // for the SPTree

namespace lzw{


void get_leaf_count_max_depth(SPTree& tree, int &leafCount, int &maxDepth);


void get_depth_mean(SPTree& tree, int leafCount, double &meanDepth);


void get_depth_variance(SPTree& tree, int leafCount, double meanDepth, double &varDepth);


enum class Traversal{
	Inorder,
	Preorder,
	Postorder
};


void print_tree_traversal(std::ostream &os, SPTree& tree, Traversal mode);


void fill_tree(std::istream &is, SPTree &tree, bool inputAsBitStream, int maxBytesToRead);

} /* end of namespace lzw */
#endif // LZW_SPTREEAUX_H