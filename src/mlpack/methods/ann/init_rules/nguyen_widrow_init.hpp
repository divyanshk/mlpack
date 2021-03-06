/**
 * @file nguyen_widrow_init.hpp
 * @author Marcus Edel
 *
 * Definition and implementation of the Nguyen-Widrow method. This
 * initialization rule initialize the weights so that the active regions of the
 * neurons are approximately evenly distributed over the input space.
 *
 * For more information, see the following paper.
 *
 * @code
 * @inproceedings{NguyenIJCNN1990,
 *   title={Improving the learning speed of 2-layer neural networks by choosing
 *   initial values of the adaptive weights},
 *   booktitle={Neural Networks, 1990., 1990 IJCNN International Joint
 *   Conference on},
 *   year={1990}
 * }
 * @endcode
 */
#ifndef __MLPACK_METHOS_ANN_INIT_RULES_NGUYEN_WIDROW_INIT_HPP
#define __MLPACK_METHOS_ANN_INIT_RULES_NGUYEN_WIDROW_INIT_HPP

#include <mlpack/core.hpp>

#include "random_init.hpp"

namespace mlpack {
namespace ann /** Artificial Neural Network. */ {

/**
 * This class is used to initialize the weight matrix with the Nguyen-Widrow
 * method. The method is defined by
 *
 * @f[
 * \gamma \le w_i \le \gamma \\
 * \beta &=& 0.7H^{\frac{1}{I}} \\
 * n &=& \sqrt{\sum_{i=0}{I}w_{i}^{2}} \\
 * w_i &=& \frac{\beta w_i}{n}
 * @f]
 *
 * Where H is the number of neurons in the outgoing layer, I represents the
 * number of neurons in the ingoing layer and gamma defines the random interval
 * that is used to initialize the weights with a random value in a specific
 * range.
 *
 * @tparam MatType Type of matrix (should be arma::mat or arma::spmat).
 */
template<typename MatType = arma::mat>
class NguyenWidrowInitialization
{
 public:
  /**
   * Initialize the random initialization rule with the given lower bound and
   * upper bound.
   *
   * @param lowerBound The number used as lower bound.
   * @param upperBound The number used as upper bound.
   */
  NguyenWidrowInitialization(const double lowerBound = -0.5,
                             const double upperBound = 0.5) :
      lowerBound(lowerBound), upperBound(upperBound) { }

  /**
   * Initialize the elements of the specified weight matrix with the
   * Nguyen-Widrow method.
   *
   * @param W Weight matrix to initialize.
   * @param n_rows Number of rows.
   * @return n_cols Number of columns.
   */
  void Initialize(MatType& W, const size_t n_rows, const size_t n_cols)
  {
    RandomInitialization<MatType> randomInit(lowerBound, upperBound);
    randomInit.Initialize(W, n_rows, n_cols);

    double beta = 0.7 * std::pow(n_cols, 1 / n_rows);
    W *= (beta / arma::norm(W));
  }

 private:
  //! The number used as lower bound.
  const double lowerBound;

  //! The number used as upper bound.
  const double upperBound;
}; // class NguyenWidrowInitialization


}; // namespace ann
}; // namespace mlpack

#endif
