#include "solverdollo.h"


SolverDollo::SolverDollo(const Matrix& B, int k, AppMC* approxmc)
  : _B(B)
  , _m(B.getNrClones())
  , _n(B.getNrMutations())
  , _k(k)
  , _B2Var()
  , _var2B()
  , _activeEntries()
  , _nrActiveVariables(0)
  , _nrConstraints(0)
  , _solA(_B.getNrClones(), _B.getNrMutations())
  , _approxmc(approxmc)
{
}

void SolverDollo::init() {
  
  /// Resize containers for each clone
  _activeEntries.resize(_m);
  _B2Var.resize(_m);
  for (int p = 0; p < _m; p++)
  {
    /// Resize container for each mutation
    _activeEntries[p].resize(_n);
    _B2Var[p].resize(_n);
    for (int c = 0; c < _n; ++c)
    {
      _activeEntries[p][c] = false;
      
      /// Check if this entry is elligible for being active
      if (_B.getEntry(p, c)==0){
        
        /// Note that is it active and generate variables
        _activeEntries[p][c] = true;
        _B2Var[p][c] = _nrActiveVariables;
        _var2B.push_back(Triple(p, c, 2));
        _nrActiveVariables = _nrActiveVariables+1;
        assert(_var2B.size() == (size_t)_nrActiveVariables);
      }
    }
  }
  _cuttingPlane = new CuttingPlaneDollo(_approxmc->solver, _B, _m, _n, _k, _B2Var, _activeEntries, _solA);
  _approxmc->setCuttingPlane(_cuttingPlane);
}

int SolverDollo::solve(AppMCConfig _conf) {
  /// Create variables
  _approxmc->solver->new_vars(_nrActiveVariables);
  
  /// Update sampling set
  for (int i = 0; i < _nrActiveVariables; ++i)
  {
    _conf.sampling_set.push_back(i);
  }

  int num_solutions = _approxmc->solve(_conf);
  if (num_solutions > 0) {
    processSolution();
  }

  return num_solutions;
}

/// Get current assignment from solver and input
lbool SolverDollo::getAssignment(int var) {
  return _approxmc->solver->get_model()[var]; // see if this is const
}

int SolverDollo::getEntryAssignment(int p, int c){
  
  if (!_activeEntries[p][c]){
    return _B.getEntry(p, c);
  }
  
  int var = _B2Var[p][c];

  if (getAssignment(var) == l_True) {
    return 2;
  }
  
  if (getAssignment(var) == l_False) {
    return 0;
  }

  throw std::runtime_error("Error: Solver did not assign truth value to variable.");
}

void SolverDollo::processSolution() {
  for (int p = 0; p < _m; p++){
    for (int c = 0; c < _n; ++c){
      _solA.setEntry(p, c, getEntryAssignment(p, c));
    }
  }
}
