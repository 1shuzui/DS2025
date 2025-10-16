#include<string>
using namespace std;

void bubblesort1A ( int A[], int n ) { //起泡排序算法（版本1A）：0 <= n 
    bool sorted = false; //整体排序标志，首先假定尚未排序  
    while ( !sorted ) { //在尚未确讣已全局排序前，逐趟进行扫描交换 
        sorted = true; //假定已经排序 
        for ( int i = 1; i < n; i++ ) { //自左向右逐对检查当前范围A[0, n)内的各相邻元素 
            if ( A[i - 1] > A[i] ) { //一旦A[i - 1]与A[i]逆序，则            
            swap ( A[i - 1], A[i] ); //交换之，并
            sorted = false; //因整体排序不能能保证，需要清除排序标志          
            } 
        } 
        n--; //至此末元素必然就位，故可以缩短待排序序列的有效长度 
    } 
} //借助布尔型标志位sorted，可及时提前退出，而不致总是蛮力地做n - 1趟扫描交换



int countOnes ( unsigned int n ) { //统计整数二进制展开中数位1的总数：O(logn)     
    int ones = 0; //计数器复位 
    while ( 0 < n ) { //在n缩减至0之前，反复地 
        ones += ( 1 & n ); //检查最低位，若为1则计数 
        n >>= 1; //右移一位 
    } 
    return ones; //返回计数 
} //等效于glibc的内置函数int __builtin_popcount (unsigned int n)



int sumI ( int A[], int n ) { //数组求和算法（迭代版） 
    int sum = 0; //初始化累计器，O(1)  
    for ( int i = 0; i < n; i++ ) //对全部共O(n)个元素，逐一 h
        sum += A[i]; //累计，O(1) 
    return sum; //返回累计值，O(1) 
} //O(1) + O(n)*O(1) + O(1) = O(n+2) = O(n)



__int64 power2BF_I ( int n ) { //幂函数2^n算法（蛮力迭代版），n >= 0    
    __int64 pow = 1; //O(1)：累积器刜始化为2^0 
    while ( 0 < n -- ) //O(n)：迭代n轮，每轮都    
        pow <<= 1; //O(1)：将累积器翻倍 
    return pow; //O(1)：返回累积器 
} //O(n) = O(2^r)，r为输入指数n的比特位数



1 int sum ( int A[], int n ) { //数组求和算法（线性递归版） 
2    
if ( 1 > n ) //平凡情况，递归基
3       
return 0; //直接（非递归式）计算 
else //一般情况
return sum ( A, n - 1 ) + A[n - 1]; //递归：前n - 1项之和，再累计第n - 1项 
} //O(1)*递归深度 = O(1)*(n + 1) = O(n)




void reverse ( int*, int, int ); //重载的倒置算法原型 
void reverse ( int* A, int n ) //数组倒置（算法的初始入口，调用的可能是reverse()的递归版迭代版） 
{ reverse ( A, 0, n - 1 ); } //由重载的入口启动递归或迭代算法



void reverse ( int* A, int lo, int hi ) { //数组倒置（多递归基递归版） 
    if ( lo < hi ) { 
        swap ( A[lo], A[hi] ); //交换A[lo]和A[hi] 
        reverse ( A, lo + 1, hi - 1 ); //递归倒置A(lo, hi) 
    } //else隐含了两种递归基 
} //O(hi - lo + 1)



inline __int64 sqr ( __int64 a ) { return a * a; } 
    __int64 power2 ( int n ) { //幂函数2^n算法（优化递归版），n >= 0 
    if ( 0 == n ) return 1; //递归基；否则，视n的奇偶分别递归 
    return ( n & 1 ) ? sqr ( power2 ( n >> 1 ) ) << 1 : sqr ( power2 ( n >> 1 ) ); 
} //O(logn) = O(r)，r为输入指数n的比特位数




void reverse ( int* A, int lo, int hi ) { //数组倒置（直接改造而得的迭代版） 
next: //算法起始位置添加跳转标志  
    if ( lo < hi ) {     
        swap ( A[lo], A[hi] ); //交换A[lo]和A[hi] 
    lo++; hi--; //收缩待倒置区间     
    goto next; //跳转至算法体的起始位置，迭代地倒置A(lo, hi) 
    } //else隐含了迭代的终止 
} //O(hi - lo + 1)



