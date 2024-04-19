// A simple example to capture the following task dependencies.
//
//           +---+
//     +---->| B |-----+
//     |     +---+     |
//   +---+           +-v-+
//   | A |           | D |
//   +---+           +-^-+
//     |     +---+     |
//     +---->| C |-----+
//           +---+
//
#include <taskflow/taskflow.hpp>  // the only include you need

int main(){

  tf::Executor executor;
  tf::Taskflow taskflow("simple");

  auto [A, B, C, D] = taskflow.emplace(
    [](bool& result) { std::cout << "TaskA\n"; result = false;},
    [](bool& result) { std::cout << "TaskB\n"; result = true;},
    [](bool& result) { std::cout << "TaskC\n"; result = true;},
    [](bool& result) { std::cout << "TaskD\n"; result = true;}
  );

  A.precede(B, C);  // A runs before B and C
  D.succeed(B, C);  // D runs after  B and C

  executor.run(taskflow).wait();

  return 0;
}
