#include "sptree.h"

namespace lzw{
	
	
SPTree::SPTree() : root_(std::make_shared<SPNode>()){ }


std::shared_ptr<SPNode> SPTree::root() const 
{ 
	return root_; 
}
	

std::shared_ptr<SPNode> SPTree::get(const std::shared_ptr<SPNode> &n, bool rhs) const 
{ 
	return (n) ? n->get(rhs) : n; 
}
	

void SPTree::set(std::shared_ptr<SPNode> &n, bool rhs, const std::shared_ptr<SPNode> &child)
{ 
	if(n){ n->set(rhs,child); } 
}


SPTreeBuilder::SPTreeBuilder(SPTree &tree) : tree_(tree), last_(tree_.root()) {}


SPTreeBuilder& SPTreeBuilder::operator<< (bool rhs)
{
	auto child = tree_.get(last_,rhs);
	if(child){
		last_ = child;
	}else{
		tree_.set(last_,rhs, std::make_shared<SPNode>());
		last_ = tree_.root();
	}
	return *this;
}

} /* end of namespace lzw */