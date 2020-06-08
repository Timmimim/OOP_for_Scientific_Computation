#include <iostream>
#include "../blatt03/matrix.h"
#include "matrix_iterator.h"

int main(){
  Matrix m(3,3);

  for(auto [row_idx, cols] : rows(m)){
    for(auto [col_idx, value] : cols){
      std::cout << row_idx << " " << col_idx << ": " << value << std::endl;
    }
  }
}
