#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
using namespace llvm;

struct MyModPass : public PassInfoMixin<MyModPass> {
  Type *voidType;
  Type *int8PtrTy;

  bool isLogger(StringRef name) { return name == "traceEdgeLogger"; }

  bool isAppModule(Module &M) {
    StringRef src = M.getSourceFileName();
    return src.endswith("app.c");
  }

  bool insertTraceEdges(Module &M, Function &F, IRBuilder<> &builder) {
    ArrayRef<Type *> paramTypes = {int8PtrTy, int8PtrTy};
    FunctionType *logFuncType = FunctionType::get(voidType, paramTypes, false);
    FunctionCallee logFunc =
        M.getOrInsertFunction("traceEdgeLogger", logFuncType);

    bool Inserted = false;
    for (auto &B : F) {
      for (auto &I : B) {
        if (isa<PHINode>(&I)) {
          continue;
        }
        for (auto &U : I.operands()) {
          Instruction *OpI = dyn_cast<Instruction>(U.get());
          if (!OpI) {
            continue;
          }
          builder.SetInsertPoint(&I);
          Value *userName = builder.CreateGlobalStringPtr(I.getOpcodeName());
          Value *operandName =
              builder.CreateGlobalStringPtr(OpI->getOpcodeName());
          Value *args[] = {userName, operandName};
          builder.CreateCall(logFunc, args);
          Inserted = true;
        }
      }
    }
    return Inserted;
  }

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    outs() << "[Module] " << M.getName() << '\n';

    if (!isAppModule(M)) {
      outs() << "[Skip] not app.c (" << M.getSourceFileName() << ")\n";
      return PreservedAnalyses::all();
    }

    LLVMContext &Ctx = M.getContext();
    IRBuilder<> builder(Ctx);
    voidType = Type::getVoidTy(Ctx);
    int8PtrTy = Type::getInt8Ty(Ctx)->getPointerTo();

    for (auto &F : M) {
      outs() << "[Function] " << F.getName() << " (arg_size: " << F.arg_size()
             << ")\n";
      if (isLogger(F.getName()) || F.isDeclaration()) {
        continue;
      }

      if (insertTraceEdges(M, F, builder)) {
        outs() << "insertTraceEdges done\n";
      }

      bool verif = verifyFunction(F, &outs());
      outs() << "[VERIFICATION] " << (verif ? "FAIL\n\n" : "OK\n\n");
    }
    outs() << '\n';
    return PreservedAnalyses::none();
  };
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerOptimizerLastEPCallback([](ModulePassManager &MPM, auto) {
      MPM.addPass(MyModPass{});
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "TracePass", "0.0.1", callback};
};

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
