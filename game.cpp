#include<iostream>
#include<ctime>
#include<unistd.h>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<vector>
#include<stack>
using namespace std;

int random_index(int);
char temp123;
int score1;
int maxscorre;
int sum_matrix;
class Game;
class game_logic
{

  int cur_game_state;
  int break_game_signal;
  char key_pressed;
  
public:
  
  int max;
  int max_score;
  int delta_score;
  int score;
  int matrix[4][4];
  int prevoius_matrix[4][4];
   
  game_logic(): score(0),delta_score(0),max_score(2048),max(0),cur_game_state(0),break_game_signal(1) {}//default constructor
  
   int matrix_filled();
   int matrix_sum();
  int game_stop();
 	void spawn();
  void max_tile();
  void undo_matrix();
  void undo();
   void main_implementation(Game*);
  void gamestatecheck(Game* );
  void key_press();
  void game_start();
  void update();
  void fill();
 
};

class Game : public game_logic
{
  char option_choice;
  string player_name;
 
  
public:
	void losingscreen();
  char playagain(int);
  void print_matrix();
  void winningscreen();
 

};
//to display grid after each and every key press
void Game::print_matrix()
{
	
			
		cout<<"\n\n Controls\t\tu - undo\tr - restart\n\n\tW\t\tq - quit\n\t\t\t\t\t\t\t\t\t"
		    <<" \n   A    S    D\t\t"
		    <<" \n ";
		
				cout<<"change in score="<<delta_score;
				cout<<"\t\t\t\t\tSCORE::"<<score<<" \n\n\n\n";
				
				cout<<"\t\t\t\t\t\tHIGHEST SCORE::"<<maxscorre<<" \n\n\n\n";
				
			
			for(int i=0;i<4;i++)
				{
				cout<<"\t\t     |";

					for(int j=0;j<4;j++)
					{
						if(matrix[i][j])
							printf("%4d    |",matrix[i][j]);
						else
							printf("        |");
					} 

				cout<<endl<<endl;
				}
				

		if( !(game_stop()) && !matrix_filled() && (temp123=='w' ||temp123=='a'||temp123=='s'||temp123=='d'))// to check wheter that move causes any change in matrix or not
		{
		  	cout<<"\n\n\t\t       The move is not valid at the moment\n";
		  	
		}
		if(temp123!='w' && temp123!='a' && temp123!='s' && temp123!='d' && temp123!='u' &&temp123!='r' &&temp123!='q' && score)
		{
		cout<<"\n\n\t\t\t invalid key press\n";

		}
		

		
}
void game_logic::key_press()
{
 
  cin>>key_pressed;
}
 
int random_index(int x)
{
    int t1;
    t1=rand()%x+0;

return t1;
}

void game_logic::main_implementation(Game *execute)
{
  
 	
temp123=key_pressed;
     if(key_pressed=='w' || key_pressed=='a' ||  key_pressed=='s' || key_pressed=='d')
     {
		  execute->undo_matrix();
		  execute->fill();
		  execute->update();
		  execute->fill();
		  execute->max_tile();
		
		  usleep(1000*130);

		  if(execute->matrix_filled()&&break_game_signal)
		  {
		      cur_game_state=-1;
		  }
		  else if(execute->game_stop())
		  {
		      execute->spawn();
		  }
		  else if( !(execute->game_stop()) && !execute->matrix_filled())
		  {
		  	cur_game_state=0;
		  }
		  else
		  {
		      cur_game_state=0;	
		  }
	}
	else if(key_pressed=='u')
	{
		  if(execute->game_stop())//check wheter the last move even did any changed or not
		  {
		    score-=delta_score;
		}
		  execute->undo();
		  
	}
	else if(key_pressed=='r')//restart the game
	{
		 execute->game_start();
		  score=0;
		  delta_score=0;
		 
	}
	else if(key_pressed=='q')//quiting at the same moment irrespctive of the current situation of the matrix
	{
		cur_game_state=-1;
		  
	}			  
	else
	{
		
		execute->print_matrix();	
	}
	sum_matrix=execute->matrix_sum();
	if(sum_matrix==8)
		cur_game_state=-1;

	
}

