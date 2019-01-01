#include "ssp.h"
using namespace mdp_planner;

SSP::SSP(MDP_Net::Ptr& pNet) {
  initTransMatrix(pNet);
};

SSP::~SSP() {
};

void SSP::initTransMatrix(MDP_Net::Ptr& pNet) {
  std::cout<<"Im here in initTransmatrix"<<std::endl;
  transMatrix.resize(pNet->n_rows * pNet->n_cols, pNet->n_rows * pNet->n_cols);
  for (int i = 0; i < pNet->mdp_states.size(); ++i) {
    mdp_state_t *state = pNet->mdp_states[i];
    int flag = 0;
    double obst_prob = 0.000001;
    //fillTransMatrix(transMatrix, state->id, pNet->n_cols, state->post_probs);
    /*
    if(state->type == OBSTACLE){
        int state_id = state->id, cols = pNet->n_cols;
        for (uint k = ZERO; k < NUM_ACTIONS; ++k) {
            if (k == ZERO) {
              transMatrix.coeffRef(state_id, state_id) = 1-(8*obst_prob);
                     //cout<<"mark1ZERO"<<endl;
            } else if (k == NORTH) {
              transMatrix.coeffRef(state_id, state_id + cols) = obst_prob;
                      //cout<<"mark1North"<<endl;
            } else if (k == NE) {
              transMatrix.coeffRef(state_id, state_id + cols + 1) = obst_prob;
                      //cout<<"mark1NE"<<endl;
            } else if (k == EAST) {
              transMatrix.coeffRef(state_id, state_id + 1) = obst_prob;
                      //cout<<"EASTmark1"<<endl;
            } else if (k == SE) {
              transMatrix.coeffRef(state_id, state_id - cols + 1) = obst_prob;
                      //cout<<"SEmark1"<<endl;
            } else if (k == SOUTH) {
              transMatrix.coeffRef(state_id, state_id - cols) = obst_prob;
                      //cout<<"SOUTHmark1"<<endl;
            } else if (k == SW) {
              transMatrix.coeffRef(state_id, state_id - cols - 1) = obst_prob;
                      //cout<<"SWmark1"<<endl;
            } else if (k == WEST) {
              transMatrix.coeffRef(state_id, state_id - 1) = obst_prob;
                      //cout<<"WESTmark1"<<endl;
            } else if (k == NW) {
              transMatrix.coeffRef(state_id, state_id + cols - 1) = obst_prob;
                      //cout<<"NWmark1"<<endl;
            }
        flag = 1;
      }
    }
    */
    if(flag == 0){
      //std::cout<<"Im here in fill matrix"<<std::endl;
        fillTransMatrix(pNet,transMatrix, state->id, pNet->n_cols, state->probs,i);
    }

  }

}
//
//probs: ZERO, N, NE, E, SE, S, SW, W, NW

