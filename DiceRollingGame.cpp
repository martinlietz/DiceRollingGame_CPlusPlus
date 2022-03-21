#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <chrono>
#include <thread>

#include "Player.cpp"


class DiceRollingGame
    {
        public:
        int running = 0;

        int numberPlayers = 2;
        int numberRounds = 5;
        //list<list<string>> lstReplay = new();
        //list<Player> players = new List<Player>();

        std::string defaultNames[5] = { "A", "B", "C", "D", "E" };
        std::vector<std::string> history;

        Player players[5];
        //Random rnd = new();
        int noDefaultPlayers = 2;
        int noDefaultRounds = 5;

        int rolld6()
        {
            srand(time(NULL));
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            return rand() % 6 + 1;
        }
        /// <summary>
        /// This method starts the game and define the players and rounds
        /// 
        /// </summary>
        void start(){
            std::cout << "How many players we have?(2-5) default is ";
            std::cout << noDefaultPlayers;
            std::cout << std::endl;
            std::string strPlayers;
            std::getline(std::cin, strPlayers);
            if(strPlayers.empty())
                    strPlayers = std::to_string(noDefaultPlayers);
            
            numberPlayers = stoi(strPlayers);
            if(numberPlayers==0 || numberPlayers==10) 
                    numberPlayers = noDefaultPlayers;
            
            while(!(numberPlayers > 1 & numberPlayers < 6))
            {
                std::cout << "How many players we have?(2-5) default is ";
                std::cout << noDefaultPlayers;
                std::cout << std::endl;
                std::getline(std::cin, strPlayers);
                numberPlayers = stoi(strPlayers);
            }
            std::cout << numberPlayers << std::endl;
            for (int i = 0; i < 5; i++)
            {
                players[i].active = false;
            }
            for (int i = 0; i < numberPlayers; i++)
            {
                std::string namePlayer;
                std::cout << "Player " << (i+1) << " , what is your short name(max. 3 chars only) default " << defaultNames[i] << "?" << std::endl;
                std::getline(std::cin, strPlayers);
                if(namePlayer.empty())
                    namePlayer = defaultNames[i];
                
                players[i].shortname = namePlayer;
                players[i].active = true;
            }
            
            std::cout << "How many rounds we play?(2-10) default is ";
            std::cout << noDefaultRounds;
            std::cout << std::endl;
            std::string strRounds;
            std::getline(std::cin, strRounds);
            if(strRounds.empty())
                    strRounds = std::to_string(noDefaultRounds);
            
            numberRounds = stoi(strRounds);
            while(!(numberRounds  > 1 & numberRounds  < 10))
            {
                std::cout << "How many rounds we play?(2-10) default is ";
                std::cout << noDefaultRounds;
                std::cout << std::endl;
                std::getline(std::cin, strRounds);
                numberRounds = stoi(strRounds);
            }
            running = 1;
            std::cout << numberRounds << std::endl;
        }
        /// <summary>
        /// This method init the game
        /// 
        /// </summary>
        void play(){
        int n = numberRounds;
        for(int i = 0;i < n;i++)
        {
            for(int x = 0;x < 5;x++)
            {
                Player* player = &players[x];
                //in case we got no winner only the two winners compete,the rest will be inactive
                if(player->active == true)
                {
                    history.push_back("Round " + std::to_string(i+1));
                    std::cout << "Round ";
                    std::cout << (i+1);
                    std::cout << std::endl;
                    history.push_back("Player " + player->shortname + " now rolling");
                    std::cout << "Player " + player->shortname + " now rolling" << std::endl;
                    int rnd1 = 0;
                    int rnd2 = 0;
                        while(rnd1 == rnd2)
                        {
                            history.push_back("Roll?");
                            std::cout << "Roll? (Press ENTER)" << std::endl;
                            rnd1 = rolld6();
                            
                            std::string strDummy;
                            std::getline(std::cin, strDummy);
                            for (int x=0;x<10;x++)
                            {
                                std::cout << "\r" << "|"<< std::flush;
                                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                                std::cout << "\r" << "/"<< std::flush;
                                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                                std::cout << "\r" << "-"<< std::flush;
                                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                                std::cout << "\r" << "\\"<< std::flush;
                                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                                
                            }
                            rnd2 = rolld6();
                            std::cout << std::endl;
                            player->gameScore += rnd1;
                            player->gameScore += rnd2;
                            history.push_back("Player " + player->shortname + "  your dices are " + std::to_string(rnd1) + " and " + std::to_string(rnd2) + " your running total is " + std::to_string(player->gameScore));
                            std::cout << "Player " + player->shortname + "  your dices are " + std::to_string(rnd1) + " and " + std::to_string(rnd2) + " your running total is " + std::to_string(player->gameScore) << std::endl;
                            std::cout << std::endl;
                            if (rnd1 == rnd2)
                            {
                                std::cout << "Double! you can roll again!" << std::endl;
                                history.push_back("Double! you can roll again!");
                            }
                        }
                        if(i==(n-1) & player->shortname == players[numberPlayers-1].shortname)
                        {
                            Player winner = checkWinner();
                            if (winner.shortname == "")
                            {
                                //Still no winner lets do one more run.
                                std::cout << "Still no winner lets do one more run." << std::endl;
                                history.push_back("Still no winner lets do one more run.");
                                n += 1;
                            }
                            else
                            {
                                history.push_back("---------------------------");
                                std::cout << "---------------------------"<< std::endl;
                                std::cout << "And the winner is:" << std::endl;
                                history.push_back("And the winner is:");
                                for (int x=0;x<10;x++)
                                {
                                    std::cout << "\r" << "|"<< std::flush;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                                    std::cout << "\r" << "/"<< std::flush;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                                    std::cout << "\r" << "-"<< std::flush;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                                    std::cout << "\r" << "\\"<< std::flush;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                                    
                                }
                                std::cout << std::endl;
                                history.push_back("Player " + winner.shortname + " with running total " + to_string(winner.gameScore));
                                std::cout << "Player " << winner.shortname << "with running total "<< winner.gameScore << std::endl;
                                history.push_back("---------------------------");
                                std::cout << "---------------------------"<< std::endl;
                                
                                stop();
                            }
                        }
                } 
            }
        }
        std::cout << numberRounds << std::endl;
        stop();
        }
        /// <summary>
        /// This method stops the game and define what to do next
        /// 
        /// </summary>
        void stop(){
            char nChoose;
            bool valid;
            std::cout << "End of the game!"<< std::endl << std::endl;
            std::cout << "Choose one of the following options:"<< std::endl;
            std::cout << "a. Play another game."<< std::endl;
            std::cout << "b. Play back the game just completed."<< std::endl;
            std::cout << "c. Quit the game."<< std::endl;
            std::cin >> nChoose;
            while(!(nChoose == 'a' | nChoose == 'b' | nChoose == 'c'))
            {
                std::cout << "Choose one of the following options:"<< std::endl;
                std::cout << "a. Play another game."<< std::endl;
                std::cout << "b. Play back the game just completed."<< std::endl;
                std::cout << "c. Quit the game."<< std::endl;
                std::cin >> nChoose;
            }
            switch (nChoose)
                    {
                        case 'a':
                            playagain();
                            valid=true;
                            break;
                        case 'b':
                            replay();
                            std::cout << "Choose one of the following options:"<< std::endl;
                            std::cout << "a. Play another game."<< std::endl;
                            std::cout << "b. Play back the game just completed."<< std::endl;
                            std::cout << "c. Quit the game."<< std::endl;
                            std::cin >> nChoose;
                            break;
                        case 'c':
                            std::cout << "Was nice to play with you, bye!";
                            running = 0;
                            valid = true;
                            break;
                        default:
                            break;
                    }
        }
        /// <summary>
        /// This method checks who is the winner, if two have the same score we return null 
        /// and we add another round
        /// 
        /// </summary>
        Player checkWinner(){
            int maxValue = 0;
            int nWinner = 0;
            Player winner;
            Player nullPlayer;
            for(int x = 0;x < 5;x++)
            {
                Player player = players[x];
                //in case we got no winner only the two winners compete,the rest will be inactive
                if(player.active == true)
                {
                    if(player.gameScore > maxValue)
                    {
                        maxValue = player.gameScore;
                        winner = player;
                    }
                }
            }
            for(int x = 0;x < 5;x++)
            {
                Player player = players[x];
                //in case we got no winner only the two winners compete,the rest will be inactive
                if(player.active == true)
                {
                    if(player.gameScore == maxValue)
                    {
                        nWinner += 1;
                    }
                    else
                    {
                        player.active=false;
                    }
                }
            }
            if(nWinner>1){
                return nullPlayer;
            }
            else
            {
                return winner;
            }
             
        }
        /// <summary>
        /// This method starts the game over 
        /// but replaces the defaults by the previous game
        /// 
        /// </summary>
        void playagain(){
            //setDefaults to previous game values
            noDefaultPlayers = numberPlayers;
            noDefaultRounds = numberRounds;
            //and play again
            start();
            while (running == 1)
            {
                play();
            }
             
        }
        /// <summary>
        /// This method replay the last game
        /// 
        /// </summary>
        void replay(){
            for(int i = 0; i < history.size(); i++)
            {
                cout << history[i] << endl;
                if (history[i] == "Roll?")
                {
                    cout << "Next section click ENTER" << endl;
                    std::string strDummy;
                    std::getline(std::cin, strDummy);
                    for (int x=0;x<10;x++)
                    {
                        std::cout << "\r" << "|"<< std::flush;
                        std::this_thread::sleep_for(std::chrono::milliseconds(50));
                        std::cout << "\r" << "/"<< std::flush;
                        std::this_thread::sleep_for(std::chrono::milliseconds(50));
                        std::cout << "\r" << "-"<< std::flush;
                        std::this_thread::sleep_for(std::chrono::milliseconds(50));
                        std::cout << "\r" << "\\"<< std::flush;
                        std::this_thread::sleep_for(std::chrono::milliseconds(50));
                        
                    }
                    std::cout << std::endl;
                }
            }
              
        }
    };