void game_logic::game_start()//method to intialize starting 4*4 matrix
{
	 delta_score=0;
	 score=0;
	 max=0;
	for(int i=0;i<4;i++)	
		for(int j=0;j<4;j++)
			matrix[i][j]=0;

	int t1,t2;
	t1=random_index(4);//at start we dont have to consider case of occupancy since entire matrix is unoccupied
	t2=random_index(4);
		matrix[t1][t2]=2;

	int t3,t4;	
		do
		{
		    t3=random_index(4);
		    t4=random_index(4);
		}while(matrix[t3][t4]);// since one tile is occupied so as to make sure than in case rand function generates same index it do not display one tile at start
		matrix[t3][t4]=2;
}



void game_logic::undo_matrix()
{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				prevoius_matrix[i][j]=matrix[i][j];
			}
		}
}

		
void game_logic::fill()
{

	switch(key_pressed)
	{
		case 'a':
					for(int i=0;i<4;i++)
						for(int j=0;j<4;j++)
						{
							if(!matrix[i][j])
							{
								for(int k=j+1;k<4;k++)
									if(matrix[i][k])
									{
										matrix[i][j]=matrix[i][k];
										matrix[i][k]=0;
										break;
									}
							}

						}break;


		case 'd':
					for(int i=0;i<4;i++)
						for(int j=3;j>=0;j--)
						{
							if(!matrix[i][j])
							{
								for(int k=j-1;k>=0;k--)
									if(matrix[i][k])
									{
										matrix[i][j]=matrix[i][k];
										matrix[i][k]=0;
										break;
									}
							}

						}break; 

	
		case 'w':
					for(int i=0;i<4;i++)
						for(int j=0;j<4;j++)
						{
							if(!matrix[j][i])
							{
								for(int k=j+1;k<4;k++)
									if(matrix[k][i]!=0)
									{
										matrix[j][i]=matrix[k][i];
										matrix[k][i]=0;
										break;
									}
							}

						}break;

		case 's':
					for(int i=0;i<4;i++)
						for(int j=3;j>=0;j--)
						{
							if(!matrix[j][i])
							{
								for(int k=j-1;k>=0;k--)
									if(matrix[k][i])
									{
										matrix[j][i]=matrix[k][i];
										matrix[k][i]=0;
										break;
									}
							}

						}break;
					}
		
}


void game_logic::update()
{
	delta_score=0;
	break_game_signal=1;

	switch(key_pressed)
	{
		
		case 'a':
        for(int i=0;i<4;i++)
            for(int j=0;j<3;j++)
            {
                if(matrix[i][j]&&matrix[i][j]==matrix[i][j+1])
                {
                    break_game_signal=0;
                    matrix[i][j]+=matrix[i][j+1];
                    matrix[i][j+1]=0;
                    delta_score+=((log2(matrix[i][j]))-1)*matrix[i][j];
                    score+=((log2(matrix[i][j]))-1)*matrix[i][j];
                    if(score>maxscorre)
                    maxscorre=score;
                }
            }break;

		case 'd':
        for(int i=0;i<4;i++)
            for(int j=3;j>0;j--)
            {
                if(matrix[i][j]&&matrix[i][j]==matrix[i][j-1])
                {
                    break_game_signal=0;
                    matrix[i][j]+=matrix[i][j-1];
                    matrix[i][j-1]=0;
                    delta_score+=((log2(matrix[i][j]))-1)*matrix[i][j];
                    score+=(((log2(matrix[i][j]))-1)*matrix[i][j]);
                    if(score>maxscorre)
                    maxscorre=score;
                }
            }break;

            case 'w':
        for(int i=0;i<4;i++)
            for(int j=0;j<3;j++)
            {
                if(matrix[j][i]&&matrix[j][i]==matrix[j+1][i])
                {
                    break_game_signal=0;
                    matrix[j][i]+=matrix[j+1][i];
                    matrix[j+1][i]=0;
                    delta_score+=(((log2(matrix[j][i]))-1)*matrix[j][i]);//standard formula
                    score+=(((log2(matrix[j][i]))-1)*matrix[j][i]);
                    if(score>maxscorre)
                    maxscorre=score;
                    
                }
            }break;

		case 's':
        for(int i=0;i<4;i++)
            for(int j=3;j>0;j--)
            {
                if(matrix[j][i]&&matrix[j][i]==matrix[j-1][i])
                {
                    break_game_signal=0;
                    matrix[j][i]+=matrix[j-1][i];
                    matrix[j-1][i]=0;
                    delta_score+=(((log2(matrix[j][i]))-1)*matrix[j][i]);
                    score+=(((log2(matrix[j][i]))-1)*matrix[j][i]);
                     if(score>maxscorre)
                    maxscorre=score;
                }
            }break;

	}
		if(break_game_signal!=0)
		{
	 		for(int i=0;i<4;i++)
	 		{
	            for(int j=0;j<3;j++)
	            {
	                if(matrix[j][i]&&matrix[j][i]==matrix[j+1][i])
	                {
	                    break_game_signal=0;
	                }
	            }
        	}
        	for(int i=0;i<4;i++)
        	{
	            for(int j=0;j<3;j++)
	            {
	                if(matrix[i][j]&&matrix[i][j]==matrix[i][j+1])
	                {
	                    break_game_signal=0;
	                }
	            }
       		}
       		for(int i=0;i<4;i++)
       		{
	            for(int j=3;j>0;j--)
	            {
	                if(matrix[j][i]&&matrix[j][i]==matrix[j-1][i])
	                {
	                    break_game_signal=0;
	                }
	            }
        	}
        	for(int i=0;i<4;i++)
        	{
	            for(int j=3;j>0;j--)
	            {
	                if(matrix[i][j]&&matrix[i][j]==matrix[i][j-1])
	                {
	                    break_game_signal=0;
	                }
	            }
        	}
        }	

}
void game_logic::spawn()
{
		int i,j,k;
		
		do
		{
		    i=random_index(4);
		    j=random_index(4);
		    k=random_index(2);

		}while(matrix[i][j]);
				
		
			
		if(k==1)
		    matrix[i][j]=4;

		else
		    matrix[i][j]=2;
	

}
		
		
void game_logic::max_tile()
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(matrix[i][j]>max)
				max=matrix[i][j];
}

