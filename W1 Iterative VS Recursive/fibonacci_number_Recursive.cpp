/**********************************
2022/02/23 0.0.1
用遞迴實作費式數列

n = 0, 1
F(0) = 0, F(1) = 1
n > 1
F(n) = F(n-1) + F(n-2)

時間複雜度:O(1.618^n)

author : 110310138 電機一甲 劉千榮
**********************************/
#include <iostream>

using namespace std;

int fibo(int n);

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

    output = fibo(n);
    cout << "第" << n << "個 Fibonacci number 是 " << output << endl;

    return 0;
}

int fibo(int n)
{
    int n0 = 0; // f(0) = 0
    int n1 = 1; // f(1) = 1
    int output;

    if (n == 1)
    {
        return n1;
    }
    else if (n == 0)
    {
        return n0;
    }
    else
    {
        //重複 F(n) = F(n-1) + F(n-2)
        return fibo(n - 1) + fibo(n - 2);
    }
}
