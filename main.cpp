#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

class user
{
    public:

    int number_of_movements = 0;
    int wall_hits = 0;
};

class maze_manager
{
    public:

    bool unlocked[3] = {true, true, true};

    // h = Hall (open for walking)
    // w = Wall (unpassable)
    // s = Start (where you are)
    // f = Finish (where you are heading)

    //Level 1
    string one[12] =
    {
        "wwwwwwwwwww",
        "whhhhhhhhhw",
        "whwwwwwwhww",
        "wwhhhhhwhww",
        "whwwwhwhhhw",
        "whhhhhhhwhw",
        "wwwwwwwhhww",
        "whwfwhwwhww",
        "whhhhhwhhsw",
        "wwhwwhwhwww",
        "whhhwhhhhww",
        "wwwwwwwwwww"
    };

    //Level 2
    string two[16] =
    {
        "wwwwwwwwwwwwwww",
        "wwwswwhhhhhwwhw",
        "whhhhhhwwwhhhhw",
        "whwwwwhhhwhwhww",
        "whhhhwwwwwwwhhw",
        "wwwwhhhhhhhwwww",
        "wwhwhwhwhwhhhhw",
        "whhwhwwwhwwwwhw",
        "wwhhhhwhhhwhhhw",
        "wwwhwhhhwhwhwhw",
        "wwhhwwwwwhwhwhw",
        "wwhwwhhhwwwhwww",
        "wwhwwhwhhhhhwfw",
        "whhhwhwwhwwwwhw",
        "wwwhwhwhhhhhhhw",
        "wwwwwwwwwwwwwww"
    };

    //Level 3
    string three[14] = 
    {
        "wwwwwwwwwwwwwwwwwwwwwwwwwwww",
        "wwwhwhhhhhwhhhhhhhwhhhwwhhhw",
        "wwhhhhwhwhhhwwwhwhwwhwhhhwhw",
        "wwhwhwwhwwhwhhhhwhhhhhhwhwhw",
        "wwhwhhhwhhhhhwwhwhwhwwhhhhhw",
        "wwhwwwhwhwhwwhhhhwhhhhwhwhww",
        "wshhhhhhhwhhhhwwhhhwwhhhwwfw",
        "whwwwwwhwwwwwhhwwhwhwwwwhwhw",
        "whhhhhhwhhhhhwhwhwwhhhhhhwhw",
        "wwhwhwhhhwhwwhhhhhhhwhwwhhhw",
        "whhhhhwwhwhhwhwhwhwwhhhhhwhw",
        "wwwhwwwhhhwhwwwhwhhhhwwhwhhw",
        "wwhhhhhhwhhhwhhhwwhwhhhhhhww",
        "wwwwwwwwwwwwwwwwwwwwwwwwwwww"
    };

    //Level 4
    string four[24] =
    {
        "wwwwwwwwwwwwwwwww",
        "wwhhhhhhhhhhhhhhw",
        "whwhwwwwhwhwhwwhw",
        "whhhhhhwhwhwhhhhw",
        "whwwwwhhwhhhwhwhw",
        "whhwhwwhhwwhhhhww",
        "wwhwhhhwhhwhwwhww",
        "wwhwhwwwwhhhwhhhw",
        "wwhhhwhhhwwhhwwhw",
        "whwhwwhwhhhwwwhhw",
        "whhhhhswhwhhhwwhw",
        "wwwwhwwhwhhwhhhww",
        "wwhwhhhhwwwhwhwhw",
        "whhhhwhwhhhhwhhhw",
        "wwwhwwhhhwhwwwwww",
        "whwhhwhwhwwhhhhww",
        "whhwhwwwhhhhwwhhw",
        "wwhwhhhwhwwhhhwhw",
        "whhwhwhwwwhhwhhww",
        "wwhhhwwwhhhwwwhhw",
        "whhwhhhwwwhhhhwhw",
        "wwwwhwhhhwhwwhwhw",
        "wwhhhhwwwhhhwhfww",
        "wwwwwwwwwwwwwwwww"
    };

    int selector();
    string* builder(int);
    int size(int);
};

