// Copyright Roger Peralta Aranibar

#include "RTree.hpp"

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <stdexcept>

void press_enter_to_continue() {
  /* Use getline to stall until receiving input. */
  getchar();
}

/* Reports that an unexpected error occurred that caused a test to fail. */
void fail_test(const std::exception& e) {
  std::cerr << "TEST FAILED: Unexpected exception: " << e.what() << std::endl;
  press_enter_to_continue();
}

/* This function is what the test suite uses to ensure that the KDTree works
 * correctly.  It takes as parameters an expression and description, along
 * with a file and line number, then checks whether the condition is true.
 * If so, it prints that the test passed.  Otherwise, it reports that the
 * test fails and points the caller to the proper file and line.
 */
void do_check_condition(bool expr, const std::string& rationale,
                        const std::string& file, int line) {
  /* It worked!  Congrats. */
  if (expr) {
    std::cout << "PASS: " << rationale << std::endl;
    return;
  }

  /* Uh oh!  The test failed! */
  std::cout << "FAIL: " << rationale << std::endl;
  std::cout << "  Error at " << file << ", line " << line << std::endl;
  std::cout << "  (ENTER to continue)" << std::endl;

  /* Pause so that the test fail stands out. */
  press_enter_to_continue();
}

/* This macro takes in an expression and a string, then invokes
 * DoCheckCondition passing in the arguments along with the file
 * and line number on which the macro was called.  This makes it
 * easier to track down the source of bugs if a test case should
 * fail.
 */
#define CHECK_CONDITION(expr, rationale) \
  do_check_condition(expr, rationale, __FILE__, __LINE__)

/* Utility function to delimit the start and end of test cases. */
void print_banner(const std::string& header) {
  std::cout << std::endl << "Beginning test: " << header << std::endl;
  std::cout << std::setw(40) << std::setfill('-') << "" << std::setfill(' ')
            << std::endl;
}

/* Utility function to signal that a test isn't begin run. */
void test_disabled(const std::string& header) {
  std::cout << "== Test " << header
            << " NOT RUN: press ENTER to continue ==" << std::endl;

  /* Pause for the user to hit enter. */
  press_enter_to_continue();
}

/* Utility function to signal the end of a test. */
void end_test() {
  std::cout << "== end of test: press ENTER to continue ==" << std::endl;
  press_enter_to_continue();
}

void basic_r_tree_test() try {
  print_banner("Basic R-Tree Test.");

  /* Construct the RTree. */
  RTree<3, std::string, 5> r_tree;
  CHECK_CONDITION(true, "R-Tree construction completed.");

  /* Check basic properties of the KDTree. */
  CHECK_CONDITION(r_tree.dimension() == 3, "Dimension is three.");
  CHECK_CONDITION(r_tree.size() == 0, "New KD tree has no elements.");
  CHECK_CONDITION(r_tree.empty(), "New KD tree is empty.");

  throw std::overflow_error("Testing Limits.");
} catch (const std::exception& e) {
  fail_test(e);
}

int main() {
  Rectangle<2> r;
  r[0] = Interval(1, 2);
  r[1] = Interval(1, 2);
  Rectangle<2> r2;
  r2[0] = Interval(2, 3);
  r2[1] = Interval(1, 2);
  for (Interval i : r) {
    std::cout << i.begin() << " " << i.end() << std::endl;
  }

  std::cout << overlaps(r, r2) << std::endl;

  RTree<2, std::string, 5>::Node my_node;
  std::cout << "Printing the node" << std::endl;

  for (RTree<2, std::string, 5>::SpatialObject current : my_node) {
    std::cout << "IN" << std::endl;
  }

  RTree<2, std::string, 5> r_tree;
  r_tree.insert(r, "key");
  std::cout << "ID: " << (*r_tree.root_pointer_)[0].identifier << std::endl;

  // basic_r_tree_test();
  return 0;
}
