/*
 * 1. This Program is Developed Solely by Myself: Yes
 * 2. Student ID: 107000119
 * 3. OJ ID: 107000119chou
 * 4. OJ SID: 2159490
 * 5. OJ Score: 10
 */

#include <iostream>
using namespace std;
struct Block {
    int width;
    int height;
    int **block; // the shape of it
    bool used;
};

Block puzzle;
int num_block;
Block arr_block[1000];

/*void PrintPuzzle() {
    cout<<"--Print--\n";
    for (int i=0; i<puzzle.height; i++) {
        for (int j=0; j<puzzle.width; j++) {
            cout<<puzzle.block[i][j]<<' ';
        }
        cout<<endl;
    }
}*/
bool PutBlock(int y, int x, Block block) {

    // check bound
    if (y + block.height-1 >= puzzle.height || x + block.width-1 >= puzzle.width) return false;
    // check position
    for (int i=0; i<block.height; i++) {
        for (int j=0; j<block.width; j++) {
                if (puzzle.block[y+i][x+j]==2 && block.block[i][j]==1) return false;
                if (puzzle.block[y+i][x+j]==0 && block.block[i][j]==1) return false;
        }
    }
    for (int i=0; i<block.height; i++) {
        for (int j=0; j<block.width; j++) {
                puzzle.block[y+i][x+j] += block.block[i][j];
        }
    }
    return true;

}
void RemoveBlock(int y, int x, Block block) {
    for (int i=0; i<block.height; i++) {
        for (int j=0; j<block.width; j++) {
            if (y+i<puzzle.height && x+j<puzzle.width)
                puzzle.block[y+i][x+j] -= block.block[i][j];
        }
    }
}
bool SolvePuzzle() {
    int pw = puzzle.width;
    int ph = puzzle.height;
    for (int i=0; i<ph; i++) {
        for (int j=0; j<pw; j++) {
            if (puzzle.block[i][j] != 2) {
                for (int k=0; k<num_block; k++) {
                    if (!arr_block[k].used) {
                        if (PutBlock(i, j, arr_block[k])) {
                            arr_block[k].used = true;
                            if (SolvePuzzle()) return true;
                            else {
                                arr_block[k].used = false;
                                RemoveBlock(i, j, arr_block[k]);
                            }
                        }

                    }
                }

            }
        }
    }


    // check
    // finish means there is no 1

    for (int i=0; i<ph; i++) {
        for (int j=0; j<pw; j++) {
            if (puzzle.block[i][j]==1) return false;
        }
    }
    return true;

}
int main() {

    // freopen("in.in", "r", stdin);
    int num_puz;
    cin>>num_block;

    for (int i=0; i<num_block; i++) {
        int w, h;
        cin>>w>>h;

        arr_block[i].width = w;
        arr_block[i].height = h;
        arr_block[i].used = false;

        // create the 2d array
        arr_block[i].block = new int*[h];
        for (int j=0; j<h; j++) {
            arr_block[i].block[j] = new int[w];
        }

        for (int j=0; j<h; j++) {
            for (int k=0; k<w; k++) {
                char c;
                cin>>c;
                if (c=='-') arr_block[i].block[j][k] = 0;
                else arr_block[i].block[j][k] = 1;
            }
        }

    }

    cin>>num_puz;
    for (int i=0; i<num_puz; i++) {
        int w, h;
        cin>>w>>h;

        puzzle.width = w;
        puzzle.height = h;
        // create the 2d array
        puzzle.block = new int*[h];
        for (int j=0; j<h; j++) {
            puzzle.block[j] = new int[w];
        }
        // initial block !!!!!!!!1
        for (int i=0; i<num_block; i++) {
            arr_block[i].used = false;
        }

        for (int j=0; j<h; j++) {
            for (int k=0; k<w; k++) {
                char c;
                cin>>c;
                if (c=='O') puzzle.block[j][k] = 0;
                else puzzle.block[j][k] = 1;
            }
        }


        bool ans = SolvePuzzle();
        if (ans) cout<<"Yes\n";
        else cout<<"No\n";

    }


}