void reverse ( int* A, int lo, int hi ) { //数组倒置（规范整理之后的迭代版） 
    while ( lo < hi ) //用while替换跳转标志和if，完全等效 
        swap ( A[lo++], A[hi--] ); //交换A[lo]和A[hi]，收缩待倒置区间
} //O(hi - lo + 1) 



int sum ( int A[], int lo, int hi ) { //数组求和算法（二分递归版，入口为sum(A, 0, n - 1)） 
    if ( lo == hi ) //如遇递归基（区间长度已降至1），则 
        return A[lo]; //直接返回该元素 
    else { //否则（一般情况下lo < hi），则 
        int mi = ( lo + hi ) >> 1; //以居中单元为界，将原区间一分为二 
        return sum ( A, lo, mi ) + sum ( A, mi + 1, hi ); //递归对各子数组求和，然后合计 
    } 
} //O(hi - lo + 1)，线性正比于区间的长度



__int64 fib ( int n ) { //计算Fibonacci数列的第n项（二分递归版）：O(2^n) 
    return ( 2 > n ) ?     
           ( __int64 ) n //若到达递归基，直接取值   
           : fib ( n - 1 ) + fib ( n - 2 ); //否则，逑弻计算前两项，其和即为正解 
}  



__int64 fib ( int n, __int64& prev ) { //计算Fibonacci数列第n项（线性递归版）：入口形式fib(n, prev) 
    if ( 0 == n ) //若到达递归基，则 
        { prev = 1; return 0; } //直接取值：fib(-1) = 1, fib(0) = 0 
    else { //否则 
        __int64 prevPrev; prev = fib ( n - 1, prevPrev ); //递归计算前两项 
        return prevPrev + prev; //其和即为正解 
    } 
} //用辅助变量记录前一项，返回数列的当前项，O(n)



__int64 fibI ( int n ) { //计算Fibonacci数列的第n项（迭代版）：O(n)   
    __int64 f = 0, g = 1; //刜始化：fib(0) = 0, fib(1) = 1  
    while ( 0 < n-- ) { g += f; f = g - f; } //依据原始定义，通过n次加法和减法计算fib(n) 
    return f; //返回
} 



typedef int Rank; //秩 
#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大） 
template <typename T> class Vector { //向量模板类 
protected: 
    Rank _size; int _capacity;  T* _elem; //规模、容量、数据区域
    void copyFrom ( T const* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi) 
    void expand(); //空间不足时扩容 
    void shrink(); //装填因子过小时压缩 
    bool bubble ( Rank lo, Rank hi ); //扫描交换 
    oid bubbleSort ( Rank lo, Rank hi ); //起泡排序算法 
    Rank max ( Rank lo, Rank hi ); //选取最大元素 
    void selectionSort ( Rank lo, Rank hi ); //选择排序算法 
    void merge ( Rank lo, Rank mi, Rank hi ); //归并算法 
    void mergeSort ( Rank lo, Rank hi ); //归并排序算法 
    Rank partition ( Rank lo, Rank hi ); //轴点排序算法 
    void quickSort ( Rank lo, Rank hi ); //快速排序算法 
    void heapSort ( Rank lo, Rank hi ); //堆排序（稍后结合完全堆讲解） 
public:
// 析构函数 
    Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) //容量为c、规模为s、所有元素初始为v 
    { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } //s<=c 
    Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //数组整体复刢 
    Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //区间 
    Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //向量整体复制
    Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } //区间
// 析构函数 
    ~Vector() { delete [] _elem; } //释放内部空间 
// 只读的访问接口 
    Rank size() const { return _size; } //规模
    bool empty() const { return !_size; } //判空
    int disordered() const; //判断向量是否已排序 
    Rank find ( T const& e ) const { return find ( e, 0, _size ); } //无序向量整体查找 
    Rank find ( T const& e, Rank lo, Rank hi ) const; //无序向量区间查找 
    Rank search ( T const& e ) const //有序向量整体查找 
    { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); } 
    Rank search ( T const& e, Rank lo, Rank hi ) const; //有序向量区间查找 
