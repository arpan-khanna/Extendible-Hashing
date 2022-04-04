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
    //vector<int *> buckets;
    int time=0;

public:
    hashing(int glod,int n);
    void insert(int n);
    void print();
    int search(int n);
    void deleteval(int n,int ingd);
    ~hashing();
};

hashing::hashing(int glod,int n)
{
    gd = glod;
    x = n;

    for(int i=0;i<pow(2,gd);i++)
    {
        directory.push_back(new int[n + 3]);
        directory[i][n + 1] = gd;
        directory[i][n] = 0;
        //cout << time << endl;
        directory[i][n+2] = time++;

    }
    // directory.push_back(new int[n + 3]);
    // directory.push_back(new int[n + 3]);
    // directory[0][n + 1] = 1;
    // directory[1][n + 1] = 1;

    // directory[0][n] = 0;
    // directory[1][n] = 0;

    // directory[0][n+2] = time++;
    // directory[1][n+2] = time++;


    // buckets.push_back(directory[0]);
    // buckets.push_back(directory[1]);

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

            directory[pos + pow(2, gd)] = new int[x + 3];
            // buckets.push_back(directory[pos + pow(2, gd)]);
            directory[pos + pow(2, gd)][x] = 0;
        //cout << time << endl;
            directory[pos + pow(2, gd)][x+2] = time++;
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
            int tin = bin;
            directory[bin][x + 1] = ld + 1;
            directory[bin][x] = 0;

            bin = bin + pow(2,ld);
            int *nar = new int[x+3];
            directory[bin] = nar;
            //buckets.push_back(directory[bin + pow(2, ld)]);
        ///cout << time << endl;
            directory[bin][x+2] = time++;
            directory[bin][x + 1] = ld + 1;
            directory[bin][x] = 0;

            ld++;
            while(bin+pow(2,ld) < pow(2,gd))
            {
                bin = bin + pow(2,ld);
                directory[bin]=nar;
                ld++;
            }

            vector<int> tuff;

            for (int i = 0; i < x; i++)
            {
                tuff.push_back(directory[tin][i]);
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

        cout << " time = " << directory[i][x+2]<< endl;

        // cout << endl;
    }

    set<pair<int,pair<int,int>>> se;

    for (int i = 0; i < directory.size(); i++)
    {   
       se.insert({directory[i][x+2],{directory[i][x],directory[i][x+1]}});

        // cout << endl;
    }

    // for(int k=0;k< buckets.size();k++)
    // {
    //     for(int i=0;i<buckets[i][x];i++)
    //     {
    //         cout << buckets[k][i] << " ";
    //     }

    //     cout << endl;
    // }

    cout << gd << endl;

    int count = 0;
    for(auto x:se)
    {
        count++;
    }

    cout << count << endl;
    for(auto x:se)
    {
        cout <<  x.second.first << " " << x.second.second << endl;
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

void hashing::deleteval(int val,int ingd)
{
    int k = 1 << gd;
    int index = val % k;

    if (search(val) == 0)
        return;

    for (int i = 0; i < directory[index][x]; i++)
        {
            if (directory[index][i] == val)
            {
                for (int j = i + 1; j < directory[index][x]; j++)
                    directory[index][j - 1] = directory[index][j];

                break;
            }
        }
    directory[index][x]--;

    int l1 = directory[index][x+1];
    if (directory[index][x] == 0 && gd > 1 && l1 > 1)
    {
        l1--;
        int k1 = 1 << l1;
        int i1 = index ^ k1;
        if (directory[index][x+1] != directory[i1][x+1])
            return;

        int *B1 = directory[index];
        directory[i1][x+1] = l1;
        directory[index] = directory[i1];
        for (int p = 0; p < directory.size(); p++)
        {
            if (directory[p] == B1)
                directory[p] = directory[i1];
        }

        // for (auto it = Buckets.begin(); it != Buckets.end(); it++)
        // {
        //     if (*it == B1)
        //     {
        //         Buckets.erase(it);
        //         break;
        //     }
        // }

        int j = 0;
        for (; j < directory.size(); j++)
        {
            if (directory[j][x+1] == gd)
                break;
        }
        if (j == directory.size())
        {
            for (int n1 = 0; n1 < j / 2; n1++)
                directory.pop_back();

            gd--;
        }

        // delete B1;
    }

    return ;
}

hashing::~hashing()
{
}

int main()
{
    int glod,n;
    cin >> glod >> n;

    hashing has(glod,n);

    int a,b;

    while(cin >> a)
    {
        switch (a)
        {
        case 2:
            cin >> b;
            has.insert(b);
            break;
        
        case 3:
            cin >> b;
            has.search(b);
            break;

        case 4:
            cin >> b;
            has.deleteval(b,glod);
            break;

        case 5:
            //cin >> b;
            has.print();
            break;
        
        default:
            break;
        }

    }


    //vector<int> buckets;

    // int num;
    // cin >> num;

    // for(int i=0;i<num;i++)
    // {
    //     int x;
    //     cin >> x;

    //     has.insert(x);
    // }

    // has.insert(10);
    // has.insert(20);
    // has.insert(91);
    // has.insert(79);
    // has.insert(40);
    // has.insert(50);
    // has.insert(31);
    // has.insert(7);
    // has.insert(9);
    // has.insert(20);
    // has.insert(26);

    //has.deleteval(10);
    //has.deleteval(50);

    // cout << has.search(26) << endl;

    //has.print();

    // set<int *> se;
    // int *arr=  new int[5];

    // se.insert(arr);

    // arr=  new int[5];

    // se.insert(arr);

    // cout << se.size() << endl;
}