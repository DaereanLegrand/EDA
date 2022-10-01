// Copyright Roger Peralta Aranibar

#include "RTree.hpp"
#include "Rectangle.hpp"

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

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
    /*
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
    // */

    RTree<2, std::string, 5>::Node n;
    RTree<2, std::string, 5>::Node nn;

    Rectangle<2> r1;
    r1[0] = Interval(1, 2);
    r1[1] = Interval(2, 4);
    Rectangle<2> r2;
    r2[0] = Interval(3, 4);
    r2[1] = Interval(4, 5);
    Rectangle<2> r3;
    r3[0] = Interval(6, 7);
    r3[1] = Interval(2, 3);
    Rectangle<2> r4;
    r4[0] = Interval(5, 6);
    r4[1] = Interval(1, 2);
    Rectangle<2> r5;
    r5[0] = Interval(8, 9);
    r5[1] = Interval(2, 4);
    Rectangle<2> r6;
    r6[0] = Interval(10, 11);
    r6[1] = Interval(4, 5);
    Rectangle<2> r7;
    r7[0] = Interval(13, 14);
    r7[1] = Interval(2, 3);
    Rectangle<2> r8;
    r8[0] = Interval(12, 13);
    r8[1] = Interval(1, 2);
    Rectangle<2> r9;
    r9[0] = Interval(15, 16);
    r9[1] = Interval(3, 4);

    RTree<2, std::string, 5> r_tree;
    r_tree.insert(r1, "l1");
    r_tree.insert(r2, "l2");
    r_tree.insert(r3, "ll1");
    r_tree.insert(r4, "ll2");
    r_tree.insert(r5, "lll1");
    r_tree.insert(r6, "lll2");
    r_tree.insert(r7, "llll1");
    r_tree.insert(r8, "llll2");



    r_tree.insert(r9, "llll3");
    return 0;
}
