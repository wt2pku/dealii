//----------------------------------------------------------------------
//    $Id: functional_01.cc 23753 2011-05-30 00:22:23Z bangerth $
//
//    Copyright (C) 2012 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//----------------------------------------------------------------------

#include "../tests.h"
#include <deal.II/base/logstream.h>
#include <deal.II/lac/trilinos_sparsity_pattern.h>
#include <deal.II/lac/trilinos_sparse_matrix.h>

int main(int argc, char ** argv)
{
  const std::string logname = JobIdentifier::base_name(__FILE__) + std::string("/output");
  std::ofstream logfile(logname.c_str());
  deallog.attach(logfile);
  deallog.depth_console (0);

  Utilities::MPI::MPI_InitFinalize mpi_initialization (argc, argv);
  
  TrilinosWrappers::SparsityPattern pattern(4,5,2);
  pattern.add(0,2);
  pattern.add(0,0);
  pattern.add(1,0);
  pattern.add(1,3);
  pattern.add(2,4);
  pattern.add(2,2);
  pattern.add(3,0);
  pattern.add(3,4);
  pattern.compress();
  
  TrilinosWrappers::SparseMatrix matrix(pattern);
  matrix.set(0,2, 3.5);
  matrix.set(0,0, 1.);
  matrix.set(1,0, -2.);
  matrix.set(1,3, 1.5);
  matrix.set(2,4, -2.25);
  matrix.set(2,2, -0.5);
  matrix.set(3,0, 2.);
  matrix.set(3,4, 0.);

				   // Print the matrix
  for (TrilinosWrappers::SparseMatrix::const_iterator i=matrix.begin(); i != matrix.end();++i)
    deallog << i->row() << ' ' << i->column() << ' ' << i->value() << std::endl;
  deallog << std::endl;
  
				   // Add 0.5 to each element
  for (TrilinosWrappers::SparseMatrix::iterator i=matrix.begin(); i != matrix.end();++i)
    i->value() += .5;
  
				   // Print the matrix
  for (TrilinosWrappers::SparseMatrix::const_iterator i=matrix.begin(); i != matrix.end();++i)
    deallog << i->row() << ' ' << i->column() << ' ' << i->value() << std::endl;
  deallog << std::endl;
  
				   // Subtract 1 from each element in row 2
  for (TrilinosWrappers::SparseMatrix::iterator i=matrix.begin(2); i != matrix.end(2);++i)
    i->value() -= 1.;

				   //  Double each element in row 1
  for (TrilinosWrappers::SparseMatrix::iterator i=matrix.begin(1); i != matrix.end(1);++i)
    i->value() *= 2;

				   // Set the first entry to zero
  matrix.begin()->value() = 0;
  
				   // Print the matrix
  for (TrilinosWrappers::SparseMatrix::const_iterator i=matrix.begin(); i != matrix.end();++i)
    deallog << i->row() << ' ' << i->column() << ' ' << i->value() << std::endl;
  deallog << std::endl;
}