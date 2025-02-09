### 红黑树的C++源码编写
性质:
- 红黑树的根与叶子结点(*虚拟的结点*)都为**黑色**
- 红黑树不存在两个**红色结点**相邻(*黑色结点相邻无所谓*)
- 红黑树从根节点到每一个叶子结点的路径上经过的**黑色结点**的个数是相同的
由性质可推出的隐藏要求:
- 每个红结点下的两个子结点肯定为黑色
- 新插入的结点默认为红色结点
常见的操作说明:
- 左旋
![rotate left](https://github.com/user-attachments/assets/dd0c74a8-447a-44ab-a60a-325cb103efa4)
- 右旋
![rotate right](https://github.com/user-attachments/assets/d72216a9-0579-4bc8-9cc7-a3649b41290d)

