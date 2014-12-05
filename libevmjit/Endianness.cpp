
#include "Endianness.h"

#include <llvm/IR/IntrinsicInst.h>

#include "Type.h"

namespace dev
{
namespace eth
{
namespace jit
{

llvm::Value* Endianness::bswapIfLE(llvm::IRBuilder<>& _builder, llvm::Value* _word)
{
	union tester
	{
		unsigned int  x;
		unsigned char isLE;
	};

	if (tester{1}.isLE)
	{
		// OPT: Cache func declaration?
		auto bswapFunc = llvm::Intrinsic::getDeclaration(_builder.GetInsertBlock()->getParent()->getParent(), llvm::Intrinsic::bswap, Type::Word);
		return _builder.CreateCall(bswapFunc, _word);
	}
	return _word;
}

}
}
}
