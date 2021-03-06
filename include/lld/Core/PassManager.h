//===- lld/Core/PassManager.h - Manage linker passes ----------------------===//
//
//                             The LLVM Linker
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLD_CORE_PASS_MANAGER_H
#define LLD_CORE_PASS_MANAGER_H

#include "lld/Core/LLVM.h"
#include "lld/Core/Pass.h"
#include <memory>
#include <vector>

namespace lld {
class SimpleFile;
class Pass;

/// \brief Owns and runs a collection of passes.
///
/// This class is currently just a container for passes and a way to run them.
///
/// In the future this should handle timing pass runs, running parallel passes,
/// and validate/satisfy pass dependencies.
class PassManager {
public:
  void add(std::unique_ptr<Pass> pass) {
    _passes.push_back(std::move(pass));
  }

  std::error_code runOnFile(std::unique_ptr<SimpleFile> &file) {
    for (std::unique_ptr<Pass> &pass : _passes)
      pass->perform(file);
    return std::error_code();
  }

private:
  /// \brief Passes in the order they should run.
  std::vector<std::unique_ptr<Pass>> _passes;
};
} // end namespace lld

#endif