// 可写访问接口 
    T& operator[] ( Rank r ) const; //重载下标操作符，可以类似于数组形式引用各元素 
    Vector<T> & operator= ( Vector<T> const& ); //重载赋值操作符，以便直接克隆向量 
    T remove ( Rank r ); //删除秩为r的元素 
    int remove ( Rank lo, Rank hi ); //删除秩在区间[lo, hi)之内的元素 
    Rank insert ( Rank r, T const& e ); //揑入元素 
    Rank insert ( T const& e ) { return insert ( _size, e ); } //默认作为末元素插入
    void sort ( Rank lo, Rank hi ); //对[lo, hi)排序 
    void sort() { sort ( 0, _size ); } //整体排序 
    void unsort ( Rank lo, Rank hi ); //对[lo, hi)置乱 
    void unsort() { unsort ( 0, _size ); } //整体置乱
    int deduplicate(); //无序去重 
    int uniquify(); //有序去重 
// 遍历 
    void traverse ( void (* ) ( T& ) ); //遍历（使用函数指针，只读或局部性修改） 
    template <typename VST> void traverse ( VST& ); //遍历（使用函数对象，可局部性修改） 
}; //Vector 



template <typename T> //元素类型 
void Vector<T>::copyFrom ( T const* A, Rank lo, Rank hi ) { //以数组区间[lo, hi)为蓝本复制向量    
    _elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //分配空间，规模清零   
    while ( lo < hi ) //A[lo, hi)内的元素逐一   
        _elem[_size++] = A[lo++]; //复制至_elem[0, hi - lo) 
} 



template <typename T> Vector<T>& Vector<T>::operator= ( Vector<T> const& V ) { //重载 
    if ( _elem ) delete [] _elem; //释放原有内容  
    copyFrom ( V._elem, 0, V.size() ); //整体复制 
    return *this; //返回当前对象的引用，以便链式赋值 
}



template <typename T> void Vector<T>::expand() { //向量空间不足时扩容 
    if ( _size < _capacity ) return; //尚未满员时，不必扩容 
    if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //不低于最小容量 
    T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //容量加倍 
    for ( int i = 0; i < _size; i++ ) 
        _elem[i] = oldElem[i]; //复制原向量内容（T为基本类型，或已重载赋值操作符'='） 
    delete [] oldElem; //释放原空间 
} 



template <typename T> void Vector<T>::shrink() { //装填因子过小时压缩向量所占空间 
    if ( _capacity < DEFAULT_CAPACITY << 1 ) return; //不致收缩到DEFAULT_CAPACITY以下 
    if ( _size << 2 > _capacity ) return; //以25%为界 
    T* oldElem = _elem;  _elem = new T[_capacity >>= 1]; //容量减半 
    for ( int i = 0; i < _size; i++ ) _elem[i] = oldElem[i]; //复制原向量内容 
    delete [] oldElem; //释放原空间 
}



template <typename T> T& Vector<T>::operator[] ( Rank r ) const //重载下标操作符 
{ return _elem[r]; } // assert: 0 <= r < _size



template <typename T> void permute ( Vector<T>& V ) { //随机置乱向量，使各元素等概率出现于各位置 
    for ( int i = V.size(); i > 0; i-- ) //自后向前 
        swap ( V[i - 1], V[rand() % i] ); //V[i - 1]与V[0, i)中某一随机元素交换 
}



template <typename T> void Vector<T>::unsort ( Rank lo, Rank hi ) { //等概率随机置乱区间[lo, hi) 
    T* V = _elem + lo; //将子向量_elem[lo, hi)视作另一向量V[0, hi - lo) 
    for ( Rank i = hi - lo; i > 0; i-- ) //自后向前 
        swap ( V[i - 1], V[rand() % i] ); //将V[i - 1]与V[0, i)中某一元素随机交换 
} 



