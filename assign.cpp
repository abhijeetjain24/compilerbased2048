#include<iostream>
#include<map>
#include<vector>
#include<string>
#include"assign.h"
#include"assignment.tab.hpp"
using namespace std;
int matrix[4][4]={0}; //maintains the values of the tiles on matrix
map<pair<int,int>,vector<string> > tile_names;
int flag;
int yylex();
void fill_left()
{
        for(int i=0;i<4;i++)
        {
                for(int j=0;j<4;j++)
                {
                        if(!matrix[i][j])
                        {
                                for(int k=j+1;k<4;k++)
                                {
                                        if(matrix[i][k])
                                        {       
                                                pair<int,int> temp=make_pair(i,k);
                                                pair<int,int>t1=make_pair(i,j);
                                                tile_names[t1]=tile_names[temp];
                                                tile_names[temp].clear();
                                                matrix[i][j]=matrix[i][k];
                                                matrix[i][k]=0;
                                                break;
                                        }
                                }
                        }

                }
        }
}
void fill_right()
{
        for(int i=0;i<4;i++)
	{
                for(int j=3;j>=0;j--)
                {
                        if(!matrix[i][j])
                        {
                                for(int k=j-1;k>=0;k--)
                                {      
                                        if(matrix[i][k])
                                        {
                                                pair<int,int> temp=make_pair(i,k);
                                                pair<int,int>t1=make_pair(i,j);
                                                tile_names[t1]=tile_names[temp];
                                                tile_names[temp].clear();
                                                matrix[i][j]=matrix[i][k];
                                                matrix[i][k]=0;
                                                break;
                                        }
                                }
                        }

                }
        }
}
void fill_down()
{
        for(int i=0;i<4;i++)
        {
                for(int j=3;j>=0;j--)
                {
                        if(!matrix[j][i])
                        {
                                for(int k=j-1;k>=0;k--)
                                {       if(matrix[k][i])
                                        {
                                                pair<int,int> temp=make_pair(k,i);
                                                pair<int,int>t1=make_pair(j,i);
                                                tile_names[t1]=tile_names[temp];
                                                tile_names[temp].clear();
                                                matrix[j][i]=matrix[k][i];
                                                matrix[k][i]=0;
                                                break;
                                        }
                                }
                        }

                }
        }
}
void fill_up()
{
        for(int i=0;i<4;i++)
        {       for(int j=0;j<4;j++)
                {
                        if(!matrix[j][i])
                        {
                                for(int k=j+1;k<4;k++)
                                {       if(matrix[k][i]!=0)
                                        {
                                                pair<int,int> temp=make_pair(k,i);
                                                pair<int,int>t1=make_pair(j,i);
                                                tile_names[t1]=tile_names[temp];
                                                tile_names[temp].clear();
                                                matrix[j][i]=matrix[k][i];
                                                matrix[k][i]=0;
                                                break;
                                        }
                                }
                        }

                }
        }
}
int random_index(int x)
{
    int t1;
    t1=rand()%x+0;

return t1;
}
void update_tile_names(pair<int,int> start,pair<int,int> end)
{
        for(int ij=0;ij<tile_names[start].size();ij++)
        {
                tile_names[end].push_back(tile_names[start][ij]);
        }
        tile_names[start].clear();
}
int Do_move(int operation,int direction)
{
        if(direction==1)
        {
                fill_left();
                for(int i=0;i<4;i++)
                {       for(int j=0;j<3;j++)
                        {
                                if(matrix[i][j]&&matrix[i][j]==matrix[i][j+1])
                                {       
                                        pair<int,int> temp=make_pair(i,j+1);
                                        pair<int,int> t1=make_pair(i,j);
                                        update_tile_names(temp,t1);              
                                        if(operation==6)
                                                tile_names[t1].clear();
                                        if(operation==5)
                                                {matrix[i][j]+=matrix[i][j+1];cout<<"1\n";}
                                        else if(operation==7)
                                                matrix[i][j]*=matrix[i][j+1];
                                        else if(operation==8)
                                                matrix[i][j]/=matrix[i][j+1];
                                        else
                                                matrix[i][j]-=matrix[i][j+1];
                                        matrix[i][j+1]=0;
                                }
                        }
                }
                fill_left();
                insert_random_tile();
                cout<<"Thanks, left move done, random tile added\nThe current state is:\n";
                return 0;
        }
        else if(direction==2)
        {
                fill_right();
                for(int i=0;i<4;i++)
                {       for(int j=3;j>0;j--)
                        {
                                if(matrix[i][j]&&matrix[i][j]==matrix[i][j-1])
                                {       
                                        pair<int,int> temp=make_pair(i,j-1);
                                        pair<int,int> t1=make_pair(i,j);
                                        update_tile_names(temp,t1);
                                        if(operation==6)
                                                tile_names[t1].clear();
                                        if(operation==5)
                                                matrix[i][j]+=matrix[i][j-1];
                                        else if(operation==7)
                                                matrix[i][j]*=matrix[i][j-1];
                                        else if(operation==8)
                                                matrix[i][j]/=matrix[i][j-1];
                                        else
                                                matrix[i][j]-=matrix[i][j-1];
                                        matrix[i][j-1]=0;
                                }
                        }
                }
                fill_right();
                insert_random_tile();
                cout<<"Thanks, right move done, random tile added\nThe current state is:\n";
                return 0;
        }
        else if(direction==4)
        {
                fill_down();
                for(int i=0;i<4;i++)
                {       for(int j=0;j<3;j++)
                        {
                                if(matrix[j][i]&&matrix[j][i]==matrix[j+1][i])
                                {       
                                        pair<int,int> temp=make_pair(j+1,i);
                                        pair<int,int> t1=make_pair(j,i);
                                        update_tile_names(temp,t1);
                                        if(operation==6)
                                                tile_names[t1].clear();
                                        if(operation==5)
                                                matrix[j][i]+=matrix[j+1][i];
                                        else if(operation==7)
                                                matrix[j][i]*=matrix[j+1][i];
                                        else if(operation==8)
                                                matrix[j][i]/=matrix[j+1][i];
                                        else
                                                matrix[j][i]-=matrix[j+1][i];
                                        matrix[j+1][i]=0;
                                }
                        }
                }
                fill_down();
                insert_random_tile();
                cout<<"Thanks, down move done, random tile added\nThe current state is:\n";
                return 0;
        }
        else
        {
                fill_up();
                for(int i=0;i<4;i++)
                {       for(int j=3;j>0;j--)
                        {
                                if(matrix[j][i]&&matrix[j][i]==matrix[j-1][i])
                                {       
                                        pair<int,int> temp=make_pair(j-1,i);
                                        pair<int,int> t1=make_pair(j,i);
                                        update_tile_names(temp,t1);
                                        if(operation==6)
                                                tile_names[t1].clear();
                                        if(operation==5)
                                                matrix[j][i]+=matrix[j-1][i];
                                        else if(operation==7)
                                                matrix[j][i]*=matrix[j-1][i];
                                        else if(operation==8)
                                                matrix[j][i]/=matrix[j-1][i];
                                        else
                                                matrix[j][i]-=matrix[j-1][i];
                                        matrix[j-1][i]=0;
                                }
                        }
                }
                fill_up();
                insert_random_tile();
                cout<<"Thanks, up move done, random tile added\nThe current state is:\n";
                return 0;
        }
        return 0;

}
int set_name(string* name1,int x,int y)
{
        string name = *name1;
        cout<<"name\n\n\n";
        free(name1);
        int flag=0;
        if(!matrix[x-1][y-1])
        {
                cout<<"Name being assigned to empty tile\nEnter Next Command:\n\n";
                return 1;
        }
        for(int i=0;i<4;i++)
        {
                for(int j=0;j<4;j++)
                {
                        pair<int,int> t1=make_pair(i,j);
                        for(int k=0;k<tile_names[t1].size();k++)
                        {
                                if(tile_names[t1][k]==name)
                                {
                                        flag=1;
                                        break;
                                }
                        }
                        if(flag==1)
                                break;
                }
        }
        if(flag==1)
        {
                cout<<"Name already exists\nEnter Next Command:\n";
                return 1;

        }
        if(x<=4 && y<=4 && x>0 && y>0)
        {       
                if(matrix[x-1][y-1])
                {
                tile_names[make_pair(x-1,y-1)].push_back(name);
                cout<<"Thanks, naming done.\n Current state is:\n";
                return 0;
                }
                else
                {
                        cout<<"Name being assigned to empty tile\nEnter Next Command:\n\n";
                        return 1;
                }
        }
        return -5;
}
int get_value(int x,int y)
{
        if(x<=4 && y<=4 && x>0 && y>0)
        {
                if(matrix[x-1][y-1])
                {cout<<"Value is:        ";
                cout<<matrix[x-1][y-1]<<"\n";
                cout<<"Current state is:\n";
                return 0;
                }
                else
                        cout<<"Tile is empty\nCurrent state is:\n";
        }
        return -5;
}
int assign_value(int value,int x,int y)
{
        if(x<=4 && y<=4 && x>0 && y>0)
        {
                matrix[x-1][y-1]=value;
                cout<<"Thanks, Assignment Done\n Current State is:\n";
                return 0;
        }
        return -5;
}
int assign_value_1()
{
    
    return -4;
}
int insert_random_tile()
{
        int i,j,k;
        int flg=0;
        for(int ij=0;ij<4;ij++)
        {
                for(int jk=0;jk<4;jk++)
                {
                        if(!matrix[ij][jk])
                                flg=1;
                }
        }
        if(flg==0)
                return 1;
        do
        {
                i=random_index(4);
                j=random_index(4);
                k=random_index(4);

        }while(matrix[i][j]);		
        
                
        if(k==1)
                matrix[i][j]=4;
        else
                matrix[i][j]=2;

        return 0;
        
}
int print_output(int error_code)
{
    flag=0;
        if(error_code==0)
        {
               
                cout<<" ";
                for(int j=0;j<4;j++)
                {
                        
                                printf("_ _ _ _ _");
                } 
                cout<<"\n\n";
                for(int i=0;i<4;i++)
                {
                        cout<<"|";

                        for(int j=0;j<4;j++)
                        {
                                if(matrix[i][j])
                                        printf("%4d    |",matrix[i][j]);
                                else
                                        printf("        |");
                        } 

                        cout<<endl;
                        cout<<" ";
                        for(int j=0;j<4;j++)
                        {
                                
                                        printf("_ _ _ _ _");
                        } 
                        cout<<"\n\n";
                }
                cout<<"\n";
                for(auto u:tile_names)
                {
                        if(u.second.size()>0)
                        {
                                cout<<u.first.first+1<<" "<<u.first.second+1<<"\n";
                                for(int i=0;i<u.second.size();i++)
                                {
                                        cout<<u.second[i]<<" ";
                                }
                                cout<<"\n";
                        }
                }
                cout<<"\n\nENTER NEXT COMMAND\n";
        }
        else if(error_code==-5)
        {
                
                cout<<"There is no tile like that. The tile co-ordinates must be in the range 1,2,3,4\n\nENTER NEXT COMMAND\n";
        }
        else if(error_code==-4)
        {
            cout<<"Syntax error.\n\nENTER NEXT COMMAND\n";
        }
        else if(error_code==1)
        {
                cout<<"\n";
        }
        else
        {
                printf("-1\n\nENTER NEXT COMMAND\n");
        }
        return 0;
}
void initialize()
{
       
        insert_random_tile();
        cout<<"The start state is:\n";
        print_output(0);
        cout<<"\nEnter command\n";
        return;
}
int main()
{
         initialize();

         while(1)
         {
                
                 yyparse();
                
         }

         return 0;
}