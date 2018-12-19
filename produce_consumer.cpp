#include<iostream>
#include<thread>
#include<vector>
#include<queue>
#include<algorithm>
#include<condition_variable>
#include<atomic>


using namespace std;

mutex m_mutex;
condition_variable full_cond_var, empty_cond_var;
atomic<int> shared_variable;
const int num_of_producers = 1;
const int num_of_consumers = 1;
const int max_num_of_items = 100;
const int num_of_items_to_produce = 5;
const int num_of_items_to_consume = 3;
queue<int> queue_buffer;


class Producer 
{
    int item;
    public:
   Producer() : item(0){
       
   }

   void thread_run(int thread_id)
   {
      cout<<"Producer thread run"<<endl;
     
      
      // wait if buffer is full.
     while (1) {
         cout<<"queue size " << queue_buffer.size() <<endl;
           
         {
           //  queue_buffer.push(1);
           unique_lock<mutex> lock_guard(m_mutex); 
      full_cond_var.wait_for(lock_guard,  chrono::seconds(2), [] {
                                     return queue_buffer.size() <= max_num_of_items;
                                    }
                    );
cout<<"PRODUCER THREAD "<<endl;
      // out of blocked state. Lets do some job now.
      for (int i=0;i<num_of_items_to_consume;i++) {
          cout<<"Producing element "<<item<<" iter " << i <<endl;
          item++;
          if (item >= max_num_of_items) {
              break;
          }
           queue_buffer.push(item);
           }


      lock_guard.unlock();
    empty_cond_var.notify_all();  // have produced some items. Consumers please start consuming.
   // this_thread::sleep_for(chrono::milliseconds(500));
   }
 //empty_cond_var.notify_all();  // have produced some items. Consumers please start consuming.
   this_thread::sleep_for(chrono::milliseconds(500));
 //    this_thread::yield();
     }

   }

};

class Consumer
{
   public:
    Consumer(){}
    
   void thread_run(int thread_id)
   {
      cout<<"Consumer thread run"<<endl;


      // wait if buffer is empty.
     while (1) {
        
         {
         unique_lock<mutex> lock_guard(m_mutex);           
      empty_cond_var.wait_for(lock_guard, chrono::seconds(2), [] {
                                     return  !queue_buffer.empty();
                                    }
                    );
cout<<"Consumer THREAD "<<endl;
        for (int i=0;i<num_of_items_to_consume;i++) {
            if (queue_buffer.size() > 0) {
             int consumed_element =  queue_buffer.front();
             cout<<"Consumed element "<<consumed_element<<endl;
             queue_buffer.pop();
        }
      }
      lock_guard.unlock();
   full_cond_var.notify_all(); // some space is there. producer please produce.
   //this_thread::sleep_for(chrono::milliseconds(500));
   }
    //full_cond_var.notify_all(); // some space is there. producer please produce. 
      this_thread::sleep_for(chrono::milliseconds(500));
    //  this_thread::yield();
     }
   }
};

int main()
{
   vector<thread> thread_list;
   Producer producer;
   Consumer consumer;

   for (int i=0;i<num_of_producers;i++) {
       thread_list.push_back(thread(&Producer::thread_run, &producer, i));
  }

   for (int i=0;i<num_of_consumers;i++) {
       thread_list.push_back(thread(&Consumer::thread_run, &consumer, i));
  }

   for(thread& thread_iter: thread_list)  {
       thread_iter.join();
   }

}