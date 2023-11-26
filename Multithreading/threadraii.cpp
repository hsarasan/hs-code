#include <iostream>
#include <thread>

class threadRAII{
    

    public:
        enum class Action{JOIN,DETACH};
        threadRAII(std::thread &t, Action act=Action::JOIN){
            t_=std::move(t);
            std::cout<<"Created"<<std::endl;
        }
        threadRAII(std::thread &&t, Action act=Action::JOIN){
            std::cout<<"OK"<<std::endl;
            t_=std::move(t);
            std::cout<<"Createdd "<<std::endl;
        }
        threadRAII(const threadRAII& )=delete;
        threadRAII & operator=(const threadRAII& )=delete;
        std::thread & get(){
            return t_;
        }
        ~threadRAII()
        {
            if (act_==Action::JOIN){
                if (t_.joinable())
                {
                    t_.join();
                }
            }
            else{
                t_.detach();
            }
        }
    private:
        std::thread t_;
        Action act_;

};
void doSomething()
{
    for (int i=0;i<10000000;++i)
        i++;
}

int main(){

    std::thread t1(doSomething);
    threadRAII thr(t1);
    threadRAII thr2(std::move(std::thread(doSomething)));
    std::this_thread::sleep_for(std::chrono::seconds(5));
}