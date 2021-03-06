/******************************************************************************
 * Copyright (c) 2017 Philipp Schubert.
 * All rights reserved. This program and the accompanying materials are made
 * available under the terms of LICENSE.txt.
 *
 * Contributors:
 *     Philipp Schubert and others
 *****************************************************************************/

#ifndef ANALYSIS_IFDS_IDE_PROBLEMS_IFDS_LINEARCONSTANTANALYSIS_H_
#define ANALYSIS_IFDS_IDE_PROBLEMS_IFDS_LINEARCONSTANTANALYSIS_H_

#include <functional>
#include <map>
#include <phasar/PhasarLLVM/IfdsIde/DefaultIFDSTabulationProblem.h>
#include <set>
#include <string>
#include <utility>
#include <vector>

// Forward declaration of types for which we only use its pointer or ref type
namespace llvm {
class Instruction;
class Function;
class Value;
} // namespace llvm

namespace psr {
class LLVMBasedICFG;

// A small pair data type to encode data flow facts for this LCA
struct LCAPair {
  const llvm::Value *first;
  int second;
  LCAPair();
  LCAPair(const llvm::Value *V, int i);
  friend bool operator==(const LCAPair &lhs, const LCAPair &rhs);
  friend bool operator<(const LCAPair &lhs, const LCAPair &rhs);
};

} // namespace psr

// Specialize std::hash to be used in containers like std::unordered_map
namespace std {
template <> struct hash<psr::LCAPair> {
  std::size_t operator()(const psr::LCAPair &k) const;
};
} // namespace std

namespace psr {

class IFDSLinearConstantAnalysis
    : public DefaultIFDSTabulationProblem<const llvm::Instruction *, LCAPair,
                                          const llvm::Function *,
                                          LLVMBasedICFG &> {
private:
  std::vector<std::string> EntryPoints;

public:
  typedef LCAPair d_t;
  typedef const llvm::Instruction *n_t;
  typedef const llvm::Function *m_t;
  typedef LLVMBasedICFG &i_t;

  IFDSLinearConstantAnalysis(LLVMBasedICFG &icfg,
                             std::vector<std::string> EntryPoints = {"main"});

  virtual ~IFDSLinearConstantAnalysis() = default;

  std::shared_ptr<FlowFunction<d_t>> getNormalFlowFunction(n_t curr,
                                                           n_t succ) override;

  std::shared_ptr<FlowFunction<d_t>> getCallFlowFunction(n_t callStmt,
                                                         m_t destMthd) override;

  std::shared_ptr<FlowFunction<d_t>> getRetFlowFunction(n_t callSite,
                                                        m_t calleeMthd,
                                                        n_t exitStmt,
                                                        n_t retSite) override;

  std::shared_ptr<FlowFunction<d_t>> getCallToRetFlowFunction(
      n_t callSite, n_t retSite,
      std::set<IFDSLinearConstantAnalysis::m_t> callees) override;

  std::shared_ptr<FlowFunction<d_t>>
  getSummaryFlowFunction(n_t callStmt, m_t destMthd) override;

  std::map<n_t, std::set<d_t>> initialSeeds() override;

  d_t createZeroValue() override;

  bool isZeroValue(d_t d) const override;

  std::string DtoString(d_t d) const override;

  std::string NtoString(n_t n) const override;

  std::string MtoString(m_t m) const override;
};

} // namespace psr

#endif /* ANALYSIS_IFDS_IDE_PROBLEMS_IFDS_TAINT_ANALYSIS_IFDSTAINTANALYSIS_HH_ \
        */
