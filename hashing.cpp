#include <bits/stdc++.h>
using namespace std;

int bindec(int x, int d)
{
    int ans = 0;
    for (int i = 0; i < d; i++)
    {
        int buff = x & 1;
        if (buff == 1)
            ans = ans + pow(2, i);
        x = x >> 1;
    }

    return ans;
}

class hashing
{
private:
    int x;
    int gd;
    vector<int *> directory;

public:
    hashing(int n);
    void insert(int n);
    void print();
    int search(int n);
    void deleteval(int n);
    ~hashing();
};

hashing::hashing(int n)
{
    gd = 1;
    x = n;
    directory.push_back(new int[n + 2]);
    directory.push_back(new int[n + 2]);
    directory[0][n + 1] = 1;
    directory[1][n + 1] = 1;

    directory[0][n] = 0;
    directory[1][n] = 0;
}

void hashing::insert(int n)
{

    int flag = search(n);

    if (flag == 1)
        return;

    int pos = bindec(n, gd);

    int size = directory[pos][x];

    if (directory[pos][x] < x)
    {
        directory[pos][directory[pos][x]] = n;
        directory[pos][x]++;
    }

    else
    {
        if (directory[pos][x + 1] == gd)
        {
            for (int i = 0; i < pow(2, gd); i++)
            {
                directory.push_back(directory[i]);
            }

            directory[pos + pow(2, gd)] = new int[x + 2];
            directory[pos + pow(2, gd)][x] = 0;
            directory[pos + pow(2, gd)][x + 1] = gd + 1;
            directory[pos][x + 1] = gd + 1;
            gd++;

            vector<int> buff;

            for (int i = 0; i < x; i++)
            {
                buff.push_back(directory[pos][i]);
            }

            directory[pos][x] = 0;
            directory[pos + pow(2, gd - 1)][x] = 0;

            for (int q = 0; q < buff.size(); q++)
            {

                int ex_pos = bindec(buff[q], gd);
                directory[ex_pos][directory[ex_pos][x]] = buff[q];
                directory[ex_pos][x]++;
            }

            insert(n);
        }

        else
        {
            int ld = directory[pos][x + 1];
            int test = directory[pos][0];

            int bin = bindec(test, ld);

            directory[bin + pow(2, ld)] = new int[x + 2];
            directory[bin + pow(2, ld)][x + 1] = ld + 1;
            directory[bin + pow(2, ld)][x] = 0;
            directory[bin][x + 1] = ld + 1;
            directory[bin][x] = 0;

            vector<int> tuff;

            for (int i = 0; i < x; i++)
            {
                tuff.push_back(directory[bin][i]);
            }

            for (int i = 0; i < tuff.size(); i++)
                insert(tuff[i]);

            insert(n);
        }
    }
}

void hashing::print()
{
    for (int i = 0; i < directory.size(); i++)
    {
        cout << "directory" << i << " "
             << "values =";

        for (int j = 0; j < directory[i][x]; j++)
            cout << directory[i][j] << " ";

        cout << endl;
    }
}

int hashing::search(int n)
{
    int hash = bindec(n, gd);
    int found = 0;
    for (int i = 0; i < directory[hash][x]; i++)
    {
        if (directory[hash][i] == n)
            found = 1;
    }

    return found;
}

void hashing::deleteval(int n)
{
    int flag = search(n);

    if (flag == 0)
        return;

    int pos = bindec(n, gd);

    if (directory[pos][x] != 1)
    {
        for (int i = 0; i < directory[pos][x]; i++)
        {
            if (directory[pos][i] == n)
            {
                for (int j = i + 1; j < directory[pos][x]; j++)
                    directory[pos][j - 1] = directory[pos][j];

                break;
            }
        }
        directory[pos][x]--;
    }

    else
    {
        if (directory[pos][x + 1] == 1)
            return;

        int *arrptr = directory[pos];

        int ld = directory[pos][x + 1];

        int num = bindec(pos, ld - 1);

        if (directory[num] == arrptr)
        {
            num = num + pow(2, ld - 1);
        }

        for (int i = 0; i < directory.size(); i++)
        {
            if (directory[i] == arrptr)
                directory[i] = directory[num];
        }

        directory[num][x + 1]--;

        delete[] arrptr;
    }
}

hashing::~hashing()
{
}

int main()
{
    int n;
    cin >> n;

    hashing has(n);

    // int num;
    // cin >> num;

    // for(int i=0;i<num;i++)
    // {
    //     int x;
    //     cin >> x;

    //     has.insert(x);
    // }

    has.insert(10);
    has.insert(20);
    has.insert(91);
    has.insert(79);
    has.insert(40);
    has.insert(50);
    has.insert(31);
    has.insert(7);
    has.insert(9);
    has.insert(20);
    // has.insert(26);

    has.deleteval(10);
    has.deleteval(50);

    // cout << has.search(26) << endl;

    has.print();

    // set<int *> se;
    // int *arr=  new int[5];

    // se.insert(arr);

    // arr=  new int[5];

    // se.insert(arr);

    // cout << se.size() << endl;
}