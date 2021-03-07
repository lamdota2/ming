/*************************************************************************
	> File Name: queue_shuzu.cpp
	> Author: Terry
	> Mail: terry.liao@nokia-sbell.com
	> Created Time: 2021年03月14日 星期日 15时49分39秒
 ************************************************************************/
//http://c.biancheng.net/view/3353.html
#include<iostream>
using namespace std;
const int maxn=3;
//head队首，taill队尾
int q[maxn],head=0,tail=0;

int en_queue(int x)
{
    if((tail+1)%maxn == head){
        cout<<"queue is full"<<tail<<endl;
        return -1;
    }
    q[tail] = x;
    cout<<"en_queue "<<q[tail]<<endl;
    tail = (tail + 1)%maxn;
    return 0;
}

int pop()
{
    if(head == tail){
        cout<<"queue is empty"<<endl;
        return -1;
    }
    int x=q[head];
    head = (head +1)%maxn;
    cout<<"pop x="<<x<<endl;
    return 0;
}

int main()
{
    en_queue(7);
    en_queue(8);
    en_queue(9);
   // en_queue(6);
    pop();
    pop();
    pop();

    return 0;
}
