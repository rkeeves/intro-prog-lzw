#ifndef LZW_SPTREE_H
#define LZW_SPTREE_H

#include "spnode.h"

namespace lzw{
/**
 * SPTree
 *
 *
 */
class SPTree
{
public:
  SPTree();
  
  ~SPTree ();
	
private: 

  SPTree (const SPTree &);
  
  SPTree & operator= (const SPTree &);
	
public:
	
	std::shared_ptr<SPNode> root() const;
	
	std::shared_ptr<SPNode> get(const std::shared_ptr<SPNode> &n, bool rhs) const;
	
public:

	void set(std::shared_ptr<SPNode> &n, bool rhs);
	
public:

	template<typename F>
	void traverse_inorder(F f);
	
	template<typename F>
	void traverse_preorder(F f);
	
	template<typename F>
	void traverse_postorder(F f);
	
	template<typename F>
	void traverse_leafs(F f);
	
private:

	template<typename F>
	void traverse_inorder(const std::shared_ptr<SPNode> &n, bool n_isrhs, int depth, F f);
	
	template<typename F>
	void traverse_preorder(const std::shared_ptr<SPNode> &n, bool n_isrhs, int depth, F f);
	
	template<typename F>
	void traverse_postorder(const std::shared_ptr<SPNode> &n, bool n_isrhs, int depth, F f);
	
	template<typename F>
	void traverse_leafs(const std::shared_ptr<SPNode> &n, int depth, F f);

protected:
	std::shared_ptr<SPNode> root_;
};/* SPTree */


template<typename F>
void SPTree::traverse_inorder(F f)
{ 
	traverse_inorder(root(),false, 0, f); 
}


template<typename F>
void SPTree::traverse_preorder(F f)
{ 
	traverse_preorder(root(),false, 0, f); 
}


template<typename F>
void SPTree::traverse_postorder(F f)
{	
	traverse_postorder(root(),false, 0, f); 
}


template<typename F>
void SPTree::traverse_leafs(F f)
{ 
	traverse_leafs(root(), 0, f);
}


template<typename F>
void SPTree::traverse_inorder(const std::shared_ptr<SPNode> &n, bool n_isrhs, int depth, F f)
{
	if(n){
		traverse_inorder(n->get(true),true,depth+1,f);
		f(n_isrhs,n->leaf(),depth);
		traverse_inorder(n->get(false),false,depth+1,f);
	}
}


template<typename F>
void SPTree::traverse_preorder(const std::shared_ptr<SPNode> &n, bool n_isrhs, int depth, F f)
{
	if(n){
		f(n_isrhs,n->leaf(),depth);
		traverse_preorder(n->get(true),true,depth+1,f);
		traverse_preorder(n->get(false),false,depth+1,f);
	}
}


template<typename F>
void SPTree::traverse_postorder(const std::shared_ptr<SPNode> &n, bool n_isrhs, int depth, F f)
{
	if(n){
		traverse_postorder(n->get(true),true,depth+1,f);
		traverse_postorder(n->get(false),false,depth+1,f);
		f(n_isrhs,n->leaf(),depth);
	}
}


template<typename F>
void SPTree::traverse_leafs(const std::shared_ptr<SPNode> &n, int depth, F f)
{
	if(n){
		if(false == n->any()){
			f(depth);
		}else{
			traverse_leafs(n->get(true),depth+1,f);
			traverse_leafs(n->get(false),depth+1,f);
		}
	}
}
} /* end of namespace lzw */
#endif // LZW_SPTREE_H