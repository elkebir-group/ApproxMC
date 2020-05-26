/*
 * cuttingplane.h
 *
 */

#ifndef CUTTINGPLANE_H
#define CUTTINGPLANE_H

#include "approxmcconfig.h"
#include <fstream>
#include <random>
#include <map>
#include <cstdint>
#include <cryptominisat5/cryptominisat.h>

using namespace CMSat;

/// This class provides a cutting plane wrapper for ApproxMC
class CuttingPlane
{
public:

  /// Constructor
  CuttingPlane(SATSolver* solver): _solver(solver) {}

  virtual ~CuttingPlane() {}

  /// Identify violated constraints
  virtual int separate() = 0;

  int getNumClausesAdded() const {
    return _numClausesAdded;
  }
  
protected:
  
  /// Get current assignment from solver and input
  lbool getAssignment(int var) {
    return _solver->get_model()[var]; // see if this is const
  }

  void addClause(const std::vector<Lit>& clause) {
    _solver->add_clause(clause);
    _numClausesAdded++;
//    std::cerr << clause << " 0" << std::endl;
  }
  
//  void sortClause(std::vector<Lit>& clause) {
//    std::sort(clause.begin(), clause.end(), [](Lit a, Lit b){
//      int delta = a.var() - b.var();
//      if (delta < 0) {
//        return true;
//      }
//      else if (delta > 0) {
//        return false;
//      }
//      else if (a.sign()) {
//        return false;
//      }
//      else {
//        return true;
//      }
//    });
//  }

private:
  SATSolver* _solver;
  int _numClausesAdded;
};

#endif
