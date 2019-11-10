#ifndef LZW_SPNODE_H
#define LZW_SPNODE_H

#include <memory> // for smart pointers

namespace lzw{
/**
 * SPNode
 *
 *
 */
class SPNode
{
	
public:

	SPNode();
	
	~SPNode ();
	
private: 

	SPNode (const SPNode &);

	SPNode & operator= (const SPNode &);

public:

	bool test(bool rhs) const;
	
	bool any() const;

	bool leaf() const;
	
	std::shared_ptr<SPNode> get(bool rhs) const;
	
	std::shared_ptr<SPNode> set(bool rhs);
	
private:
	
	std::shared_ptr<SPNode> lhs_;
	
	std::shared_ptr<SPNode> rhs_;
}; /* SPNode */
} /* end of namespace lzw */
#endif // LZW_SPNODE_H