template <typename T> static bool lt ( T* a, T* b ) { return lt ( *a, *b ); } //less than 
template <typename T> static bool lt ( T& a, T& b ) { return a < b; } //less than 
template <typename T> static bool eq ( T* a, T* b ) { return eq ( *a, *b ); } //equal 
template <typename T> static bool eq ( T& a, T& b ) { return a == b; } //equal



template <typename T> //无序向量的顺序查找：返回最后一个元素e的位置；失败时，返回lo - 1 
Rank Vector<T>::find ( T const& e, Rank lo, Rank hi ) const { //assert: 0 <= lo < hi <= _size 
    while ( ( lo < hi-- ) && ( e != _elem[hi] ) ); //从后向前，顺序查找 
    return hi; //若hi < lo，则意味着失败；否则hi即命中元素的秩  
}



template <typename T> //将e作为秩为r元素插入
Rank Vector<T>::insert ( Rank r, T const& e ) { //assert: 0 <= r <= size 
    expand(); //若有必要，扩容 
    for ( int i = _size; i > r; i-- ) _elem[i] = _elem[i-1]; //自后向前，后继元素顺次后移一个单元 
    _elem[r] = e; _size++; //置入新元素并更新容量 
    return r; //返回秩 
}



template <typename T> int Vector<T>::remove ( Rank lo, Rank hi ) { //删除区间[lo, hi) 
    if ( lo == hi ) return 0; //出于效率考虑，单独处理退化情况，比如remove(0, 0) 
    while ( hi < _size ) _elem[lo++] = _elem[hi++]; //[hi, _size)顺次前移uhi - lo个单元 
    _size = lo; //更新规模，直接丢弃尾部[lo, _size = hi)区间
    shrink(); //若有必要，则缩容 
    return hi - lo; //返回被删除元素的数目 
}



template <typename T> T Vector<T>::remove ( Rank r ) { //删除向量中秩为r的元素，0 <= r < size   
    T e = _elem[r]; //备份被删除元素 
    remove ( r, r + 1 ); //调用区间删除算法，等效于对区间[r, r + 1)的删除 
    return e; //返回被删除元素 
} 



template <typename T> int Vector<T>::deduplicate() { //删除无序向量中重复元素（高效版） 
    int oldSize = _size; //记弽原规模
    Rank i = 1; //从_elem[1]开始 
    while ( i < _size ) //自前向后逐一考查各元素_elem[i] 
        ( find ( _elem[i], 0, i ) < 0 ) ? //在其前缀中寻找与之雷同者（至多一个） 
        i++ : remove ( i ); //若无雷同则继续考查其后继，否则删除雷同者 
    return oldSize - _size; //向量规模变化量，即被删除元素总数 
} 



template <typename T> void Vector<T>::traverse ( void ( *visit ) ( T& ) ) //借助函数指针机制
{ for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); } //遍历向量 
template <typename T> template <typename VST> //元素类型、操作器 
void Vector<T>::traverse ( VST& visit ) //借助函数对象机制
{ for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); } //遍历向量 



template <typename T> struct Increase //函数对象：逑增、、递增一个T类对象 
{  virtual void operator() ( T& e ) { e++; }  }; //假设T可直递增或已重载++ 

template <typename T> void increase ( Vector<T> & V ) //统一递增向量中的各元素 
{  V.traverse ( Increase<T>() );  } //以Increase<T>()为基本操作进行遍历



template <typename T> int Vector<T>::disordered() const { //返回向量中逆序相邻元素对的总数 
    int n = 0; //计数器 
    for ( int i = 1; i < _size; i++ ) //逐一检查_size - 1对相邻元素    
        if ( _elem[i - 1] > _elem[i] ) n++; //逆序则计数 
    return n; //向量有序当且仅当n = 0 
}



template <typename T> int Vector<T>::uniquify() { //有序向量重复元素剔除算法（低效版） 
    int oldSize = _size; int i = 1; //当前比对元素的秩，起始于首元素 
    while ( i < _size ) //从前向后，逐一比对各对相邻元素 
        _elem[i - 1] == _elem[i] ? remove ( i ) : i++; //若雷同，则删除后者；否则，转至后一元素 
    return oldSize - _size; //向量规模发化量，即被删除元素总数 
}



