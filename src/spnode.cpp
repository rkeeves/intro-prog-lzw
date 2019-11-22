#include "spnode.h"

#include <utility>	// move

namespace lzw{


	SPNode::SPNode() : lhs_(nullptr), rhs_(nullptr) 
	{
		
	}

	
	SPNode::~SPNode ()
	{	

	}

	
	SPNode::SPNode (const SPNode& o) : lhs_(o.lhs_), rhs_(o.rhs_)
	{
		
	}

	
	SPNode& SPNode::operator=(const SPNode& o)
	{
		lhs_ = o.lhs_;
		rhs_ = o.rhs_;
		return *this;
	}
	
	
	SPNode::SPNode(const SPNode&& o) :  lhs_(std::move(o.lhs_)), rhs_(std::move(o.rhs_)) 
	{
		
	}

	
	SPNode& SPNode::operator= (const SPNode&& o) {
		lhs_ = std::move(o.lhs_);
		rhs_ = std::move(o.rhs_);
		return *this;
	}
	

	bool SPNode::leaf() const 
	{ 
		return ( !(rhs_) && !(lhs_));
	}
	
	
	std::shared_ptr<SPNode> SPNode::get(bool rhs) const
	{ 
		return rhs ? rhs_ : lhs_; 
	}
	
	
	void SPNode::set(bool rhs, std::shared_ptr<SPNode>&& sp)
	{
		(rhs) ? ( rhs_ = std::move(sp) ) : ( lhs_ = std::move(sp) );
	}
	
	
	void SPNode::reset(bool rhs)
	{
		(rhs) ? ( rhs_.reset() ) : ( lhs_.reset() );
	}
	
} /* end of namespace lzw */