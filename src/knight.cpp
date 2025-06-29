#include "knight.h"
#include <algorithm>
#include <cmath>

using namespace std;

/* -------- minKnightMoves -------- */
int minKnightMoves(const Pos& start, const Pos& target) {
    /*
     * TODO: Implement BFS to find minimum knight moves
     *
     * Algorithm Steps:
     * 1. Handle edge case: if start == target, return 0
     * 2. Initialize BFS queue with start position and distance 0
     * 3. Use unordered_set to track visited positions
     * 4. For each position in queue:
     *    - Generate all 8 possible knight moves
     *    - Check if any move reaches the target
     *    - Add unvisited valid moves to queue
     * 5. Return distance when target is found
     *
     * Knight Moves (8 possibilities):
     * - (+2, +1), (+2, -1), (-2, +1), (-2, -1)
     * - (+1, +2), (+1, -2), (-1, +2), (-1, -2)
     *
     * Requirements:
     * - Use BFS for shortest path guarantee
     * - Handle infinite board (no bounds checking needed)
     * - Return minimum number of moves
     * - Optimize for negative coordinates (knight can move to negative positions)
     */

    // TODO: Implement BFS algorithm here


    if(start == target)
    {
        return 0;
    }

    int distance = 1;
    queue<Pos> PositionQ;
    PositionQ.push(start);
    vector<vector<int>> possiblemoves = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    unordered_set<Pos, PosHash> visited;
    visited.insert(start);

    while(!PositionQ.empty())
    {

        int size = PositionQ.size();

        for(int i = 0; i < size; i++)
        {
            Pos initialpos = PositionQ.front();
            PositionQ.pop();
            int PMS = possiblemoves.size();

            for(int j = 0; j < PMS; j++)
            {
                Pos currentpos = {initialpos.row + possiblemoves[j][0], initialpos.col + possiblemoves[j][1]};

                if(currentpos == target)
                {
                    return distance;
                }else if(visited.find(currentpos) == visited.end())
                {
                    visited.insert(currentpos);
                    PositionQ.push(currentpos);
                }
            }
        }

        distance++;
    }

    return -1;
}

/* -------- getKnightPath -------- */
vector<Pos> getKnightPath(const Pos& start, const Pos& target) {
    /*
     * TODO: Implement BFS with path reconstruction
     *
     * Algorithm Steps:
     * 1. Handle edge case: if start == target, return {start}
     * 2. Initialize BFS queue with start position
     * 3. Use unordered_map to track parent positions for path reconstruction
     * 4. Use unordered_set to track visited positions
     * 5. For each position in queue:
     *    - Generate all 8 possible knight moves
     *    - If move reaches target, reconstruct path and return
     *    - Add unvisited valid moves to queue with parent tracking
     * 6. Reconstruct path by following parent pointers from target to start
     * 7. Reverse path to get start-to-target order
     *
     * Path Reconstruction:
     * - Store parent[child] = parent mapping during BFS
     * - Start from target and follow parents back to start
     * - Reverse the resulting path
     *
     * Requirements:
     * - Return complete path including start and target
     * - Path should be optimal (shortest)
     * - Handle edge cases gracefully
     */

    // TODO: Implement BFS with path tracking here
    if(start == target)
    {
        return {start};
    }


    queue<Pos> PositionQ;
    PositionQ.push(start);
    vector<vector<int>> possiblemoves = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    unordered_map<Pos, Pos, PosHash> parent;
    parent[start] = start;
    unordered_set<Pos, PosHash> visited;
    visited.insert(start);

    while (!PositionQ.empty())
    {
        int size = PositionQ.size();

        for (int i = 0; i < size; i++)
        {
            Pos initialpos = PositionQ.front();
            PositionQ.pop();

            for (const auto& move : possiblemoves)
            {
                Pos currentpos = {
                    initialpos.row + move[0],
                    initialpos.col + move[1]
                };

                if (visited.find(currentpos) == visited.end())
                {
                    parent[currentpos] = initialpos;
                    visited.insert(currentpos);
                    PositionQ.push(currentpos);

                    if (currentpos == target)
                    {
                        vector<Pos> path;
                        path.push_back(target);
                        while (path.back() != start)
                        {
                            path.push_back(parent[path.back()]);
                        }
                        reverse(path.begin(), path.end());
                        return path;
                    }
                }
            }
        }
    }

    return {};

}

/* -------- isValidPosition -------- */
bool isValidPosition(const Pos& pos, int boardSize) {

    if (boardSize == -1) {
        return true;
    }
    return pos.row >= 0 && pos.row < boardSize &&
           pos.col >= 0 && pos.col < boardSize;
}

