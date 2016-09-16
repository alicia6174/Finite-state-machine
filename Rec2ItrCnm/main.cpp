#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

struct Frame
{
    Frame(int n = 0, int m = 0, int s = 0):
        arg_n(n),
        arg_m(m),
        st(s)
    {}

    int arg_n;
    int arg_m;
    int st;
    int tmp;
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
    ST_RETURN = 64
};

int Cnm(int n, int m)
{

    Stack<Frame> sys_st;

    sys_st.push(Frame(n, m, 0));


    int ret_val = 0;

    while (!sys_st.empty())
    {
        int n = sys_st.top()->arg_n;
        int m = sys_st.top()->arg_m;
        int st = sys_st.top()->st;

        switch (st)
        {
            case 0:
                if (m == 0 || m == n)
                {
                    sys_st.top()->ret = 1;
                    sys_st.top()->st = ST_RETURN;
                    break;
                }

                sys_st.top()->st = 1;
                sys_st.push(Frame(n-1, m-1, 0));
                break;

            case 1:
                sys_st.top()->tmp = ret_val;
                sys_st.top()->st = 2;
                sys_st.push(Frame(n-1, m, 0));
                break;

            case 2:
                sys_st.top()->ret = sys_st.top()->tmp + ret_val;
                sys_st.top()->st = ST_RETURN;
                break;

            case ST_RETURN:
                ret_val = sys_st.top()->ret;
                sys_st.pop();
                break;
        };

    }
    return ret_val;
}


int main(int argc, const char * argv[])
{
   printf("C(%d,%d) = %d\n", 3, 2, Cnm(3, 2));

    return 0;
}