void SSP::fillTransMatrix( MDP_Net::Ptr& pNet,SpMat& matrix, const int &state_id, const int &cols, const vector<double>& probs,int oo) {
  double obst_prob = 0.000001;
int num = 1;
double prob_sum = 0.001;
int flag = 0;
for (uint i = ZERO; i < NUM_ACTIONS; ++i) {
  //if (probs[i] != 0) {
    if (i == ZERO) {
      matrix.coeffRef(state_id, state_id) = probs[i];
      //num = num + 1;
      //        cout<<"mark1ZERO"<<endl;
    } else if (i == NORTH) {
      for(uint obs_num_id = 0; obs_num_id < pNet->mdp_obstacle_ids.size(); obs_num_id++)
      {
        if(state_id + cols == pNet->mdp_obstacle_ids[obs_num_id])
        {
          //matrix.coeffRef(state_id, state_id) = probs[i]*num;
          //num = num + 1;
          flag = 1;
        }
      }
      if(flag ==0)
      {
        if(state_id+cols>pNet->n_rows * pNet->n_cols || state_id+cols==pNet->n_rows * pNet->n_cols)
        {
          //matrix.coeffRef(state_id, state_id) = probs[i]*num;
          //num = num + 1;
          continue;
        }
        else
          {matrix.coeffRef(state_id, state_id + cols) = probs[i];
          prob_sum+=probs[i];}
      }
      flag = 0;
      //if (std::find(pNet->mdp_obstacle_ids.begin(), pNet->mdp_obstacle_ids.end(), state_id + cols) != pNet->mdp_obstacle_ids.end()) {matrix.coeffRef(state_id, state_id + cols) = obst_prob;}
      //        cout<<"mark1North"<<endl;
    } else if (i == NE) {
      for(uint obs_num_id = 0; obs_num_id < pNet->mdp_obstacle_ids.size(); obs_num_id++)
      {
        if(state_id + cols+1 == pNet->mdp_obstacle_ids[obs_num_id])
        {
          //matrix.coeffRef(state_id, state_id) = probs[i]*num;
          //num = num + 1;
          flag = 1;
        }
      }
      if(flag == 0)
      {
      if(state_id+cols+1>pNet->n_rows * pNet->n_cols || state_id+cols+1==pNet->n_rows * pNet->n_cols)
      {
        //matrix.coeffRef(state_id, state_id) = probs[i]*num;
        //num = num + 1;
        continue;
      }
      else
      {matrix.coeffRef(state_id, state_id + cols + 1) = probs[i];
      prob_sum+=probs[i];}
    }
    flag = 0;
      //if (std::find(pNet->mdp_obstacle_ids.begin(), pNet->mdp_obstacle_ids.end(), state_id + cols + 1) != pNet->mdp_obstacle_ids.end()) {matrix.coeffRef(state_id, state_id + cols + 1) = obst_prob;}
      //        cout<<"mark1NE"<<endl;
    }
     else if (i == EAST) {
       for(uint obs_num_id = 0; obs_num_id < pNet->mdp_obstacle_ids.size(); obs_num_id++)
       {
         if(state_id + 1 == pNet->mdp_obstacle_ids[obs_num_id])
         {
           //matrix.coeffRef(state_id, state_id) = probs[i]*num;
           //num = num + 1;
           flag = 1;
         }
       }
       if(flag == 0)
       {
      if(state_id+1>pNet->n_rows * pNet->n_cols || state_id+1==pNet->n_rows * pNet->n_cols)
      {
        //matrix.coeffRef(state_id, state_id) = probs[i]*num;
        //num = num + 1;
        continue;
      }
      else
      {matrix.coeffRef(state_id, state_id + 1) = probs[i];
      prob_sum+=probs[i];}
    }
    flag = 0;
      //if (std::find(pNet->mdp_obstacle_ids.begin(), pNet->mdp_obstacle_ids.end(), state_id + 1) != pNet->mdp_obstacle_ids.end()) {matrix.coeffRef(state_id, state_id + 1) = obst_prob;}
      //        cout<<"EASTmark1"<<endl;
    } else if (i == SE) {
      //std::cout<<"Im at fourth"<<std::endl;
      //std::cout<<"stateid "<<state_id<<std::endl;
      //std::cout<<"cols "<<cols<<std::endl;
      for(uint obs_num_id = 0; obs_num_id < pNet->mdp_obstacle_ids.size(); obs_num_id++)
      {
        if(state_id -cols+1 == pNet->mdp_obstacle_ids[obs_num_id])
        {
          //matrix.coeffRef(state_id, state_id) = probs[i]*num;
          //num = num + 1;
          flag = 1;
        }
      }
      if(flag == 0)
      {
      if(state_id-cols+1<0)
      {
          //matrix.coeffRef(state_id, state_id) = probs[i]*num;
          //num = num + 1;
          continue;
      }
      else{
      matrix.coeffRef(state_id, state_id - cols + 1) = probs[i];
      prob_sum+=probs[i];}
    }
    flag = 0;
      //if (std::find(pNet->mdp_obstacle_ids.begin(), pNet->mdp_obstacle_ids.end(), state_id - cols + 1) != pNet->mdp_obstacle_ids.end()) {matrix.coeffRef(state_id, state_id - cols + 1) = obst_prob;}
      //        cout<<"SEmark1"<<endl;
    } else if (i == SOUTH) {
      for(uint obs_num_id = 0; obs_num_id < pNet->mdp_obstacle_ids.size(); obs_num_id++)
      {
        if(state_id -cols == pNet->mdp_obstacle_ids[obs_num_id])
        {
          //matrix.coeffRef(state_id, state_id) = probs[i]*num;
          //num = num + 1;
          flag = 1;
        }
      }
      if(flag == 0)
      {
      if(state_id-cols<0)
      {
          //matrix.coeffRef(state_id, state_id) = probs[i]*num;
          //num = num + 1;
          continue;
      }
      else{
      matrix.coeffRef(state_id, state_id - cols) = probs[i];
    prob_sum+=probs[i];}
    }
    flag = 0;
      //if (std::find(pNet->mdp_obstacle_ids.begin(), pNet->mdp_obstacle_ids.end(), state_id - cols) != pNet->mdp_obstacle_ids.end()) {matrix.coeffRef(state_id, state_id - cols) = obst_prob;}
      //        cout<<"SOUTHmark1"<<endl;
    } else if (i == SW) {
      for(uint obs_num_id = 0; obs_num_id < pNet->mdp_obstacle_ids.size(); obs_num_id++)
      {
        if(state_id -cols-1 == pNet->mdp_obstacle_ids[obs_num_id])
        {
          //matrix.coeffRef(state_id, state_id) = probs[i]*num;
          //num = num + 1;
          flag = 1;
        }
      }
      if(flag == 0)
      {
      if(state_id-cols-1<0)
      {
          //matrix.coeffRef(state_id, state_id) = probs[i]*num;
          //num = num + 1;
          continue;
      }
      else{
      matrix.coeffRef(state_id, state_id - cols - 1) = probs[i];
    prob_sum+=probs[i];}
    }
    flag = 0;
      //if (std::find(pNet->mdp_obstacle_ids.begin(), pNet->mdp_obstacle_ids.end(), state_id - cols - 1) != pNet->mdp_obstacle_ids.end()) {matrix.coeffRef(state_id, state_id - cols - 1) = obst_prob;}
      //        cout<<"SWmark1"<<endl;
    } else if (i == WEST) {
      for(uint obs_num_id = 0; obs_num_id < pNet->mdp_obstacle_ids.size(); obs_num_id++)
      {
        if(state_id -cols+1 == pNet->mdp_obstacle_ids[obs_num_id])
        {
          //matrix.coeffRef(state_id, state_id) = probs[i]*num;
          //num = num + 1;
          flag = 1;
        }
      }
      if(flag ==0)
      {
      if(state_id-1<0)
      {
          //matrix.coeffRef(state_id, state_id) = probs[i]* num;
          //num = num + 1;
          continue;
      }
      else{
      matrix.coeffRef(state_id, state_id - 1) = probs[i];
    prob_sum+=probs[i];}
    }
    flag = 0;
      //if (std::find(pNet->mdp_obstacle_ids.begin(), pNet->mdp_obstacle_ids.end(), state_id - 1) != pNet->mdp_obstacle_ids.end()) {matrix.coeffRef(state_id, state_id - 1) = obst_prob;}
      //        cout<<"WESTmark1"<<endl;
    } else if (i == NW) {
      for(uint obs_num_id = 0; obs_num_id < pNet->mdp_obstacle_ids.size(); obs_num_id++)
      {
        if(state_id -cols+1 == pNet->mdp_obstacle_ids[obs_num_id])
        {
          //matrix.coeffRef(state_id, state_id) = probs[i]*num;
          //num = num + 1;
          flag = 1;
        }
      }
      if(flag == 0)
      {
      if(state_id+cols-1>pNet->n_rows * pNet->n_cols || state_id+cols-1==pNet->n_rows * pNet->n_cols)
      {
          //matrix.coeffRef(state_id, state_id) = probs[i]*num;
          //num = num + 1;
          continue;
      }
      else{
      matrix.coeffRef(state_id, state_id + cols - 1) = probs[i];
    prob_sum+=probs[i];}
    }
    flag = 0;
      //if (std::find(pNet->mdp_obstacle_ids.begin(), pNet->mdp_obstacle_ids.end(), state_id + cols - 1) != pNet->mdp_obstacle_ids.end()) {matrix.coeffRef(state_id, state_id + cols - 1) = obst_prob;}
      //        cout<<"NWmark1"<<endl;
    }
//  }
}
matrix.coeffRef(state_id, state_id) = std::abs(1-prob_sum);
}

void removeRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove) {
  unsigned int numRows = matrix.rows() - 1;
  unsigned int numCols = matrix.cols();

  if (rowToRemove < numRows)
    matrix.block(rowToRemove, 0, numRows - rowToRemove, numCols) = matrix.block(rowToRemove + 1, 0, numRows - rowToRemove, numCols);

  matrix.conservativeResize(numRows, numCols);
}

void removeColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove) {
  unsigned int numRows = matrix.rows();
  unsigned int numCols = matrix.cols() - 1;

  if (colToRemove < numCols)
    matrix.block(0, colToRemove, numRows, numCols - colToRemove) = matrix.block(0, colToRemove + 1, numRows, numCols - colToRemove);

  matrix.conservativeResize(numRows, numCols);
}

//bool SSP::pairCompare(const std::pair<int, double>& firstElem, const std::pair<int, double>& secondElem) {
//  return firstElem.second < secondElem.second;

//}

void SSP::MFPT(MDP_Net::Ptr& pNet, int id)
{
  reachability = new double[pNet->n_rows*pNet->n_cols];
  int n = transMatrix.rows();
  //std::cout << "N: " << n << std::endl;
  Eigen::MatrixXd I(n - 1, n - 1);
  I.setIdentity();
  Eigen::SparseMatrix<double> full_A = transMatrix;

  //  std::cout << "full_A " << full_A;

  Eigen::VectorXd b = -Eigen::VectorXd::Ones(n - 1);
  //  std::cout << "b " << std::endl;
  //  std::cout << b << std::endl;

  // solve Ax = b
  //  Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>> solver;
  Eigen::SimplicialLDLT<Eigen::MatrixXd> solver;

  vector<double> mu_s(n, -1);

  // meanFirstPassageTime to state i
  int i = id;
    Eigen::MatrixXd temp_A = full_A;


    removeColumn(temp_A, i);
    removeRow(temp_A, i);
  //  removeColumn(full_A, i);
  //  removeRow(full_A, i);
    temp_A = temp_A - I;
    //full_A = full_A - I;

    Eigen::MatrixXd A = temp_A;
    //Eigen::MatrixXd A = full_A;


    Eigen::VectorXd x = A.partialPivLu().solve(b);
    std::cout<<"Im here in MFPT"<<std::endl;

    for (int j = pNet -> n_rows - 1; j >= 0; j--) {
      for (int k = 0; k < pNet -> n_cols; k++) {
        int index = j * pNet -> n_cols + k;
        if (index == i) {
          reachability[index] = 0;
          //std::cout << "0 ";
        } else if (index < i) {
          reachability[index] = fabs(x[j * pNet -> n_cols + k]);
          //if(fabs(x[j * pNet -> n_cols + k]) < 600) std::cout << fabs(x[j * pNet -> n_cols + k]) << " "; else std::cout << "600 ";

        } else {
          reachability[index] = fabs(x[j * pNet -> n_cols + k - 1]);
        }
        //std::cout<< reachability[index]<<" ";
      }
      //std::cout << ";" << std::endl;
      //std::cout<<std::endl;
    }

}

