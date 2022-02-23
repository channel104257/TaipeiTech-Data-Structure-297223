/**********************************
2022/02/23 0.0.1
用for迴圈實作階乘

n = 0, 1
n! = 1
n > 1
n! = n * (n-1)!

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
    int output = 1;

    if (n == 0) // 0! = 1
    {
        return 1;
    }
    else
    {
        //重複的乘上 i，直到 i = n
        for (size_t i = 1; i <= n; i++)
        {
            output = output * i;
        }

        return output;
    }
}
