//===- SymbolTable.h ------------------------------------------------------===//
//
//                             The LLVM Linker
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLD_COFF_SYMBOL_TABLE_H
#define LLD_COFF_SYMBOL_TABLE_H

#include "Reader.h"
#include "llvm/Support/Allocator.h"

namespace lld {
namespace coff {

class SymbolTable {
public:
  SymbolTable();

  std::error_code addFile(std::unique_ptr<InputFile> File);
  bool reportRemainingUndefines();

  std::vector<std::unique_ptr<ObjectFile>> &getFiles() {
    return ObjectFiles;
  }

  uint64_t getRVA(StringRef Symbol);
  void dump();

  std::vector<std::unique_ptr<ImplibFile>> ImplibFiles;

private:
  std::error_code addFile(ObjectFile *File);
  std::error_code addFile(ArchiveFile *File);
  std::error_code addFile(ImplibFile *File);

  std::error_code resolve(Symbol *Sym);
  std::error_code addMemberFile(CanBeDefined *Sym);

  std::vector<std::unique_ptr<ObjectFile>> ObjectFiles;
  std::vector<std::unique_ptr<ArchiveFile>> ArchiveFiles;
  std::map<llvm::StringRef, SymbolRef *> Symtab;

  void addInitialSymbol(Symbol *Sym);

  std::vector<std::unique_ptr<Symbol>> Symbols;
  llvm::BumpPtrAllocator Alloc;
};

} // namespace pecoff
} // namespace lld

#endif