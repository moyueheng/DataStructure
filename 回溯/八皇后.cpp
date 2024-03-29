/***
 * @Author: Heng
 * @Date: 2022-10-10 16:50:51
 * @LastEditTime: 2022-10-10 16:58:56
 * @LastEditors: Heng
 * @Description:
 * @FilePath: /DataStructure/回溯/八皇后.cpp
 * @Heng
 */

#include <iostream>
using namespace std;
#include <climits>
#include <vector>
#include <cmath>

class Main
{
private:
public:
    static void main()
    {
        Main *m = new Main();
        m->placeQueens(8);
    }
    int * queens;
    bool *cols;      // 某一列是否有皇后
    bool *left_top;  // 左上角到右下角的斜线角线，有没有皇后， 2n-1
    bool *right_top; // 右上角到左下角的对角线
    int n;
    int ways;

    void placeQueens(int n)
    {
        if (n < 1)
        {
            return;
        }
        this->queens = new int[n];
        this->cols = new bool[n];
        this->left_top = new bool[(n << 1) + 1];
        this->right_top = new bool[(n << 1) + 1];
        this->n = n;
        this->ways = 0;
        place(0);
        printf("%d\n", this->ways);
    }

    void show()
    {
        for (int row = 0; row < this->n; row++)
        {
            for (int col = 0; col < this->n; col++)
            {

                if (this->queens[row] == col) // 这个
                {
                    printf("1 ");
                }
                else
                {
                    printf("0 ");
                }
            }
            printf("\n");
        }
        printf("---------------------\n");
    }
    void print_arr(bool *arr, int n)
    {
        for (int i = 0; i < n; i++)
        {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
    /***
     * @description: 从第row航开始摆放皇后
     * @param {int} row
     * @return {*}
     */
    void place(int row)
    {
        if (row == this->n)
        {
            this->show();
            this->ways += 1;
            return;
        }
        // 从第一列开始遍历
        for (int col = 0; col < this->n; col++)
        {
            // 获得 row行， col列所在的 两个对角线信息和列号

            if (cols[col])
                continue; // 当前行已经放置了皇后
            int rt_index = row - col + (n - 1);
            if (this->right_top[rt_index])
                continue;
            int lt_index = row + col;
            if (this->left_top[lt_index])
                continue;
            // 更新存放信息
            this->right_top[rt_index] = true;
            this->left_top[lt_index] = true;
            cols[col] = true; // col已经放置皇后了
            queens[row] = col; // 为了方便画出结果图，记录行号和列号
            //
            place(row + 1); // 准备去摆放下一行
            // 重制一下，为了下一次回溯再深入的时候是可以深入的
            this->right_top[rt_index] = false;
            this->left_top[lt_index] = false;
            cols[col] = false; // col已经放置皇后了
        }
    }
    /***
     * @description: 判断是否要剪枝
     * @param {int} row
     * @param {int} col
     * @return {*}
     */
    bool isValid(int row, int col)
    {
        // 遍历
        for (int i = 0; i < row; i++)
        {
            // 判断这一列能不能放
            if (cols[i] == col)
            {
                return false;
            }
            // 判断斜对角线有没有冲突
            // 通过斜率的知识，我们知道斜率应该上+1，或者-1，(row - i) / (col - cols[i]) == -1或者+1
            // row - i 一定为正，col - cols[i] 可正可负
            // (row - i) / abs(col - cols[i]) == 1 不能这样子写，这里的除法会因为不精确为1而出问题
            if ((row - i) == abs(col - cols[i])) // 第i行的皇后和第row行col列的格子在同一条斜线上
            {
                return false;
            }
        }
        return true;
    }
};
int main(int argc, char const *argv[])
{
    Main::main();
    return 0;
}