template <typename T> int Vector<T>::uniquify() { //有序向量重复元素剔除算法（高效版）   
    Rank i = 0, j = 0; //各对互异“相邻”元素的秩 
    while ( ++j < _size ) //逐一扫描，直至末元素 
        if ( _elem[i] != _elem[j] ) //跳过雷同者 
        _elem[++i] = _elem[j]; //发现不同元素时，向前移至紧邻于前者右侧 
    _size = ++i; shrink(); //直接截除尾部多余元素 
    return j - i; //向量规模发化量，即被删除元素总数 
} 



template <typename T> //在有序向量的区间[lo, hi)内，确定不大于e的最后一个节点的秩 
Rank Vector<T>::search ( T const& e, Rank lo, Rank hi ) const { //assert: 0 <= lo < hi <= _size 
    return ( rand() % 2 ) ? //按各50%的概率随机使用二分查找或Fibonacci查找 
           binSearch ( _elem, e, lo, hi ) : fibSearch ( _elem, e, lo, hi ); 
} 



 // 二分查找算法（版本A）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size 
template <typename T> static Rank binSearch ( T* A, T const& e, Rank lo, Rank hi ) { 
    while ( lo < hi ) { //每步迭代可能要做两次比较判断，有三个分支 
        Rank mi = ( lo + hi ) >> 1; //以中点为轴点 
        if      ( e < A[mi] ) hi = mi; //深入前半段[lo, mi)继续查找 
        else if ( A[mi] < e ) lo = mi + 1; //深入后半段(mi, hi)继续查找 
        else                
    return mi; //在mi处命中 
    } //成功查找可以提前终止 

    return -1; //查找失败 
} //有多个命中元素时，不能保证返回秩最大者；查找失败时，简单地返回-1，而不能指示失败的位置



#include "..\fibonacci\Fib.h" //引入Fib数列类 
// Fibonacci查找算法（版本A）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size 
template <typename T> static Rank fibSearch ( T* A, T const& e, Rank lo, Rank hi ) { 
    Fib fib ( hi - lo ); //用O(log_phi(n = hi - lo)时间创建Fib数列 
    while ( lo < hi ) { //每步迭代可能要做两次比较判断，有三个分支 
        while ( hi - lo < fib.get() ) fib.prev(); //通过向前顺序查找（分摊O(1)）——至多迭代几次？ 
        Rank mi = lo + fib.get() - 1; //确定形如Fib(k) - 1的轴点 
        if      ( e < A[mi] ) hi = mi; //深入前半段[lo, mi)继续查找 
        else if ( A[mi] < e ) lo = mi + 1; //深入后半段(mi, hi)继续查找 
        else                return mi; //在mi处命中 
    } //成功查找可以提前终止  
    return -1; //查找失败 
} //有多个命中元素时，不能保证返回秩最大者；失败时，简单地返回-1，而不能指示失败的位置



// 二分查找算法（版本B）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size 
template <typename T> static Rank binSearch ( T* A, T const& e, Rank lo, Rank hi ) { 
    while ( 1 < hi - lo ) { //每部迭代仅需做一次比较判断，有两个分支；成功查找不能提前终止 
        Rank mi = ( lo + hi ) >> 1; //以中点为轴点 
        ( e < A[mi] ) ? hi = mi : lo = mi; //经比较后确定深入[lo, mi)或[mi, hi) 
    } //出口时hi = lo + 1，查找区间仅含一个元素A[lo] 
    return ( e == A[lo] ) ? lo : -1 ; //查找成功时返回对应的秩；否则统一返回-1 
} //有多个命中元素时，不能保证返回秩最大者；查找失败时，简单地返回-1，而不能指示失败的位置



