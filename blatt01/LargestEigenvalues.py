#!/usr/bin/env python3

import numpy as np
import math
import typing as tp

class LargestEigenvalues:
    ''' Class encapsulating methods of computing the largest Eigenvalue of any n x n Matrix.

    Methods implemented
    -------------------
    power_method(A: np.ndarray, r: np.array, sigma: tp.Callable) -> float

    State of development
    --------------------
    Assignment completed. 
    For reasons of clarity and conveyyance of ideas and methodology, code is not optimised for performance.
    '''

    # private boolean for declaring test usage, changes output
    _test_mode = False
    # setter for test (default when used True)
    def set_test_mode(self, b: bool=True) -> None:
        self._test_mode = b

    def power_method(self, A: np.ndarray, n: int) -> (float, np.array):
        ''' Apply the Power Method to approximate the largest Eigenvalue for matrix A
        
        Parameters
        ----------
        A : numpy.ndarray (m,m)     
            positive definite square np.ndarray Matrix (m x m) [i.e. all Eigenvalues > 0]
        n : integer     
            number of iterations to be performed in approximation
        
        Returns
        -------
        (sigma : float, partial_sigmas : np.array(m))
            Returns a tuple, containing:
            - [0] the resulting estimation for largest Eigenvalue sigma
            - [1] a numpy array holding all interim results for sigma in order of iteration
        '''
        ## Assertions ##

        # A is positive definite square matrix
        assert(A.shape[0] == A.shape[1])
        assert(np.all(np.linalg.eigvals(A) > 0))
        # positive number of iterations
        assert(n > 0)

        # find an initial r and transpose it [yields (n x 1) vector]
        r = self.find_initial_vector(A)
        r_tilde = np.zeros(A.shape[0])
        # reserve array for interim results and variable to store current result in
        partial_sigmas = np.zeros(n)
        sigma = 0.
        
        for i in range(1, n+1):
            '''
            Through n iterations, approximate an Eigenvector r(n), 
            which corresponds to the largest Eigenvalue of matrix A.
            Approximation gains accuracy through larger number of iterations n.
            '''
            r_tilde = A.dot(r)            # r_tilde(1) through r_tilde(n)
            r = r_tilde / self.euclidean_norm(r_tilde)       # new r(i)) for i = 1..n
            # compute new approximate eigenvalue sigma
            sigma = self.rayleigh_quotient(A, r)
            # store interim result
            partial_sigmas[i-1] = sigma
            
            # when in test setting, use test() method to print current estimation error
            if self._test_mode:
                print(f"\n\tIteration {i}:")
                self.test(A, r, sigma)

        return sigma, partial_sigmas


    def find_initial_vector(self, A: np.ndarray) -> np.array:
        ''' Determine a random initial vector r, with A*r != 0.

        Parameters
        ----------
        A: numpy.ndarray (m x m)-Matrix

        Returns
        -------
        r : numpy.array
            Array / Vector of length n with numpy.dot(A,r) does not give a zero vector.
        '''

        r = np.random.rand(A.shape[0])
        product = A.dot(r)
        while not product.any():
            r = np.random.rand(A.shape[0])
            product = A.dot(r)
        return r
    
    def rayleigh_quotient(self, A: np.ndarray, r: np.array) -> float:
        '''Compute the Rayleigh quotient for a given Matrix and current approximat Eigenvector r

        Parameters
        ----------
        A : numpy.ndarray(m,m)
            positive definite square matrix [i.e. all Eigenvalues > 0]
        r : numpy.array(m) 
            current approx. Eigenvector corresponding to A's largest Eigenvalue

        Returns
        -------
        sigma : float
            Quotient of scalarproduct of r and A*r and scalarproduct of r with itself.
            I.e. <r, A*r> / <r, r>
        '''
        ## Assertions ##

        # A is positive definite square matrix
        assert(A.shape[0] == A.shape[1])
        assert(np.all(np.linalg.eigvals(A) > 0))
        # r must be Array of size n
        assert(r.size == A.shape[0])

        # perform computation and return result
        sigma = np.dot(r, A.dot(r)) / np.dot(r,r)   # dot-product == scalar product
        return sigma

    def euclidean_norm(self, r: np.array) -> float:
        '''Compute euclidean norm for input vector

        Parameters
        ----------
        r : numpy.array   
            Vector to compute euclidean norm for.
        
        Returns
        -------
        eucliNorm : float
            Sum of squared scalars.
        '''
        eucliNorm = np.sum(np.square(r))
        return eucliNorm

    def test(self, A: np.ndarray, r: np.array, sigma: float) -> None:
        '''Method testing accuracy of current estimate (only active if bool _test_mode is set);
        Prints out current approximation error using L1, L2 and L-Infinity norms.

        Parameters
        ----------
        A : numpy.ndarray (m,m)
            Definite positive quare matrix for which to find largest Eigenvalue.
        r : numpy.array(m)
            Current hypothesis Eigenvector
        sigma : float
            Currently approximated largest Eigenvalue for A

        Returns
        -------
        None
        '''
        estimation = A.dot(r) - sigma*r
        error_L1 = self.dist_norm_L1(estimation)
        error_L2 = self.dist_norm_L2(estimation)
        error_L_inf = self.dist_norm_L_inf(estimation)
        print(f"\t\tError by L1-Norm: \t{error_L1}")
        print(f"\t\tError by L2-Norm: \t{error_L2}")
        print(f"\t\tError by L_inf-Norm: \t{error_L_inf}")   

    def dist_norm_L1(self, v: np.array) -> float:
        '''Calculate L1 distance norm

        Parameters
        ----------
        v : numpy.array
            Vector of numerical values represented by numpy array.

        Returns:
        L1_distance : float
            Sum of absolute values in input vector v.
        '''
        L1_distance = np.sum(np.abs(v))
        return L1_distance

    def dist_norm_L2(self, v: np.array) -> float:
        '''Calculate L2 distance norm

        Parameters
        ----------
        v : numpy.array
            Vector of numerical values represented by numpy array.

        Returns:
        L2_distance : float
            Square root of sum of squared values in input vector v.
        '''
        L2_distance = math.sqrt(np.sum(np.square(v)))
        return L2_distance

    def dist_norm_L_inf(self, v: np.array) -> float:
        '''Calculate L-infinity distance norm

        Parameters
        ----------
        v : numpy.array
            Vector of numerical values represented by numpy array.

        Returns:
        L_inf_distance : float
            Maximum absolute value in input vector v.
        '''
        L_inf_distance =  np.max(np.absolute(v))
        return L_inf_distance