int maze_manager::selector()
{
    int selected = -1;

    if(unlocked[0]) cout << "1. First Steps" << endl;
    else cout << "1. [Locked]" << endl;

    if(unlocked[1]) cout << "2. Level 2" << endl;
    else cout << "2. [Locked]" << endl;

    if(unlocked[2]) cout << "3. Level 3" << endl;
    else cout << "3. [Locked]" << endl;

    if(unlocked[3]) cout << "4. Level 4" << endl;
    else cout << "4. [Locked]" << endl;

    cout << "0. Exit" << endl;

    while(selected < 0 or selected > 3)
    {
        cout << "Write the number of the maze you want to play: ";
        cin >> selected;
    }
    cout << endl;

    return selected;
}

string* maze_manager::builder(int selected)
{
    switch(selected)
    {
        case 1: return one;
        case 2: if(unlocked[1]) return two;
        case 3: if(unlocked[2]) return three;
        case 4: if(unlocked[3]) return four;
    }
    return NULL;
}

int maze_manager::size(int maze_number)
{
    switch(maze_number)
    {
        case 1: return 12;
        case 2: return 16;
        case 3: return 14;
        case 4: return 24;
    }
    return NULL;
}

int main()
{
    user player;
    maze_manager mm;

    int selected_maze = -1;

    while(true)
    {
        selected_maze = mm.selector();
        if(selected_maze == 0) break;
        string* maze = mm.builder(selected_maze);

        int starting_file = -1;
        int starting_row = -1;

        int file_number = mm.size(selected_maze);
        int row_number = maze[0].size();

        int number_of_movements = 0;
        int wall_hits = 0;

        for(int file_index = 0; file_index < file_number; file_index++)
        {
            for(int row_index = 0; row_index < row_number; row_index++)
            {
                if(maze[file_index][row_index] == 's')
                {
                    starting_file = file_index;
                    starting_row = row_index;
                    break;
                }
            }
        }

        int current_file = starting_file;
        int current_row = starting_row;
        char command = '0';

        while(maze[current_file][current_row] != 'f')
        {
            cout << "  " << maze[current_file - 1][current_row] << endl;
            cout << maze[current_file][current_row - 1] << ' ' << maze[current_file][current_row] << ' ' << maze[current_file][current_row + 1] << endl;
            cout << "  " << maze[current_file + 1][current_row] << endl;
            while(command != 'w' and command != 'a' and command != 's' and command != 'd')
            {
                cout << "Write WASD for movement: ";
                cin >> command;
                command = tolower(command);
            }

            switch(command)
            {
                case 'w':
                    if(maze[current_file - 1][current_row] == 'w')
                    {
                        cout << "You have hit a wall!" << endl;
                        wall_hits++;
                        break;
                    } 
                    else
                    {
                        current_file -= 1;
                        break;
                    } 
                case 'a':
                    if(maze[current_file][current_row - 1] == 'w')
                    {
                        cout << "You have hit a wall!" << endl;
                        wall_hits++;
                        break;
                    } 
                    else
                    {
                        current_row -= 1;
                        break;
                    } 
                case 's':
                    if(maze[current_file + 1][current_row] == 'w')
                    {
                        cout << "You have hit a wall!" << endl;
                        wall_hits++;
                        break;
                    } 
                    else
                    {
                        current_file += 1;
                        break;
                    } 
                case 'd':
                    if(maze[current_file][current_row + 1] == 'w')
                    {
                        cout << "You have hit a wall!" << endl;
                        wall_hits++;
                        break;
                    } 
                    else
                    {
                        current_row += 1;
                        break;
                    } 
            }

            cout << endl;
            number_of_movements++;
            command = '0';
        }

        cout << "Congratulations! You have won" << endl;
        cout << "It took you just " << number_of_movements << " movements" << endl;
        cout << "And you hit the wall " << wall_hits << " times" << endl;
        cout << endl;

        player.number_of_movements += number_of_movements;
        player.wall_hits += wall_hits;

        mm.unlocked[selected_maze] = true;
    }

    cout << "Thanks for playing the game!" << endl;
    cout << "It took you just " << player.number_of_movements << " movements" << endl;
    cout << "And you hit the wall " << player.wall_hits << " times" << endl;

    return 0;
}