#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class TILE {
    public:
        vector<int> LEFT;
        vector<int> RIGHT;
        vector<int> TOP;
        vector<int> BOTTOM;
        string texture_path;

        TILE(){}

        TILE(int rules) {
            this->LEFT = vector<int>(rules);
            this->RIGHT = vector<int>(rules);
            this->TOP = vector<int>(rules);
            this->BOTTOM = vector<int>(rules);
        }
};

vector<TILE> tiles;
vector<vector<vector<TILE>>> brd;

int BOARD_SIZE;
int TILE_SIZE;

RenderWindow window(VideoMode(1080, 1080), "WFC - Random Houses");

bool complete_board(int row, int col, vector<vector<vector<TILE>>> brd);

void handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            // Handle the spacebar press to generate a new pattern
            complete_board(0, 0, brd);
        }
    }
}

void drawBoard(vector<vector<vector<TILE>>> &brd) 
{

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                sf::Texture texture;
                texture.loadFromFile(brd[i][j][0].texture_path);

                sf::Sprite sprite(texture);
                sprite.setScale(static_cast<float>(TILE_SIZE) / texture.getSize().x, static_cast<float>(TILE_SIZE) / texture.getSize().y);
                sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                window.draw(sprite);

                
            }
        }
        handleEvents(window);

        window.display();
    }
}


void print_board(vector<vector<vector<TILE>>> &brd) 
{
    cout << "Board:" << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (i % 3 == 0) cout << "-------------------------" << endl;
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << "| ";
            if (brd[i][j].size() == 0) cout << "    ";
            for (int k = 0; k < brd[i][j].size(); k++)
            {
                for (int l = 0; l < brd[i][j][k].TOP.size(); l++) cout << brd[i][j][k].TOP[l] << " ";
                cout << " ";
                for (int l = 0; l < brd[i][j][k].RIGHT.size(); l++) cout << brd[i][j][k].RIGHT[l] << " ";
                cout << " ";
                for (int l = 0; l < brd[i][j][k].BOTTOM.size(); l++) cout << brd[i][j][k].BOTTOM[l] << " ";
                cout << " ";
                for (int l = 0; l < brd[i][j][k].LEFT.size(); l++) cout << brd[i][j][k].LEFT[l] << " ";
                cout << " | ";
            }
        }
    }
    cout << "-------------------------" << endl;
}


bool collapse_tile(int row, int col, TILE tile, vector<vector<vector<TILE>>> &brd) 
{
    // Remove all tiles except the collapsed one
    brd[row][col] = {tile};

    // Collapse tile on left
    if (col > 0) 
    {
        TILE curr = tile;
        for (int j = 0; j < brd[row][col-1].size(); j++)
        {
            // If not possible to place remove
            if (brd[row][col-1][j].RIGHT != tile.LEFT)
            {
                brd[row][col-1].erase(brd[row][col-1].begin() + j);
                j--;
            }
        }
        if (brd[row][col-1].size() > 0) curr = brd[row][col-1][0];
        else return false;
    }

    // Collapse tile on right
    if (col < BOARD_SIZE - 1) 
    {
        TILE curr = tile;
        for (int j = 0; j < brd[row][col+1].size(); j++)
        {
            // If not possible to place remove
            if (brd[row][col+1][j].LEFT != tile.RIGHT)
            {
                brd[row][col+1].erase(brd[row][col+1].begin() + j);
                j--;
            }
        }
        if (brd[row][col+1].size() > 0) curr = brd[row][col+1][0];
        else return false;
    }

    // Collapse tile on top
    if (row > 0) 
    {
        TILE curr = tile;
        for (int j = 0; j < brd[row-1][col].size(); j++)
        {
            // If not possible to place remove
            if (brd[row-1][col][j].BOTTOM != tile.TOP)
            {
                brd[row-1][col].erase(brd[row-1][col].begin() + j);
                j--;
            }
        }
        if (brd[row-1][col].size() > 0) curr = brd[row-1][col][0];
        else return false;
    }

    // Collapse tile on bottom
    if (row < BOARD_SIZE - 1) 
    {
        TILE curr = tile;
        for (int j = 0; j < brd[row+1][col].size(); j++)
        {
            // If not possible to place remove
            if (brd[row+1][col][j].TOP != tile.BOTTOM)
            {
                brd[row+1][col].erase(brd[row+1][col].begin() + j);
                j--;
            }
        }
        if (brd[row+1][col].size() > 0) curr = brd[row+1][col][0];
        else return false;
    }

    return true;
}

