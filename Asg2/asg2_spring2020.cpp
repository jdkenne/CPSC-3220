//I'm really sorry I'm submitting this late, I will try to do better next time
#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class task{
private:


public:
  char task_id;
  int arrival_time;
  int service_time;
  int remaining_time;
  int completion_time;
  int response_time;
  int wait_time;
  int orig_t;
  int final_time;
  int number_of_tasks;
  int task_counter;
  int beginning_of_queue;
  int end_of_queue;
  void setRemainingTime(int rem_time){
    remaining_time = rem_time;
  }
  void setCompletionTime(int comp_time){
    completion_time = comp_time;
  }
  void setResponseTime(int res_t){
    response_time = res_t;
  }
  void setWaitTime(int wait){
    wait_time = wait;
  }
  char getTaskID() const {
    return task_id;
  }
  int getArrivalTime() const {
    return arrival_time;
  }
  int getServiceTime() const{
    return service_time;
  }
  int getTimeRemaining() const{
    return remaining_time;
  }
  int getCompletionTime() const{
    return completion_time;
  }
  int getResponseTime() const{
    return response_time;
  }
  int getWaitTime() const{
    return wait_time;
  }

};

void FIFO (){
  cout << "FIFO scheduling results\n\n";
  cout << "time\tcpu\treadyqueue (tid/rst)\n";
  for(int i = 0; i < 35; i++){
    cout << "-";
  }
  cout << "\n";
  int x1;
  int x2;
  char taskID = 'A';
  vector<task> Pablo;
  int time_that_is_available = 0;
  //reading input file
  while(cin >> x1){
    cin >> x2;
    task t1;
    //setting variables to values in input file
    t1.task_id = taskID;
    t1.orig_t = x1;
    t1.arrival_time = x1;
    t1.final_time = x1+x2-1;
    t1.number_of_tasks = x2;
    t1.service_time = x2;
    t1.completion_time = t1.service_time + t1.arrival_time;
    t1.remaining_time = t1.service_time;
    t1.wait_time = 0;
    t1.response_time = t1.service_time;
    t1.beginning_of_queue = 0;
    t1.end_of_queue = 0;
    for(auto x:Pablo){
      if(t1.arrival_time <= x.final_time){
        t1.beginning_of_queue = t1.arrival_time;
        t1.end_of_queue = time_that_is_available-1;
        t1.arrival_time = time_that_is_available;
        t1.final_time = time_that_is_available + t1.number_of_tasks - 1;
        t1.remaining_time--;
        t1.wait_time = t1.end_of_queue - t1.beginning_of_queue;
      }
    }
    time_that_is_available = t1.final_time + 1;
    //pushing task onto vector
    Pablo.emplace_back(t1);
    taskID++;
  }
  //printing out first table
  for(int time = 0; time < time_that_is_available; time++){
    cout << time;
    for(auto &x: Pablo){
      if(time >= x.arrival_time && time <= x.final_time){
        cout << "\t" << x.task_id << x.number_of_tasks;
        x.number_of_tasks-=1;
      }
      else if(time >= x.beginning_of_queue && time <= x.end_of_queue && x.beginning_of_queue != 0){
        cout << "\t" << x.task_id << x.number_of_tasks;
      }
    }
    cout << "\n";
  }
  //printing second table
  cout << "\n\tarrival\tservice\tcompletion\tresponse\twait\n";
  cout << "tid\ttime\ttime\ttime\t\ttime\t\ttime\n";
  for(int i = 0; i < 60; i++){
    cout << "-";
  }
  cout << "\n";
  for(auto x: Pablo){
    if(x.wait_time > 0){
      x.wait_time += 1;
    }
    cout << x.task_id << "\t" << x.orig_t << "\t" << x.service_time << "\t" << (x.final_time+1) << "\t\t" << x.service_time + x.wait_time << "\t\t" << x.wait_time << "\n";
  }
  //printing out third table
  cout << "\nservice\twait\n";
  cout << "time\ttime\n";
  cout << "----- -------\n";
  for(auto x:Pablo){
    if(x.wait_time > 0){
      x.wait_time += 1;
    }
    cout << x.service_time << "\t" << x.wait_time << "\n";
  }
}
bool sortVector(task &x, task &y){
  //comparing arrival time of x to arrival time of y
  if(x.arrival_time < y.arrival_time) return true;
  if(x.arrival_time > y.arrival_time) return false;
  //comparing number of tasks of x to number of tasks of y
  if(x.number_of_tasks < y.number_of_tasks) return true;
  if(x.number_of_tasks > y.number_of_tasks) return false;
  return false;
}
void SJF(){
  cout << "SJF(preemptive) scheduling results\n\n";
  cout << "time\tcpu\treadyqueue (tid/rst)\n";
  for(int i = 0; i < 35; i++){
    cout << "-";
  }
  cout << "\n";
  int x1;
  int x2;
  char taskID = 'A';
  vector<task> Pablo;
  int time_that_is_available = 0;
  //reading input file
  while(cin >> x1){
    cin >> x2;
    task t1;
    //assigning variables
    t1.orig_t = x1;
    t1.arrival_time = x1;
    t1.final_time = x1+x2-1;
    t1.number_of_tasks = x2;
    t1.service_time = x2;
    Pablo.emplace_back(t1);
  }
  //sorting vector
  sort(Pablo.begin(), Pablo.end(), sortVector);
  for(auto &x:Pablo){
    x.task_id = taskID;
    taskID++;
  }
  //setting variables
  Pablo[0].completion_time = Pablo[0].service_time + Pablo[0].arrival_time;
  Pablo[0].remaining_time = Pablo[0].service_time;
  Pablo[0].wait_time = 0;
  Pablo[0].response_time = Pablo[0].service_time;
  Pablo[0].beginning_of_queue = 0;
  Pablo[0].end_of_queue = 0;
  for(int index = 1; index < sizeof(Pablo); index++){
    Pablo[index].completion_time = Pablo[index].service_time + Pablo[index].arrival_time;
    Pablo[index].remaining_time = Pablo[index].service_time;
    Pablo[index].wait_time = 0;
    Pablo[index].response_time = Pablo[index].service_time;
    for(int i = 0; i < index; i++){
      if(Pablo[index].arrival_time <= Pablo[i].final_time){
        Pablo[index].beginning_of_queue = Pablo[index].arrival_time;
        Pablo[index].end_of_queue = Pablo[i].final_time;
        Pablo[index].arrival_time = Pablo[i].final_time+1;
        Pablo[index].final_time = Pablo[index].arrival_time + Pablo[index].number_of_tasks - 1;
        Pablo[index].remaining_time--;
        Pablo[index].wait_time = Pablo[index].end_of_queue - Pablo[index].beginning_of_queue;
      }
    }
  }

  time_that_is_available = Pablo[sizeof(Pablo)-1].final_time+1;
  //printing out first table
  for(int time = 0; time < time_that_is_available; time++){
    cout << time;
    for(auto &x: Pablo){
      if(time >= x.arrival_time && time <= x.final_time){
        cout << "\t" << x.task_id << x.number_of_tasks;
        x.number_of_tasks-=1;
      }
      else if(time >= x.beginning_of_queue && time <= x.end_of_queue && x.beginning_of_queue != 0){
        cout << "\t" << x.task_id << x.number_of_tasks;
      }


    }
   cout << "\n";
  }

  //printing out second table
  cout << "\n\tarrival\tservice\tcompletion\tresponse\twait\n";
  cout << "tid\ttime\ttime\ttime\t\ttime\t\ttime\n";
  for(int i = 0; i < 60; i++){
    cout << "-";
  }
  cout << "\n";
  for(auto x: Pablo){
    if(x.wait_time > 0){
      x.wait_time += 1;
    }
    cout << x.task_id << "\t" << x.orig_t << "\t" << x.service_time << "\t" << (x.final_time+1) << "\t\t" << x.service_time + x.wait_time << "\t\t" << x.wait_time << "\n";
  }

  //printing out third table
  cout << "\nservice\twait\n";
  cout << "time\ttime\n";
  cout << "----- -------\n";
  for(auto x:Pablo){
    if(x.wait_time > 0){
      x.wait_time += 1;
    }
    cout << x.service_time << "\t" << x.wait_time << "\n";
  }


}
int main(int argc, char* argv[]){
  string fxn = argv[1];
  vector<task> Pablo;
  //fifo
  if(fxn == "-fifo"){

    FIFO();
  }
  //sjf
  if(fxn == "-sjf"){
    SJF();
  }

  return 0;
}


