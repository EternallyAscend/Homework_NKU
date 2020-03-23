/*
快速路改造工程
Total number of submissions: 619 timespassing number: 29 timesPassing rate: 4.68%

Memory limit: 134217728(BYTE)Time limit: 10000(MS)Input limit: 1000(ROWS)Output limit: 64(ROWS)

Problem description
某地区在经过城镇交通道路调查后，得到了现有的城镇间道路的统计数据，现决定对该地区的的道路进行升级改造，实现任何两个城镇之间都可以有快速路接通（不一定是直接的快速路相连）。给出了所有可能建设成快速路的道路改造成本，求快速路改造需要的最低成本。
输入：

第一行给出城镇数目N（1<N ≤  100）,和道路数目M ≤3N,随后给出M行，每行给出3个正整数，分别是该条道路直接连通的两个城镇的编号（从1到N）以及该条道路改造的成本。

输出：

输出道路改造的最低成本。如果输入的数据不足以保证任何两个城镇之间都可以有快速路接通，则输出“Impossible”。



Annex

Sample of Input and Output
样例1
Input:
4 4
1 2 6
1 3 4
1 4 5
4 2 3
Output:
12
样例2
Input:
5 4
1 2 1
2 3 2
3 1 3
4 5 4
Output:
Impossible
*/
