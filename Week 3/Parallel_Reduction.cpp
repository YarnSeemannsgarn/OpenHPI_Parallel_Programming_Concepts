/*
Implement a program that sums up a range of numbers in parallel, using multiple threads. The general algorithmic problem is called “parallel reduction”.

In order to produce comparable solutions, your application should accept three command-line parameters in this order:

The number of threads to be used.
The start number of the range (inclusive).
The end number of the range (inclusive).
The program should perform a true parallelized computation with a flexible number of threads. Play with different thread counts and ranges, and try to answer the following questions for yourself:

What is the relation between the optimal thread count and my computer hardware ?
Does my CPU has hyperthreading enabled ? Is this relevant for the performance with different thread counts ?
Is it possible to develop a serial version of the program that is faster than my multithreaded solutions ?
*/
#include <iostream>
#include <sstream>
#include <ctime>
#include <omp.h>

int main(int argc, char* argv[])
{
  if(argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <THREADS>" << " <START>" << " <END>" << std::endl;
    return 1;
  }

  // Get command line arguments arguments
  int threads;
  int start;
  long end;
  std::istringstream ( argv[1] ) >> threads;
  std::istringstream ( argv[2] ) >> start;
  std::istringstream ( argv[3] ) >> end;

  // Parallel reduction
  omp_set_num_threads(threads);
  long sum = 0;
  
  unsigned int start_time = clock();
  #pragma omp parallel reduction(+: sum)
  {
    #pragma omp for 
    for(int i = start; i <= end; ++i)
    {
      sum += i;
    }
  }

  unsigned int time = clock() - start_time;
  std::cout << "Result: " << sum << std::endl
	    << "Used threads: " << omp_get_max_threads() << std::endl
	    << "Time: " << time << "ms" << std::endl;
}