# Test class implicitely if script run as main program
if __name__ == "__main__":
    print("\nTesting class LargestEigenvalues:\n")
    # initialize static instance
    Eigen = LargestEigenvalues()
    Eigen.set_test_mode()

    # three test matrices (two taken from assignment, one extra random case)
    A = np.random.rand(3, 3)
    while not np.all(np.linalg.eigvals(A) > 0):
        A = np.random.rand(3, 3)
    
    B = np.array(
        [
            [3, 0, 0],
            [0, 1, 0],
            [0, 0, 1]
        ])
    C = np.array(
        [
            [ 4,-1,-1],
            [.5, 2,-1],
            [ 0, 0, 1]
        ])

    print("Testing Power Method for:\n")
    print("\nMatrix A:")
    resulting_sigma_A, partial_sigmas_A = Eigen.power_method(A, 20)
    print(f"\nFinal resulting Sigma: {resulting_sigma_A}\n")
    print("\nMatrix B:")
    resulting_sigma_B, partial_sigmas_B = Eigen.power_method(B, 20)
    print(f"\nFinal resulting Sigma: {resulting_sigma_B}\n")
    print("\nMatrix C:")
    resulting_sigma_C, partial_sigmas_C = Eigen.power_method(C, 20)
    print(f"\nFinal resulting Sigma: {resulting_sigma_C}\n")