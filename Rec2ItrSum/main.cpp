#include <stdio.h>
#include <stack>

using namespace std;

int sumRec(int n)
{
    if (n == 1) return 1;
    return sumRec(n-1) + n;
}

struct sys_st_data_t
{
    int arg;
    int st;
    int ret;
};

enum
{
    ST_RETURN = 64
};

stack<sys_st_data_t> sys_st;

int sumItr(int n)
{
    sys_st_data_t tmp_data;
    tmp_data.arg = n;
    tmp_data.st = 0;
    sys_st.push(tmp_data);

    sys_st_data_t cur_data;

    int ret_val = 0;

    while (!sys_st.empty())
    {
        cur_data = sys_st.top();
        int st = cur_data.st;
        int arg = cur_data.arg;

        switch (st)
        {
            case 0:
                if (arg == 1)
                {
                    tmp_data = sys_st.top();
                    tmp_data.ret = 1;
                    tmp_data.st = ST_RETURN;

                    sys_st.pop();
                    sys_st.push(tmp_data);
                    break;
                }

                sys_st.pop();
                cur_data.st = 1;
                sys_st.push(cur_data);

                tmp_data.arg =  arg - 1;
                tmp_data.st = 0;
                sys_st.push(tmp_data);
                break;

            case 1:
                cur_data.ret = ret_val + arg;
                cur_data.st = ST_RETURN;

                sys_st.pop();
                sys_st.push(cur_data);

                break;

            case ST_RETURN:
                ret_val = sys_st.top().ret;
                sys_st.pop();
                break;
        };
    }

    return ret_val;
}

int main(int argc, const char * argv[])
{
    printf("sum = %d\n", sumItr(10));
    return 0;
}
