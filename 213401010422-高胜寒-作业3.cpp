/************************************************************************/

/* Dijkstra算法：求出从i到任意节点的最短路径

*/

/*

参数：

    int arrArcs[][MAX_VERTEX_COUNT],          有向图邻接矩阵

    const int nVertexCount,                   节点数目

    const int startVertex,                    源节点

    int *pDistance,                            各个节点到达源节点的距离

    int *pPreVertex                           各个节点的前一个节点

*/

/************************************************************************/





void Dijkstra(int arrArcs[][MAX_VERTEX_COUNT], const int nVertexCount, const int startVertex, int* pDistance, int* pPreVertex)

{

    // isIns用于判断所有的节点是否在S集合中，初始为false，每进入一个设置对应为true，直到所有为true，算法停止

    vector<bool> isInS;                  //是否已经在S集合中（S中的点均已算出从i到其的最短路径）

    isInS.reserve(0);                    // 设置大小为0

    isInS.assign(nVertexCount, false);   //重新分配vector大小，所有的节点都不在S集合中



    int i, j;

    // Step 1: 先求出i,j之间不通过第三方节点转发的距离

    //         初始化pDistance和pPreVertex数组，此时可以求出i->j不通过其他点的距离

    for (j = 0; j < nVertexCount; ++j)

    {

        // 第一次遍历时，查找的最短距离为两点之间不通过第三方的最短距离

        pDistance[j] = arrArcs[startVertex][j];

        if (arrArcs[startVertex][j] < MAX_DISTANCE)

            pPreVertex[j] = startVertex;  // i，j之间可以直连，那么j的前序节点便是i

        else

            pPreVertex[j] = -1;       // -1表示前一节点未知

    }

    pPreVertex[startVertex] = -1;     // 开始节点的前序节点未知



    // Step 2: 求出i,j之间通过第三方节点k转发的最短距离

    /*开始使用贪心思想循环处理不在S集合中的每一个节点*/

    isInS[startVertex] = true;          //开始节点放入S集合中

    int k = startVertex;                // 标记中间节点



    //开始节点已经存放在S中了，还有nVertexCount-1个节点要处理，故i从1开始

    for (i = 1; i < nVertexCount; i++)

    {



        // Step 2.1 : 寻找不在S集合中的距离i的distance最小的节点(依次遍历距离矩阵)

        int nextVertex = k;

        int tempDistance = MAX_DISTANCE;

        for (j = 0; j < nVertexCount; ++j)

        {

            //寻找不在S集合中的距离i的distance最小的节点

            if ((isInS[j] == false) && (pDistance[j] < tempDistance))

            {

                nextVertex = j;

                tempDistance = pDistance[j];

            }

        }

        // 标记：一轮循环后，可以求得在当前S下，距离i的最近的不在S中的点，并保存数据

        isInS[nextVertex] = true; //距离i最近的节点nextVertex放入S集合中

        k = nextVertex;           //下一次寻找的开始节点k



        // Step 2.2 : 在S加入新节点后，计算从i到j的最短距离，更新distance：

        //            以k为新考虑的中间点，计算从i通过k转发到达j的距离，并与原有的从i直接到j的距离进行比较，选取最小值

        for (j = 0; j < nVertexCount; j++)

        {

            // 仅需计算不在S中的节点（从i出发到达S中的节点的距离是最短的）

            if (isInS[j] == false && arrArcs[k][j] < MAX_DISTANCE)

            {

                if (pDistance[k] + arrArcs[k][j] < pDistance[j]) //以k为新考虑的中间点，计算从i通过k转发到达j的距离

                {

                    pDistance[j] = pDistance[k] + arrArcs[k][j];

                    pPreVertex[j] = k;

                }

            }

        }

    }

}

/************************************************************************/

/* Floyd 算法：求出所有节点两两之间的最短路径

*/

/*

参数：

    Graph * pGraph,                       图的数据结构

    int arrDistance[][MAX_VERTEX_COUNT],  最短距离

    int arrPath[][MAX_VERTEX_COUNT],      最短路径索引

    int nVertexCount                      节点数目

*/

/************************************************************************/

void Floyd(Graph* pGraph, int arrDistance[][MAX_VERTEX_COUNT], int arrPath[][MAX_VERTEX_COUNT])

{

    int i, j, k;

    int nVertexCount = pGraph->nVertexCount;

    // Step 1：初始化arrDistance矩阵和arrPath矩阵

    //     第一次循环时，设置i，j之间的距离即为两者之间直线距离; 

    //     从i出发的到达j的任一节点的前序节点都是i

    for (i = 0; i < nVertexCount; ++i)

    {

        for (j = 0; j < nVertexCount; ++j)

        {

            arrDistance[i][j] = pGraph->arrArcs[i][j];

            arrPath[i][j] = i;

        }

    }

    // Step 2：动态规划

    // Dis(i,j)为节点i到节点j的最短路径的距离，

    //      对于每一个节点k，检查Dis(i,k) + Dis(k,j) < Dis(i,j)是否成立，

    //      如果成立，证明从i到k再到j的路径比i直接到j的路径短，便设置Dis(i,j) = Dis(i,k) + Dis(k,j)

    //      当我们遍历完所有节点k，Dis(i,j)中记录的便是i到j的最短路径的距离



    for (k = 0; k < nVertexCount; ++k)

    {

        for (i = 0; i < nVertexCount; ++i)

        {

            for (j = 0; j < nVertexCount; ++j)

            {

                // 对于每一个节点k，检查Dis(i,k) + Dis(k,j) < Dis(i,j)是否成立，

                if (arrDistance[i][k] + arrDistance[k][j] < arrDistance[i][j])

                {

                    // 找到更短路径

                    arrDistance[i][j] = arrDistance[i][k] + arrDistance[k][j];

                    // 存储路径索引值

                    arrPath[i][j] = arrPath[k][j];

                }

            }

        }

    }

}
