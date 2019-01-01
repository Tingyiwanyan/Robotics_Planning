#ifndef SSP_H
#define SSP_H

#include <queue>
#include <map>
#include <Eigen/Sparse>
#include "methods.h"

using namespace std;


namespace mdp_planner {

  class SSP {
  public:
    typedef Eigen::SparseMatrix<double> SpMat;
    //	typedef Eigen::SparseVector<double> SpVec;

    //typedef boost::shared_ptr<SSP> Ptr;
    //typedef boost::shared_ptr<const SSP> ConstPtr;
    int loopind;

    SSP(MDP_Net::Ptr&);
    virtual ~SSP();

    //accessors
    //virtual void loadParams(void){};

    // track the state and concatinate them to get a sequence of states
    // such "future path" is in the expected sense, can be "misleading" though

    void fillTransMatrix(MDP_Net::Ptr& pNet,SpMat& matrix, const int &state_id, const int &cols, const vector<double>& probs,int oo);
    void MFPT(MDP_Net::Ptr& pNet, int id);
    void MFPT_obstacle(MDP_Net::Ptr& pNet);
    // fill in the global transition probability (size: grids * grids)
    void initTransMatrix(MDP_Net::Ptr& pNet);

  //private:
    // n-step transition probability matrix p_ij(k)
    vector<Eigen::SparseMatrix<double> > transMatrixs;
    // transition probability matrix p_ij(k) at each step
    Eigen::SparseMatrix<double> transMatrix;
    // state distribution
    double *reachability;
  };

}


#endif
