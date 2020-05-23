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
  , _solver()
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
        assert(_var2B.size() == _nrActiveVariables);
      }
    }
  }
  _cuttingPlane = new CuttingPlaneDollo(approxmc->solver, _B, _m, _n, _k, _B2Var, _activeEntries, _solA);
  approxmc->setCuttingPlane(_cuttingPlane);
}

int SolverDollo::solve() {
  return _approxmc->solve();
}