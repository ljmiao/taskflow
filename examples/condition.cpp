#include <taskflow/taskflow.hpp>  // the only include you need

int main(){

  tf::Executor executor;
  tf::Taskflow taskflow("simple");

  auto [C, D, E, F] = taskflow.emplace(
    []() ->int { std::cout << "TaskC\n"; return 0;},
    [](bool& result) { std::cout << "TaskD\n"; result = true;},
    [](bool& result) { std::cout << "TaskE\n"; result = true;},
    [](bool& result) { std::cout << "TaskF\n"; result = true;}
  );

  E.precede(D);  
  C.precede(D, F);

  executor.run(taskflow).wait();

  return 0;
}






