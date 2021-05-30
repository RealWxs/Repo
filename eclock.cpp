//
// Created by 吴 on 2021/5/20.
//

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

int seqNumber;

int * refSeq;
int * wrSeq;
int * frames;
int * pages;
int * pages_ref;
int * pages_wr;

int frameNumber;
int current_frame = 0;
int pageNumber;

int page_fault = 0;

vector<int> eliminatePages = vector<int>();
int clock_pointer = 0;


void replace_eClock();
void init(bool);
int main(int argc, char* argv[])
{
    cin >> pageNumber >> frameNumber >> seqNumber;

    init(argc>1);
    replace_eClock();

}
void replace_eClock()
{
    cout << "eClock" << endl;
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
                pages_ref[refSeq[i]] = 1;   //设置引用位
                pages_wr[refSeq[i]] = wrSeq[i]; //设置读写位
                //cout << "分配空闲帧 frame number = " << current_frame;
                for (int p = 0; p <= current_frame; ++p)
                {
                    cout << frames[p] << " ";
                }
                current_frame++;
            }
            else
            {

                int current_best = -1;
                int temp_pointer = clock_pointer;
                for (int j = 0; j < pageNumber; ++j) //寻找最佳替换&清除引用位
                {
                    if (pages[temp_pointer+1] == -1)
                    {
                        temp_pointer = (temp_pointer + 1)%pageNumber;
                        continue;
                    }
                    if (pages_ref[temp_pointer+1] == 0 && pages_wr[temp_pointer+1] == 0)//最佳替换
                    {
                        current_best = temp_pointer;
                        break;
                    }
                    else
                    {
                        pages_ref[temp_pointer+1] = 0;
                        temp_pointer = (temp_pointer + 1)%pageNumber;
                    }
                }
                temp_pointer = current_best;
                while (current_best == -1)    //寻找最佳替换&清除读写位
                {


                     if (pages[clock_pointer + 1] == -1)
                     {
                         clock_pointer = (clock_pointer + 1) % pageNumber;
                         continue;
                     }
                     if (pages_ref[clock_pointer + 1] == 0 && pages_wr[clock_pointer + 1] == 0)   //最佳替换
                     {
                         current_best = clock_pointer;
                         break;
                     }
                     else
                     {
                         pages_wr[clock_pointer + 1] = 0;
                         clock_pointer = (clock_pointer + 1) % pageNumber;
                     }

                }
                if (temp_pointer != -1) //第一次命中
                {
                    clock_pointer = temp_pointer; //调整指针位置
                }


                int temp_f = pages[clock_pointer+1]; //获得待替换页表项的页号
                //cout << "无空闲帧，选择牺牲帧 frame number = " << temp_f;
                frames[temp_f] = refSeq[i]; //装入页帧
                pages[clock_pointer+1] = -1;//被剥夺的页表项变为无效
                pages[refSeq[i]] = temp_f;//将剥夺的帧号分配给当前页表项
                pages_ref[refSeq[i]] = 1;//设置引用位
                pages_wr[refSeq[i]] = wrSeq[i];//设置读写位
                for (int p = 0; p < current_frame; ++p)
                {
                    cout << frames[p]<< " ";
                }
                eliminatePages.push_back(clock_pointer+1);
                cout << "-> " << clock_pointer+1;
                clock_pointer = (clock_pointer+1)%pageNumber;//指向下一个页面
            }

        }
        else
        {
            // cout << "页面请求正常";
            pages_ref[refSeq[i]] = 1;//更新引用位
            pages_wr[refSeq[i]] |= wrSeq[i];//更新读写位
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
    wrSeq = new int[seqNumber];
    pages = new int[pageNumber+1];
    pages_ref = new int[pageNumber+1];
    pages_wr = new int[pageNumber+1];
    frames = new int [frameNumber];



    for (int i = 0; i <= pageNumber; ++i)
    {
        pages[i] = -1;
        pages_ref[i] = 0;
        pages_wr[i] = 0;
    }
    for (int i = 0; i < frameNumber ; ++i)
    {
        frames[i] = -1;
    }
    if(flag)
    {
        cout << "random generated sequence: \n";
        srand((int)(time(NULL)));
        for (int i = 0; i < seqNumber; ++i)
        {
            int t = (rand() % pageNumber)+ 1;
            int wr = rand()%2;
            cout << t << "[" << wr <<"] ";
            refSeq[i] = t;
            wrSeq[i] = wr;

        }
        cout << endl;

    }
    else
    {
        for (int i = 0; i < seqNumber; ++i)
        {
            cin >> refSeq[i];
            cin >> wrSeq[i];
        }
    }


}


