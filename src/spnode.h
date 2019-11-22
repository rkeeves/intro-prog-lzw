#ifndef LZW_SPNODE_H
#define LZW_SPNODE_H

#include <memory> // for smart pointers

namespace lzw{
class SPNode
{
// [LIFECYCLE]
public:

	SPNode();
	
	~SPNode () = default;

	SPNode (const SPNode&) = delete;

	SPNode& operator= (const SPNode&) = delete;
	
	SPNode (const SPNode&&) = delete;

	SPNode& operator= (const SPNode&&) = delete;
	
// [ACCESSORS]
public:

	bool test(bool rhs) const;
	
	bool any() const;

	bool leaf() const;
	
	std::shared_ptr<SPNode> get(bool rhs) const;
	
// [MODIFIERS]
public:
	std::shared_ptr<SPNode> set(bool rhs, const std::shared_ptr<SPNode>& sp);
	
// [STATE]
private:
	
	std::shared_ptr<SPNode> lhs_;
	
	std::shared_ptr<SPNode> rhs_;
}; /* SPNode */
} /* end of namespace lzw */
#endif // LZW_SPNODE_H