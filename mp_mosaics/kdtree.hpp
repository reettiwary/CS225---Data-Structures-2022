/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    //setting condiitonals to return 
     if(curDim > (Dim - 1) || curDim < 0){
       return false;
     }

     if(first[curDim] > second[curDim]){
       return false;
     }

     if(first[curDim] < second[curDim]){
       return true;
     }

    //return false;

    return(second > first);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    double currdistance = distance(currentBest, target);

    double distance_sub = distance(potential, target);

    if(currdistance > distance_sub){
      return true;
    }

    if(currdistance < distance_sub){
      return false;
    }

     //return false;

     return (currentBest > potential);
}

//function added 
template <int Dim>

double KDTree<Dim>::distance(const Point<Dim> &firstpoint, const Point<Dim> &secondpoint) const{

  double distance = 0;

  for(unsigned x = 0; x < Dim; x++){

    unsigned a = (firstpoint[x] - secondpoint[x]);

    unsigned b = (firstpoint[x] - secondpoint[x]);

    distance += (a * b);
  }

  return distance; //in a sense we see that distance is being returned to the current values used

}

//newtree
template <int Dim>

typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::newtree(vector<Point<Dim>> &list, int components, unsigned left, unsigned right){

  size = 0;

  if(list.empty() || right < left || right<0 || left<0 || right>=list.size() || left>=list.size()){
    return NULL;
  }

  unsigned mid = (right + left)/2 ; 

  unsigned j = components % Dim;

  KDTreeNode * subr = new KDTreeNode(quickselect(list, j, left, right, mid));

  components++;

  size++;

  unsigned d = mid + 1; //I am storing it in random variables so there is no mixup with which ever value may be passed or stored 
  unsigned e = mid - 1; 

  unsigned constv = components % Dim;
  unsigned constz = components % Dim;

  subr->right = newtree(list, constv, d, right);
  subr->left = newtree(list, constz, left, e);

  return subr;

}

//quickselect

template <int Dim>

Point<Dim> KDTree<Dim>::quickselect(vector<Point<Dim>> &list, int components, unsigned left, unsigned right, unsigned var){

  if(left == right){

    return list[left];
  }

  unsigned indvar = partition(list, components, left, right, var);

  if(var == indvar){

    return list[var];
  }

  else if(var < indvar){

    unsigned v = indvar - 1;
    return quickselect(list, components, left, v, var);
  }

  else{

    unsigned b = indvar + 1;
    return quickselect(list, components, b, right, var);
  }

}

//partition

template <int Dim>

unsigned KDTree<Dim>::partition(vector<Point<Dim>> &list, int components, unsigned left, unsigned right, unsigned indexvar){

  Point<Dim> indexval = list[indexvar];

  swap(list[indexvar], list[right]);

  unsigned constIndex = left;

  for(unsigned x = left; x < right; x++){

    if(smallerDimVal(list[x], indexval, components)){

      swap(list[constIndex], list[x]);

      constIndex++;
    }
  }

  swap(list[right], list[constIndex]);
  
  return constIndex;
}

//swap

template <int Dim>

void KDTree<Dim>::swap(Point<Dim> &firstpoint, Point<Dim> &secondpoint){

  Point<Dim> var1 = firstpoint;

  firstpoint = secondpoint;

  secondpoint = var1;
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    vector<Point<Dim>> listcopy1;

    listcopy1.assign(newPoints.begin(), newPoints.end());

    unsigned zer = 0; 

    unsigned sir = (listcopy1).size()-1;

    root = newtree(listcopy1, 0, zer, sir);
}

//copy

template <int Dim>
void KDTree<Dim>::copy(KDTree<Dim> *sub1, KDTree<Dim> *sub2){

  if(sub2 != NULL){
    sub1 = new KDTreeNode();

    sub1->point = sub2->point;

    copy(sub1->right, sub2->right);

    copy(sub1->left, sub2->left);
  }

  else{
    sub1 = NULL;
  }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */

   copy(this->root, other.root);

   size = other.size;
}

//clear

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode *& node){

  if(node != NULL){

    clear(node->right);

    clear(node->left);

    delete node;
  }
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

   clear(this->root);

   copy(this->root, rhs.root);

   size = rhs.size;

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */

   clear(this->root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> &query, KDTreeNode *node, int components) const{

  if( ((node->right) == NULL) && ((node->left) == NULL)){

    return node->point;
  }

  Point<Dim> close1 = node->point;

  Point<Dim> close2 = close1;

  bool left1 = smallerDimVal(query, close1, components);

    if(left1 && node->left != NULL){

    unsigned int k = (components+1)%Dim;

    close2 = findNearestNeighbor(query, node->left, k);
  }

    else if(!left1 && node->right != NULL){
    unsigned int p = (components+1)%Dim;

    close2 = findNearestNeighbor(query, node->right, p);
  }

  if(shouldReplace(query, close1, close2)){

    close1 = close2;
  }

  double r = distance(query, close2);

  double subtr = (query[components] - node->point[components]);

  double subtr2 = (query[components] - node->point[components]);

  double componentsr = (subtr * subtr2);

  if(componentsr <= r){

      if(!left1 && node->left != NULL){

      unsigned int f = (components+1)%Dim;

      close2 = findNearestNeighbor(query, node->left, f);

      if(shouldReplace(query, close1, close2)){

        close1 = close2;
      }

      }
      
      else if(left1 && node->right != NULL){

        unsigned int g = (components+1)%Dim;

        close2 = findNearestNeighbor(query, node->right, g);

        if(shouldReplace(query, close1, close2)){

          close1 = close2;
        }
      }
    }

    return close1;
  }
  

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return findNearestNeighbor(query, root, 0);

    //return Point<Dim>();
}

