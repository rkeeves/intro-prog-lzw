#include "sptree.h"

namespace lzw{

	
SPTree::SPTree() : root_(std::make_shared<SPNode>()){ }


SPTree::~SPTree (){}


SPTree::SPTree(const SPTree &o) : root_(o.root_){}
  

SPTree& SPTree::operator=(const SPTree&o)
{
	root_ = o.root_;
	return *this;
}


SPTree::SPTree(const SPTree &&o) : root_(std::move(o.root_)) {}


SPTree& SPTree::operator=(const SPTree&& o)
{
	root_ = std::move(o.root_);
	return *this;
}
	

std::shared_ptr<SPNode> SPTree::root() const 
{ 
	return root_;
}
	

void SPTree::add(std::shared_ptr<SPNode> &n, bool rhs)
{ 
	if(n){ n->set(rhs,std::make_shared<SPNode>()); } 
}


SPTreeBuilder::SPTreeBuilder(SPTree &tree) : tree_(tree), last_(tree_.root()) {}


SPTreeBuilder& SPTreeBuilder::operator<< (bool rhs)
{
	if(last_){
		auto child = last_->get(rhs);
		if(child){
			last_ = std::move(child);
		}else{
			tree_.add(last_,rhs);
			last_ = tree_.root();
		}
	}
	return *this;
}

} /* end of namespace lzw */