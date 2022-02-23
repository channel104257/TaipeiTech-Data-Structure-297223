/**********************************
2022/02/23 0.0.1
用遞迴實作階乘

n = 0, 1
n! = 1
n > 1
n! = n * (n-1)!

時間複雜度:O(n)

author : 110310138 電機一甲 劉千榮
**********************************/
#include <iostream>

using namespace std;

int fact(int n);

int main()
{
    int n, output;

    //防呆迴圈
    for (int i = 0; i < 1; i++)
    {
        cout << "Please enter a number n = ";
        cin >> n;

        //若輸入數值為負數
        if (n < 0)
        {
            cout << "Please enter a positive number" << endl;
            i--;
        }
    }

    output = fact(n);
    cout << n << "! = " << output << endl;

    return 0;
}

int fact(int n)
{
    if (n == 0) // 0! = 1
    {
        return 1;
    }
    else
    {
        //使用遞迴(單一遞迴呼叫)
        return (fact(n - 1) * n);
    }
}
