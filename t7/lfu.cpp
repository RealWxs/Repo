#include <iostream>
#include <vector>
using namespace std;

int seqNumber;

int * refSeq;
int * frames;
int * pages;
int * pages_use;

int frameNumber;
int current_frame = 0;
int pageNumber;

int page_fault = 0;

vector<int> eliminatePages = vector<int>();


void replace_lfu();
void init(bool);
int main(int argc)
{
    cin >> pageNumber >> frameNumber >> seqNumber;

    init(argc>1);
    replace_lfu();

}
void replace_lfu()
{
    cout << "LFU" << endl;
    int cur = -1;//当前请求页面
    for (int i = 0; i < seqNumber; ++i) //检查引用串
    {
        //cout << "当前页号：" << refSeq[i] << "\n";
        cur = pages[refSeq[i]];//将页号映射为帧号
        if(cur == -1)   //页号无效
        {
            //cout << "缺页错误: " << "\n";
            page_fault++;   //缺页错误+1
            if (current_frame < frameNumber)//当前有空闲帧
            {
                pages[refSeq[i]] = current_frame;
                frames[current_frame] = refSeq[i]; //将页面装入页帧
                pages_use[refSeq[i]] = 1;   //设置频数位
                //cout << "分配空闲帧 frame number = " << current_frame;
                for (int p = 0; p <= current_frame; ++p)
                {
                    cout << frames[p] << " ";
                }
                current_frame++;
            }
            else
            {
                int minIndex = -1;
                int lf = INT32_MAX;
                for (int p = 0; p < pageNumber; ++p)
                {
                    if (pages[p+1]!=-1&&pages_use[p+1]<lf)
                    {
                        lf = pages_use[p+1];
                        minIndex = p;
                    }
                }
                int temp_f = pages[minIndex+1];
                pages[minIndex+1] = -1;
                pages[refSeq[i]] = temp_f;
                pages_use[refSeq[i]] = 1;
                frames[temp_f] = refSeq[i];
                for(int p=0;p<current_frame; p++)
                {
                    cout << frames[p]<< " ";
                }
                cout << "-> " << minIndex+1;

            }

        }
        else
        {
           // cout << "页面请求正常";

            pages_use[refSeq[i]]+=1;//更新频数位
            for(int p=0;p<current_frame; p++)
            {
                cout << frames[p]<< " ";
            }

        }
        cout << endl;
    }
    int swap = eliminatePages.size();
    cout << "Eliminate pages: ";
    for (int i = 0; i < swap; ++i)
    {
        cout << eliminatePages.at(i) << " ";
    }

    cout << "\nNumber of page faults: " << page_fault << "\nRate of page faults: " << (float(page_fault)/seqNumber)*100 << "%\n";
}
void init(bool flag)
{

    refSeq = new int[seqNumber];
    pages = new int[pageNumber+1];
    pages_use = new int[pageNumber+1];
    frames = new int [frameNumber];



    for (int i = 0; i <= pageNumber; ++i)
    {
        pages[i] = -1;
        pages_use[i] = 0;
    }
    for (int i = 0; i < frameNumber ; ++i)
    {
        frames[i] = -1;
    }
    if(flag)
    {
        cout << "random generated sequence: \n";
        for (int i = 0; i < seqNumber; ++i)
        {
            int t = (rand() % pageNumber)+ 1;
            cout << t << " ";
            refSeq[i] = t;
        }
        cout << endl;

    }
    else
    {
        for (int i = 0; i < seqNumber; ++i)
        {
            cin >> refSeq[i];
        }
    }


}


