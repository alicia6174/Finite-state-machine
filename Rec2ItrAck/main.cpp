#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

struct Frame
{
    Frame(int n = 0, int k = 0, int s = 0):
        arg_m(n),
        arg_n(k),
        st(s)
    {}

    int arg_m;
    int arg_n;
    int st;
    int local_tmp;
    int ret;
};

//Construct a class of Stack by myself.
template <class T>
class Stack
{
    int m_sp;
    T m_buf[1024];

public:
    Stack(void):
        m_sp(0)
    {
    }

    T * top(void)
    {
        return &m_buf[m_sp-1];
    }

    T pop(void)
    {
        return m_buf[--m_sp];
    }

    void push(const T & t)
    {
        m_buf[m_sp++] = t;
    }

    bool empty(void) const
    {
        return m_sp == 0;
    }

    int size(void)
    {
        return m_sp;
    }
};

enum
{
    ST_RETURE = 64
};

int ack(int m, int n)
{

    Stack<Frame> sys_st;

    sys_st.push(Frame(m, n));


    int ret_val = 0;

    int max_sp = 0;


    while (!sys_st.empty())
    {
        int st = sys_st.top()->st;
        int m = sys_st.top()->arg_m;
        int n = sys_st.top()->arg_n;

        max_sp = max(max_sp, sys_st.size());
        switch (st)
        {
            case 0:
                if (m == 0)
                {
                    sys_st.top()->ret = n + 1;
                    sys_st.top()->st = ST_RETURE;
                    break;
                }

                if (n == 0)
                {
                    sys_st.top()->st = 10;
                    sys_st.push(Frame(m-1, 1));
                    break;
                }

                sys_st.top()->st = 20;
                sys_st.push(Frame(m, n-1));

                break;

            case 10:
                sys_st.top()->st = ST_RETURE;
                sys_st.top()->ret = ret_val;
                break;

            case 20:
                sys_st.top()->st = 21;

                sys_st.push(Frame(m-1, ret_val));
                break;

            case 21:
                sys_st.top()->st = ST_RETURE;
                sys_st.top()->ret = ret_val;
                break;

            case ST_RETURE:
                ret_val  = sys_st.pop().ret;
                break;
        };

    }
    return ret_val;
}


int main(int argc, const char * argv[])
{
    for (int m = 0; m <= 3; ++m)
    {
        for (int n = 0; n <= 3; ++n)
        {
            printf("[%d]", ack(m, n));
        }
        printf("\n");
    }

    return 0;
}