void SSP::MFPT_obstacle(MDP_Net::Ptr& pNet)
{
  std::sort(pNet->mdp_obstacle_ids.begin(),pNet->mdp_obstacle_ids.end());
  std::cout<<"Im here in mfpd_obstacle"<<std::endl;
  reachability = new double[pNet->n_rows*pNet->n_cols];
  int n = transMatrix.rows();
  //std::sort(ids.begin(),ids.end());
  //for(int i=0;i<pNet->mdp_obstacle_ids.size();i++)
  //{
  //  std::cout<<"Obstacle_id "<<pNet->mdp_obstacle_ids[i]<<std::endl;
  //}
  //std::cout << "N: " << n << std::endl;
  Eigen::MatrixXd I(n - pNet->mdp_obstacle_ids.size(), n - pNet->mdp_obstacle_ids.size());
  I.setIdentity();
  Eigen::SparseMatrix<double> full_A = transMatrix;

  //  std::cout << "full_A " << full_A;

  Eigen::VectorXd b = -Eigen::VectorXd::Ones(n - pNet->mdp_obstacle_ids.size());
  //  std::cout << "b " << std::endl;
  //  std::cout << b << std::endl;

  // solve Ax = b
  //  Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>> solver;
  Eigen::SimplicialLDLT<Eigen::MatrixXd> solver;

  vector<double> mu_s(n, -1);

  // meanFirstPassageTime to state i
  //int i = id;
    Eigen::MatrixXd temp_A = full_A;

  for(int i=0;i<pNet->mdp_obstacle_ids.size();i++)
  {
    removeColumn(temp_A, pNet->mdp_obstacle_ids[i]-i);
    removeRow(temp_A, pNet->mdp_obstacle_ids[i]-i);
  }
    temp_A = temp_A - I;

    Eigen::MatrixXd A = temp_A;;

    Eigen::VectorXd x = A.partialPivLu().solve(b);
    std::cout<<"Im here in MFPT"<<x.size()<<std::endl;
    double max_value = -INF;
    double min_value = INF;
    double curr_value;
    for(int i=0;i<x.size();i++)
    {
      curr_value = x[i];
      if(curr_value > max_value)
      {
        max_value = curr_value;
      }
    }
    std::cout<<"Max x "<<max_value<<std::endl;

    for (int j = pNet -> n_rows - 1; j >= 0; j--) {
      for (int k = 0; k < pNet -> n_cols; k++) {
        //std::cout<<"iteration "<<k<<std::endl;
        int index = j * pNet -> n_cols + k;
        int index_obs_num;
        for(int kk=0;kk<pNet->mdp_obstacle_ids.size();kk++)
        {
            if(index<pNet->mdp_obstacle_ids[kk] || index==pNet->mdp_obstacle_ids[kk])
            {
              index_obs_num = kk;
              break;
            }
            index_obs_num = kk;
        }
        //std::cout<<"iteration "<<index_obs_num<<std::endl;
        //std::cout<<"iteration index "<<index<<std::endl;
        if (index == pNet->mdp_obstacle_ids[index_obs_num]) {
          reachability[index] = 0;
          //std::cout << "0 ";
        } else if (index < pNet->mdp_obstacle_ids[index_obs_num]) {
          reachability[index] = fabs(x[j * pNet -> n_cols + k - index_obs_num])/max_value;
          //std::cout<<"reachability index "<<j * pNet -> n_cols + k-index_obs_num<<std::endl;
          //if(fabs(x[j * pNet -> n_cols + k]) < 600) std::cout << fabs(x[j * pNet -> n_cols + k]) << " "; else std::cout << "600 ";

        } else {
          reachability[index] = fabs(x[j * pNet -> n_cols + k - index_obs_num-1])/max_value;
          //std::cout<<"reachability index "<<j * pNet -> n_cols + k - index_obs_num<<std::endl;
        }
        //std::cout<< reachability[index]<<" ";


      }
      //std::cout << ";" << std::endl;
      //std::cout<<std::endl;
    }
}
