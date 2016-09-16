#include <stdio.h>
#include <stack>

using namespace std;

struct node_t
{
    int val;
    node_t * left;
    node_t * right;

    node_t(int v):
        val(v),
        left(NULL),
        right(NULL)
    {
    }


};

struct sys_st_data_t
{
    node_t * arg;
   // int ret;

    int st;
};

stack<sys_st_data_t> sys_st;

enum
{

    ST_RETURE = 64
};

node_t * initRoot(void)
{
    node_t * t[5];
    for (int i = 0; i < 5; ++i)
        t[i] = new node_t(i);

    t[0]->left = t[1];
    t[0]->right = t[4];

    t[1]->left = t[2];
    t[1]->right = t[3];

    return t[0];

}

void postOrderRec(node_t * root)
{
    if (!root)
        return;

    postOrderRec(root->left);
    postOrderRec(root->right);
    printf("%d ", root->val);
}

void postOrderItr(node_t * root)
{
    sys_st_data_t tmp_data;
    tmp_data.arg = root;
    tmp_data.st = 0;
    sys_st.push(tmp_data);

    while (!sys_st.empty())
    {
        sys_st_data_t cur_data  = sys_st.top();
        node_t * cur_root = cur_data.arg;
        int st = cur_data.st;

        switch (st)
        {
            case 0:
                if (cur_root == NULL)
                {
                    cur_data.st = ST_RETURE;
                    sys_st.pop();
                    sys_st.push(cur_data);
                    break;
                }

                cur_data.st = 1;
                sys_st.pop();
                sys_st.push(cur_data);

                tmp_data.arg = cur_root->left;
                tmp_data.st = 0;
                sys_st.push(tmp_data);

                break;

            case 1:
                cur_data.st = 2;
                sys_st.pop();
                sys_st.push(cur_data);

                tmp_data.arg = cur_root->right;
                tmp_data.st = 0;
                sys_st.push(tmp_data);
                break;

            case 2:
                printf("%d ", cur_root->val);
                cur_data.st = ST_RETURE;
                sys_st.pop();
                sys_st.push(cur_data);
                break;

            case ST_RETURE:
                sys_st.pop();
                break;

        };

    }

    printf("\n");


}

int main(int argc, const char * argv[])
{
    node_t * root = initRoot();
    postOrderRec(root);
    printf("\n");
    postOrderItr(root);
    return 0;
}
