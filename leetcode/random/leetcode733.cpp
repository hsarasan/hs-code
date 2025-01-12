/*
An image is represented by an m x n integer grid image where image[i][j] represents the pixel value of the image.

You are also given three integers sr, sc, and color. You should perform a flood fill on the image starting from the pixel image[sr][sc].

To perform a flood fill, consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color), and so on. Replace the color of all of the aforementioned pixels with color.

Return the modified image after performing the flood fill.
*/

class Solution {
    std::queue<std::pair<int,int>> Q;
    std::map < std::pair<int,int>,bool>  visited;

    void doWork(vector<vector<int>>& image, int row, int col, int source_color, int dest_color){
        int M=image.size();
        int N=image[0].size();
        if (row<0 || row>=M) return;
        if (col<0 || col>=N) return;
        std::pair<int,int> cell{row,col};
        if (image[row][col]==source_color){
            Q.push(cell);
            image[row][col]=dest_color;
        }
    }
public:
    void colorNeighbours(vector<vector<int>>& image, int sr, int sc, int source_color, int dest_color){
        visited[{sr,sc}]=true;
        doWork(image,sr-1,sc,source_color,dest_color);
        doWork(image,sr+1,sc,source_color,dest_color);
        doWork(image,sr,sc-1,source_color,dest_color);
        doWork(image,sr,sc+1,source_color,dest_color);

    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int initialColor = image[sr][sc];
        image[sr][sc]=color;
        colorNeighbours(image,sr,sc,initialColor,color);
        while (!Q.empty()){
            auto p=Q.front();
            Q.pop();
            if (!visited[p]){
                visited[p]=true;
                colorNeighbours(image,p.first,p.second,initialColor,color);
            }
        }
        return image;
    }
};