// 二分查找算法（版本C）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size 
template <typename T> static Rank binSearch ( T* A, T const& e, Rank lo, Rank hi ) { 
    while ( lo < hi ) { //每步迭代仅需做一次比较判断，有两个分支 
        Rank mi = ( lo + hi ) >> 1; //以中点为轴点 
        ( e < A[mi] ) ? hi = mi : lo = mi + 1; //经比较后确定深入[lo, mi)或(mi, hi) 
    } //成功查找不能提前终止 
    return --lo; //循环结束时，lo为大于e的元素的最小秩，故lo - 1即大于e的元素的最大秩 
} //有多个命中元素时，总能保证返回秩最大者；查找失败时，能够返回失败的位置



 template <typename T> void Vector<T>::sort ( Rank lo, Rank hi ) { //向量区间[lo, hi)排序 
    switch ( rand() % 5 ) { //随机选取排序算法。可根据具体问题的特点灵活选取或扩充 
        case 1:  bubbleSort ( lo, hi ); break; //起泡排序 
        case 2:  selectionSort ( lo, hi ); break; //选择排序（习题） 
        case 3:  mergeSort ( lo, hi ); break; //归并排序 
        case 4:  heapSort ( lo, hi ); break; //堆排序（稍后介绍） 
        default: quickSort ( lo, hi ); break; //快速排序（稍后介绍） 
    } 
} 


template <typename T> //向量的起泡排序 
void Vector<T>::bubbleSort ( Rank lo, Rank hi ) //assert: 0 <= lo < hi <= size 
{ while ( !bubble ( lo, hi-- ) ); } //逐趟做扫描交换，直至全序



template <typename T> bool Vector<T>::bubble ( Rank lo, Rank hi ) { //一趟扫描交换 
    bool sorted = true; //整体有序标志 
    while ( ++lo < hi ) //自左向右，逐一检查各对相邻元素 
       if ( _elem[lo - 1] > _elem[lo] ) { //若逆序，则 
          sorted = false; //意味着尚未整体有序，并需要 
          swap ( _elem[lo - 1], _elem[lo] ); //通过交换使局部有序 
       } 
    return sorted; //返回有序标志 
} 



template <typename T> //向量归并排序 
void Vector<T>::mergeSort ( Rank lo, Rank hi ) { //0 <= lo < hi <= size 
    if ( hi - lo < 2 ) return; //单元素区间自然有序，否则... 
    int mi = ( lo + hi ) >> 1; mergeSort ( lo, mi ); 
    mergeSort ( mi, hi ); //以中点为界分别排序 
    merge ( lo, mi, hi ); //归并
}



template <typename T> //有序向量的归并
void Vector<T>::merge ( Rank lo, Rank mi, Rank hi ) { //各自有序的子向量[lo, mi)和[mi, hi) 
    T* A = _elem + lo; //合并后的向量A[0, hi - lo) = _elem[lo, hi) 
    int lb = mi - lo; T* B = new T[lb]; //前子向量B[0, lb) = _elem[lo, mi) 
    for ( Rank i = 0; i < lb; B[i] = A[i++] ); //复制前子向量 
    int lc = hi - mi; T* C = _elem + mi; //后子向量C[0, lc) = _elem[mi, hi) 
    for ( Rank i = 0, j = 0, k = 0; ( j < lb ) || ( k < lc ); ) { //B[j]和C[k]中的小者续至A末尾 
        if ( ( j < lb ) && ( ! ( k < lc ) || ( B[j] <= C[k] ) ) ) A[i++] = B[j++]; 
        if ( ( k < lc ) && ( ! ( j < lb ) || ( C[k] <  B[j] ) ) ) A[i++] = C[k++]; 
    } 
    delete [] B; //释放临时空间B 
} //归并后得到完整的有序向量[lo, hi)



typedef int Rank; //秩 
#define ListNodePosi(T) ListNode<T>* //列表节点位置 

template <typename T> struct ListNode { //列表节点模板类（以双向链表形式实现） 
// 成员 
    T data; ListNodePosi(T) pred; ListNodePosi(T) succ; //数值、前驱、后继 
// 构造函数 
    ListNode() {} //针对header和trailer的构造 
    ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )   
        : data ( e ), pred ( p ), succ ( s ) {} //默认构造器 
// 操作接口 
    ListNodePosi(T) insertAsPred ( T const& e ); //紧靠弼前节点之前插入新节点 
    ListNodePosi(T) insertAsSucc ( T const& e ); //紧随弼前节点之后插入新节点 
}; 