int game_logic::matrix_filled()
{
	int k=1;

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			if(!matrix[i][j])
				k=0;
				
		}
return k;
}


void game_logic::gamestatecheck(Game *screen)
{
  if(max==max_score)
  {
    screen->winningscreen();
    
    if(screen->playagain(0)=='n')
	cur_game_state=-1;
    else
	max_score*=2;
  }
  else if(cur_game_state==-1)
  {
  	screen->print_matrix();
    screen->losingscreen
   ();
  
    if(screen->playagain(1)=='y')
    {
	screen->game_start();
	cur_game_state=0;
    }
  }
    
  if(cur_game_state==-1)
  {
    cout<<"\n\n\t\t             Thank you for playing. "
        <<" \n\n";
  
    exit(0);
  }
}


void Game::winningscreen()
{
	
	
	cout<<endl<<endl;
	cout<<"\n\t\t\t  :: [  YOU MADE "<<max_score<<"!  ] ::" << "\n\n\t\t\t  :: [ YOU WON THE GAME ] ::"
	    <<"\n\n\n\n\t\t\t TILE\t     SCORE\t    player name";
	printf("\n\n\t\t\t %4d\t    %6d\t    ",max,score);
	cin>>player_name;
}

void Game::losingscreen()
{
	
	
	cout<<"\n\n\n\t\t\t   G A M E  O V E R "
	    <<"\n\n\n\n\t\t\t TILE\t     SCORE\t    player name";
	printf("\n\n\t\t\t %4d\t    %6d\t    ",max,score);
	cin>>player_name;
}

char Game::playagain(int lose)
{	
	if(lose)
	cout<<"\n\n\n\t    > Would you like to try again "<<player_name<<" (y/n) ?  ";
	else
	cout<<"\n\n\n\t    > Would you like to continue playing "<<player_name<<" (y/n) ?  ";
	
	
	cin>>option_choice;
	
	
return option_choice;
}
  
void game_logic::undo()
{
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				matrix[i][j]=prevoius_matrix[i][j];
}

int game_logic::game_stop()
{
	int k=0;

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(prevoius_matrix[i][j]!=matrix[i][j])
			{	
				k=1;
				break;
			}
return k;
}
int game_logic::matrix_sum()
{
	int temp=0;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			temp=temp+matrix[i][j];
		}
	}
	return temp;
}
int main()
{
  Game game_main;//object of the game to be played
  
  srand(time(NULL));//generate random number according to the time clock of the system

  game_main.game_start();// intializing the start matrix and all other variables
  maxscorre=0;
  sum_matrix=0;
    while(1)
    {

      game_main.print_matrix();
      if(sum_matrix>8)
      {	game_main.undo();
      	 game_main.print_matrix();
      }
      game_main.key_press();
      game_main.main_implementation(&game_main);//passing the object created with all conte
      game_main.gamestatecheck(&game_main); 

    };
    
return 0;
}

	