bool complete_board(int row, int col, vector<vector<vector<TILE>>> brd) 
{
    if (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1)
    {
        cout << "Board complete" << endl;
        print_board(brd);
        drawBoard(brd);
        return true;
    }
    if (col == BOARD_SIZE) row++, col = 0;

    // // Try all possible values for tile
    // for (int i = 0; i < brd[row][col].size(); i++) 
    // {
    //     TILE value = brd[row][col][i];
    //     vector<vector<vector<TILE>>> brd_copy = brd;
    //     if (collapse_tile(row, col, value, brd_copy))
    //         if (complete_board(row, col + 1, brd_copy)) return true;
    // }

    // Pick randomically tile till you find one that works
    while (brd[row][col].size() > 0) 
    {
        int i = rand() % brd[row][col].size();
        TILE value = brd[row][col][i];
        vector<vector<vector<TILE>>> brd_copy = brd;
        if (collapse_tile(row, col, value, brd_copy))
            if (complete_board(row, col + 1, brd_copy)) return true;
        brd[row][col].erase(brd[row][col].begin() + i);
    }

    // cout << "No solution found" << endl;
    return false;
}


int main()
{
    int rules;
    cout << "Enter number of rules per side: ";
    cin >> rules;

    int tiles_num;
    cout << "Enter number of tiles kinds: ";
    cin >> tiles_num;

    tiles = vector<TILE>(tiles_num);

    string folder;
    cout << "Enter texture folder name: ";
    cin >> folder;
    folder += "/";

    cout << "Enter rules for each tile:" << endl;
    for (int i = 0; i < tiles_num; i++) 
    {
        cout << "Tile " << i << ":" << endl;

        // Enter tile texture
        Texture texture;
        string texture_name;
        string texture_path = folder;
        cout << "Enter texture name: ";
        cin >> texture_name;
        texture_path += texture_name;
        texture_path += ".png";

        TILE new_tile(rules);
        new_tile.texture_path = texture_path;

        int rule;

        // Top row
        for (int k = 0; k < rules; k++) {
            cout << "Rule " << 0 << ", " << k << ": ";
            cin >> rule;
            new_tile.TOP[k] = rule;
        }
        
        // Right column
        for (int k = 0; k < rules; k++) {
            cout << "Rule " << k << ", " << rules - 1 << ": ";
            cin >> rule;
            new_tile.RIGHT[k] = rule;
        }
        
        // Bottom row
        for (int k = rules - 1; k >= 0; k--) {
            cout << "Rule " << rules - 1 << ", " << k << ": ";
            cin >> rule;
            new_tile.BOTTOM[k] = rule;
        }
        
        // Left column
        for (int k = rules - 1; k >= 0; k--) {
            cout << "Rule " << k << ", " << 0 << ": ";
            cin >> rule;
            new_tile.LEFT[k] = rule;
        }

        tiles[i] = new_tile;
    }

    // // print tiles
    // for (int i = 0; i < tiles_num; i++) 
    // {
    //     cout << "Tile " << i << ":" << endl;
    //     for (int j = 0; j < rules; j++) 
    //     {
    //         for (int k = 0; k < rules; k++) 
    //         {
    //             cout << tiles[i].tile_rules[j][k] << " ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    // Define board
    cout << "Enter square board size: ";
    cin >> BOARD_SIZE;
    TILE_SIZE = 1080 / BOARD_SIZE;

    brd = vector<vector<vector<TILE>>>(BOARD_SIZE, vector<vector<TILE>>(BOARD_SIZE));

    // Fill every cell with every tile
    for (int i = 0; i < BOARD_SIZE; i++) 
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            brd[i][j] = tiles;
        }
    }

    // // print board
    // for (int i = 0; i < BOARD_SIZE; i++) 
    // {
    //     for (int j = 0; j < BOARD_SIZE; j++) 
    //     {
    //         cout << "Cell " << i << ", " << j << ":" << endl;
    //         for (int k = 0; k < tiles_num; k++) 
    //         {
    //             cout << "Tile " << k << ":" << endl;
                
    //             // TOP
    //             for (int l = 0; l < rules; l++) cout << brd[i][j][k].TOP[l] << " ";

    //             // RIGHT
    //             for (int l = 0; l < rules; l++) cout << brd[i][j][k].RIGHT[l] << " ";

    //             // BOTTOM
    //             for (int l = 0; l < rules; l++) cout << brd[i][j][k].BOTTOM[l] << " ";

    //             // LEFT
    //             for (int l = 0; l < rules; l++) cout << brd[i][j][k].LEFT[l] << " ";

    //             cout << endl;
    //         }
    //         cout << endl;
    //     }
    // }

    // print_board(brd);
    // drawBoard(brd);

    complete_board(0, 0, brd);

    return 0;
}