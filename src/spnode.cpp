#include "spnode.h"

namespace lzw{

	SPNode::SPNode() : lhs_(nullptr), rhs_(nullptr){ }
/*	
	~SPNode ()
	{

	}

	SPNode (const SPNode& o)
	{
		rhs_.r = 
	}

	SPNode& operator= (const SPNode& o)
	{
		
	}
	*/
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
	
	std::shared_ptr<SPNode> SPNode::set(bool rhs, const std::shared_ptr<SPNode>& sp)
	{
		return (rhs) ? ( rhs_ = sp ) : ( lhs_ = sp );
	}
	
} /* end of namespace lzw */