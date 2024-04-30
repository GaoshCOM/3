/************************************************************************/

/* Dijkstra�㷨�������i������ڵ�����·��

*/

/*

������

    int arrArcs[][MAX_VERTEX_COUNT],          ����ͼ�ڽӾ���

    const int nVertexCount,                   �ڵ���Ŀ

    const int startVertex,                    Դ�ڵ�

    int *pDistance,                            �����ڵ㵽��Դ�ڵ�ľ���

    int *pPreVertex                           �����ڵ��ǰһ���ڵ�

*/

/************************************************************************/





void Dijkstra(int arrArcs[][MAX_VERTEX_COUNT], const int nVertexCount, const int startVertex, int* pDistance, int* pPreVertex)

{

    // isIns�����ж����еĽڵ��Ƿ���S�����У���ʼΪfalse��ÿ����һ�����ö�ӦΪtrue��ֱ������Ϊtrue���㷨ֹͣ

    vector<bool> isInS;                  //�Ƿ��Ѿ���S�����У�S�еĵ���������i��������·����

    isInS.reserve(0);                    // ���ô�СΪ0

    isInS.assign(nVertexCount, false);   //���·���vector��С�����еĽڵ㶼����S������



    int i, j;

    // Step 1: �����i,j֮�䲻ͨ���������ڵ�ת���ľ���

    //         ��ʼ��pDistance��pPreVertex���飬��ʱ�������i->j��ͨ��������ľ���

    for (j = 0; j < nVertexCount; ++j)

    {

        // ��һ�α���ʱ�����ҵ���̾���Ϊ����֮�䲻ͨ������������̾���

        pDistance[j] = arrArcs[startVertex][j];

        if (arrArcs[startVertex][j] < MAX_DISTANCE)

            pPreVertex[j] = startVertex;  // i��j֮�����ֱ������ôj��ǰ��ڵ����i

        else

            pPreVertex[j] = -1;       // -1��ʾǰһ�ڵ�δ֪

    }

    pPreVertex[startVertex] = -1;     // ��ʼ�ڵ��ǰ��ڵ�δ֪



    // Step 2: ���i,j֮��ͨ���������ڵ�kת������̾���

    /*��ʼʹ��̰��˼��ѭ��������S�����е�ÿһ���ڵ�*/

    isInS[startVertex] = true;          //��ʼ�ڵ����S������

    int k = startVertex;                // ����м�ڵ�



    //��ʼ�ڵ��Ѿ������S���ˣ�����nVertexCount-1���ڵ�Ҫ������i��1��ʼ

    for (i = 1; i < nVertexCount; i++)

    {



        // Step 2.1 : Ѱ�Ҳ���S�����еľ���i��distance��С�Ľڵ�(���α����������)

        int nextVertex = k;

        int tempDistance = MAX_DISTANCE;

        for (j = 0; j < nVertexCount; ++j)

        {

            //Ѱ�Ҳ���S�����еľ���i��distance��С�Ľڵ�

            if ((isInS[j] == false) && (pDistance[j] < tempDistance))

            {

                nextVertex = j;

                tempDistance = pDistance[j];

            }

        }

        // ��ǣ�һ��ѭ���󣬿�������ڵ�ǰS�£�����i������Ĳ���S�еĵ㣬����������

        isInS[nextVertex] = true; //����i����Ľڵ�nextVertex����S������

        k = nextVertex;           //��һ��Ѱ�ҵĿ�ʼ�ڵ�k



        // Step 2.2 : ��S�����½ڵ�󣬼����i��j����̾��룬����distance��

        //            ��kΪ�¿��ǵ��м�㣬�����iͨ��kת������j�ľ��룬����ԭ�еĴ�iֱ�ӵ�j�ľ�����бȽϣ�ѡȡ��Сֵ

        for (j = 0; j < nVertexCount; j++)

        {

            // ������㲻��S�еĽڵ㣨��i��������S�еĽڵ�ľ�������̵ģ�

            if (isInS[j] == false && arrArcs[k][j] < MAX_DISTANCE)

            {

                if (pDistance[k] + arrArcs[k][j] < pDistance[j]) //��kΪ�¿��ǵ��м�㣬�����iͨ��kת������j�ľ���

                {

                    pDistance[j] = pDistance[k] + arrArcs[k][j];

                    pPreVertex[j] = k;

                }

            }

        }

    }

}

/************************************************************************/

/* Floyd �㷨��������нڵ�����֮������·��

*/

/*

������

    Graph * pGraph,                       ͼ�����ݽṹ

    int arrDistance[][MAX_VERTEX_COUNT],  ��̾���

    int arrPath[][MAX_VERTEX_COUNT],      ���·������

    int nVertexCount                      �ڵ���Ŀ

*/

/************************************************************************/

void Floyd(Graph* pGraph, int arrDistance[][MAX_VERTEX_COUNT], int arrPath[][MAX_VERTEX_COUNT])

{

    int i, j, k;

    int nVertexCount = pGraph->nVertexCount;

    // Step 1����ʼ��arrDistance�����arrPath����

    //     ��һ��ѭ��ʱ������i��j֮��ľ��뼴Ϊ����֮��ֱ�߾���; 

    //     ��i�����ĵ���j����һ�ڵ��ǰ��ڵ㶼��i

    for (i = 0; i < nVertexCount; ++i)

    {

        for (j = 0; j < nVertexCount; ++j)

        {

            arrDistance[i][j] = pGraph->arrArcs[i][j];

            arrPath[i][j] = i;

        }

    }

    // Step 2����̬�滮

    // Dis(i,j)Ϊ�ڵ�i���ڵ�j�����·���ľ��룬

    //      ����ÿһ���ڵ�k�����Dis(i,k) + Dis(k,j) < Dis(i,j)�Ƿ������

    //      ���������֤����i��k�ٵ�j��·����iֱ�ӵ�j��·���̣�������Dis(i,j) = Dis(i,k) + Dis(k,j)

    //      �����Ǳ��������нڵ�k��Dis(i,j)�м�¼�ı���i��j�����·���ľ���



    for (k = 0; k < nVertexCount; ++k)

    {

        for (i = 0; i < nVertexCount; ++i)

        {

            for (j = 0; j < nVertexCount; ++j)

            {

                // ����ÿһ���ڵ�k�����Dis(i,k) + Dis(k,j) < Dis(i,j)�Ƿ������

                if (arrDistance[i][k] + arrDistance[k][j] < arrDistance[i][j])

                {

                    // �ҵ�����·��

                    arrDistance[i][j] = arrDistance[i][k] + arrDistance[k][j];

                    // �洢·������ֵ

                    arrPath[i][j] = arrPath[k][j];

                }

            }

        }

    }

}
