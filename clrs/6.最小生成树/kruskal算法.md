## kruskal算法

kruskal算法的正确性证明由通用算法正确性证明的推论给出：由边集A确定的多个连通分支中，选取连接任意两个连通分支的轻边e，则e为安全边。

算法伪代码如下

```pseudocode
MST_KRUSKAL
A = 空集
for each vertex 属于 G.V
	Make-SET(v) //初始化并查集，每个顶点都是一个连通分支
根据权重对所有边进行排序
for each edge(u,v) 属于 G.E 以非降序取出
	if find(u) != find(v) //这条边连接了两个不同的连通分支
		将(u,v) 加入A
		合并连通分支u,v
return A
```

时间复杂度分析：

1. 对边集进行排序复杂度为O( ElgE )
2. 初始化并查集复杂度为O( V )
3. for循环外层以非降序取出边重复次数为O( E )
4. for循环内层并查集操作在使用路径压缩与按秩合并技术的前提下复杂度为$\Theta$( lg V )
5. for循环总复杂度为O( ElgV )
6. 算法时间复杂度为( ElgE )，由于|E|<$|V|^2$，所以有lgE < 2lgV，所以复杂度为O( ElgV )

