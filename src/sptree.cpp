#include "sptree.h"

namespace lzw{
	
	
SPTree::SPTree() : root_(std::make_shared<SPNode>()){ }
 

SPTree::~SPTree (){ }


std::shared_ptr<SPNode> SPTree::root() const 
{ 
	return root_; 
}
	
std::shared_ptr<SPNode> SPTree::get(const std::shared_ptr<SPNode> &n, bool rhs) const 
{ 
	return (n) ? n->get(rhs) : n; 
}
	
void SPTree::set(std::shared_ptr<SPNode> &n, bool rhs)
{ 
	if(n){ n->set(rhs); } 
}


} /* end of namespace lzw */