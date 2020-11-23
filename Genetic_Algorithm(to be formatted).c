/*
1 2 6
1 3 9
1 4 8
1 5 5
2 3 9
2 4 2
2 5 4
3 4 1
3 5 8
4 5 3
*/


#include <stdio.h>
#include <limits.h>
#include<stdbool.h>
#include <math.h>
#include <stdlib.h>


int pop_size = 10;
int ver;
int nodes;
int graph[50][50];

int count = 1;
int map[100];

char chromo[50];

/////////////////////////////////////////////////////////////


struct individual
{
    char gnome[100];
    int fitness;
};


/////////////////////////////////////////////////////////////////


int rand_num(int start,int end)
{
    int r = end - start;
    int rnum = start + (rand() % r);
    return rnum;
}

//////////////////////////////////////////////////////////
void create_gnome()
{

    char gnome[100];
    gnome[0]='1';
    for(int i = 0; i<=nodes; i++)map[i]=0;
    count = 1;
    while(true)
    {
        if(count == nodes)
        {
            gnome[nodes]=gnome[0];
            gnome[nodes+1]='\0';
            break;
        }

        int temp = rand_num(2,nodes+1);
        printf("temp=%d\n",temp);
        if(map[temp]==0)
        {
            map[temp]=temp;
            gnome[count]=(char)(temp+48);
            count++;
        }
    }

    for(int i=0;i<=nodes;i++)chromo[i]=gnome[i];
}






///////////////////////////////////////////////////////////////////////



int cal_fitness(char gnome[])
{

    int f = 0;
    //int graph[v][v] = { { 0, 2, INT_MAX, 12, 5 }, { 2, 0, 4, 8, INT_MAX }, { INT_MAX, 4, 0, 3, 3 }, { 12, 8, 3, 0, 10 }, { 5, INT_MAX, 3, 10, 0 } };

    for (int i = 0; i <=(nodes - 1) ; i++)
    {
        if (graph[gnome[i] - 48][gnome[i + 1] - 48] == INT_MAX)
        {
            return INT_MAX;
        }

        f += graph[gnome[i] - 48][gnome[i + 1] - 48];
    }

    return f;
}



///////////////////////////////////////////////////////////////////////////////



void mutatedGene(char gnome[])
{
    while(true)
    {
        int r = rand_num(1,nodes);
        int r1 = rand_num(1,nodes);
        if(r1 !=r)
        {
            char temp = gnome[r];
            gnome [r] = gnome[r1];
            gnome [r1] = temp;
            break;
        }
    }

    for(int i=0;i<=nodes;i++)chromo[i]=gnome[i];
}

//////////////////////////////////////////////////////////////////////////////////////////



int cooldown(int temp)
{
    return (90 * temp) / 100;
}

///////////////////////////////////////////////////////////////////////////////////////////





void Tsputil()
{

    int gen = 1;
    struct individual population[pop_size+1];
    struct individual temp;


    for(int i = 0; i<pop_size; i++)
    {
        create_gnome();
        printf("i=%d\n",i);
        for(int j=0;j<=nodes;j++)
        {
            temp.gnome[j]=chromo[j];
            printf("%c",temp.gnome[j]);
        }

        //printf("\nHELLLLLLLLLLOOO END \n");
        temp.fitness = cal_fitness(temp.gnome);
        printf(" %d",temp.fitness);
        printf("\n");
        population[i] = temp;
        printf("PRINT POPULATION\n");
        for(int j=0;j<=nodes;j++)
        {
         printf("%c",population[i].gnome[j]);
        }
        printf("\n");

    }


    printf("initial population");
    printf("GNOME FITNESS VALUE\n");

    for(int i = 0; i<pop_size; i++)
    {
        for(int j=0;j<nodes;j++)
        {
         printf("%c",population[i].gnome[j]);
        }
        printf(" %d\n",population[i].fitness);

    }


    bool found = false;
    int temperature = 10000;

    int generations=22;

    while (generations>0)
        {
        //sort(population.begin(), population.end(), lessthan);
        //cout << "\nCurrent temp: " << temperature << "\n";
        printf("\nCurrent temp:%d\n",temperature);
        struct individual new_population[pop_size+1];

        int index=0;
        for (int i = 0; i < pop_size; i++)
            {
            struct individual p1 = population[i];

            while (true)
                {
                mutatedGene(p1.gnome);
                struct individual new_gnome;
                for(int k=0;k<=nodes;k++)new_gnome.gnome[k]=chromo[k];
                new_gnome.fitness = cal_fitness(new_gnome.gnome);

                if (new_gnome.fitness <= population[i].fitness)
                {
                    new_population[index]=(new_gnome);
                    index++;
                    break;
                }
                else
                    {

                    // Accepting the rejected children at
                    // a possible probablity above threshold.

                    float prob = pow(2.7, -1 * ((float)(new_gnome.fitness - population[i].fitness) / 100));


                    if (prob > 0.5) {
                        new_population[index]=(new_gnome);
                        index++;
                        break;
                    }
                }
            }
        }

        for(int s=0;s<pop_size;s++)
        {
            population[s].fitness=new_population[s].fitness;
            for(int g=0;g<=nodes;g++)
            {
                population[s].gnome[g]=new_population[s].gnome[g];
            }
        }


       // cout << "Generation " << gen << " \n";
        //cout << "GNOME     FITNESS VALUE\n";
        printf("AFTER MUTATION\n");
        printf("generation %d\n",gen);
        printf("GNOME     FITNESS VALUE \n");

        for(int i=0;i<pop_size;i++)
        {
            for(int j=0;j<=nodes;j++)
            {
                printf("%c",population[i].gnome[j]);
            }
            printf("\t");
            printf("%d\n",population[i].fitness);
        }


        gen++;
        generations--;
    }
}

///////////////////////////////////////////////////////////////////



int main()
{
    int x ,y;
    scanf("%ldd",&nodes);
    for(x=1; x<=nodes; x++)
    {
        for(y=x+1; y<=nodes; y++)
        {
            int g=rand_num(1,10);
            printf("%d %d %d\n",x,y,g);
            graph[x][y]=g;
            graph[y][x]=g;
        }
    }


    Tsputil();
    return 0;
}


