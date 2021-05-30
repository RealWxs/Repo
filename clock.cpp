#include <iostream>
#include <vector>
using namespace std;

int seqNumber;
int  _refSeq[] =  {1,2,3,4,1,2,5,1,2,3,4,5};
int _frames[] = {-1,-1,-1,-1};
int  _pages[] = {-1,-1,-1,-1,-1,-1};
int  _pages_ref[] = {0,0,0,0,0,0};

int * refSeq;
int * frames;
int * pages;
int * pages_ref;

int frameNumber;
int current_frame = 0;
int pageNumber;

int page_fault = 0;

vector<int> eliminatePages = vector<int>();
int clock_pointer = 0;


void replace_clock();
void init(bool);
int main(int argc)
{
    cin >> pageNumber >> frameNumber >> seqNumber;

    init(argc>1);
    replace_clock();

}
void replace_clock()
{
    cout << "Clock" << endl;
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
                pages_ref[refSeq[i]] = 1;
                //cout << "分配空闲帧 frame number = " << current_frame;
                for (int p = 0; p <= current_frame; ++p)
                {
                    cout << frames[p] << " ";
                }
                current_frame++;
            }
            else
            {

                while (pages_ref[clock_pointer+1] != 0 || pages[clock_pointer+1]==-1)//寻找牺牲帧:当前页表项有效且为第二次机会时退出
                {
                    pages_ref[clock_pointer+1] = 0; //修改引用位
                    clock_pointer = (clock_pointer + 1) % pageNumber; //指针轮转
                }
                int temp_f = pages[clock_pointer+1]; //获得待替换页表项的页号
                //cout << "无空闲帧，选择牺牲帧 frame number = " << temp_f;
                frames[temp_f] = refSeq[i]; //装入页帧
                pages[clock_pointer+1] = -1;//被剥夺的页表项变为无效
                pages[refSeq[i]] = temp_f;//将剥夺的帧号分配给当前页表项
                pages_ref[refSeq[i]] = 1;//设置引用位
                for (int p = 0; p < current_frame; ++p)
                {
                    cout << frames[p]<< " ";
                }
                eliminatePages.push_back(clock_pointer+1);
                cout << "-> " << clock_pointer+1;
            }

        }
        else
        {
           // cout << "页面请求正常";
            pages_ref[refSeq[i]] = 1;//更新引用位
            for(int p=0;p<current_frame; p++)
            {
                cout << frames[p]<< " ";
            }

        }
        cout << endl;
    }
    int swap = eliminatePages.size();
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
    pages_ref = new int[pageNumber+1];
    frames = new int [frameNumber];

    for (int i = 0; i <= pageNumber; ++i)
    {
        pages[i] = -1;
        pages_ref[i] = 0;
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

