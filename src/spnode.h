#ifndef LZW_SPNODE_H
#define LZW_SPNODE_H

#include <memory>    // smart ptrs

namespace lzw{
class SPNode
{
// [LIFECYCLE]
public:

	SPNode();
	
	~SPNode();

	SPNode (const SPNode&);

	SPNode& operator=(const SPNode&);
	
	SPNode(const SPNode&&);

	SPNode& operator= (const SPNode&&);
	
public:
// [ACCESSORS]

	bool leaf() const;

	std::shared_ptr<SPNode> get(bool rhs) const;
	
// [MODIFIERS]
	
	void set(bool rhs, std::shared_ptr<SPNode>&& sp);
	
	void reset(bool rhs);
	
// [STATE]
private:

	std::shared_ptr<SPNode> lhs_;

	std::shared_ptr<SPNode> rhs_;
}; /* SPNode */
} /* end of namespace lzw */
#endif // LZW_SPNODE_H