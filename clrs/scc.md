定理：强连通分支算法能得到正确结果

证明：因为算法是根据第一次DFS完成时间f的逆序对图的转置进行第二次DFS，因此要证明定理等价于证明在第一次得到的点的顺序中假设u.f>v.f，若在第二次DFS中u，v在同一棵深度优先树中即存在u到v的路径，当且仅当u，v在同一个强连通分量中。

充分性：

假设在转置图G*中存在简单路径u\~w\~v，则说明在图G中存在路径v\~w\~u，现在证明在原图中若没有u到v的路径，则不可能得到u.f>v.f。根据在第一次DFS中发现u、v的顺序讨论。当u.d<v.d时，若不存在u到v的路径，则v不是u的子节点，所以在u活动的时间内无法发现v，所以u.f<v.d<v.f，在这种情况下与假设的u.f>v.f矛盾；当v.d<u.d时，因为存在v到u的路径，所以u会成为v的子节点，所以有u.f<v.d，仍然与假设矛盾。因此必有u到v的路径，那么此时u与v能够相互到达，即u、v属于同一个连通分量。

必要性：

当u、v在同一个连通分支里面时，u，v在原图和转置图中都能互相到达（因为转置图不影响连通分量的结构），所以定理显然成立。