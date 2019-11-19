#include "spnode.h"

namespace lzw{

	SPNode::SPNode() : lhs_(nullptr), rhs_(nullptr){ }
	
	SPNode::~SPNode (){  }
	

	bool SPNode::test(bool rhs) const 
	{
		return (rhs) ? static_cast<bool>(rhs_) : static_cast<bool> (lhs_);
	}
	
	bool SPNode::any() const 
	{ 
		return ((rhs_) || (lhs_));
	}

	bool SPNode::leaf() const 
	{ 
		return ( !(rhs_) && !(lhs_));
	}
	
	std::shared_ptr<SPNode> SPNode::get(bool rhs) const
	{ 
		return rhs ? rhs_ : lhs_; 
	}
	
	std::shared_ptr<SPNode> SPNode::set(bool rhs)
	{
		return (rhs) ? ( rhs_ = std::make_shared<SPNode>() ) : ( lhs_ = std::make_shared<SPNode>() );
	}
	
} /* end of namespace lzw */