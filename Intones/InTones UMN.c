#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>


int para;
struct song
{
    char title[100];
    char artist[100];
    int year;
    char album[100];
    char country[100];
    char patch[100];
    int played;
    int status;
};

struct film
{
    char title[100];
    int year;
    char country[100];
    float rating;
    int status;
};

struct playlist
{
    char title[100];
    char artist[100];
    int year;
    char album[100];
    char country[100];
    char patch[100];
    int played;
    int status;
};

struct account
{
    char name[100];
    char username[100];
    int pins;
};

struct list
{
    char name[100];
    char username[100];
    int pins;
};


int main()
{
    int n=0,m=0,i;
    struct song song[1000];
    struct film film[1000];
    struct account akun[100];
    struct list lists[1000];

    opening();
    FILE *id= fopen("Account.txt","r");
    fscanf(id,"%[^#]#%[^#]#%d",akun[0].name,akun[0].username,&akun[0].pins);
    fclose(id);

    FILE *list=fopen("List.txt","r");
    i=0;
    while(!feof(list))
    {
        fscanf(id,"%[^#]#%[^#]#%d\n",lists[i].name,lists[i].username,&lists[i].pins);
        i++;
    }
    fclose(list);

     FILE *ups= fopen("Parameter.txt","r");
    fscanf(ups,"%d",&para);
    fclose(ups);

    FILE *songs=fopen("Music.txt","r");
    while(!feof(songs))
    {
        fscanf(songs,"%[^#]#%[^#]#%d#%[^#]#%[^#]#%[^#]#%d#%d\n",song[n].title,song[n].artist,&song[n].year,song[n].album,song[n].country,song[n].patch,&song[n].played,&song[n].status);
        n++;
    }
    fclose(songs);

    FILE *films=fopen("Movie.txt","r");
    while(!feof(films))
    {
        fscanf(films,"%[^#]#%d#%[^#]#%f#%d\n",film[m].title,&film[m].year,film[m].country,&film[m].rating,&film[m].status);
        m++;
    }
    fclose(films);

    if(para==0)
        {
            inup(akun,lists,i,song,film,n,m);
            para=1;
            FILE *upp= fopen("Parameter.txt","w+");
            fprintf(upp,"%d",para);
            fclose(upp);
        }

    menu(song,film,n,m,akun);
}

void menu(struct song song[],struct film film[],int n,int m,struct account akun[])
{
    int i,j,a;
    struct song temp;
    system("cls");
    system("color F0");

    printf("\n===============================================================================");
    printf("\n\n\t\t\t\tFeatures\n\n");
    printf("\t\t\t\t\t\t\t ----------------------\n");
    printf("\t\t\t\t\t\t\t| Hello %s",akun[0].name);
    printf("\n===============================================================================\n\n");
    printf("\tHot tracks\t:\n");
    hottrack(song,n);
    printf("\n===============================================================================\n");
    printf("\t\t| Home | Music | Video | Search | My Song | My Account |\n");
    printf("\t\t|  0   |   1   |   2   |    3   |    4    |      5     |\n");
    printf("===============================================================================\n");

    for(i=-1;i<0;)
        {
            printf("Input > 5 untuk membuka Menu Extra\n");
            printf("Input :");
            scanf("%d",&i);
        }

    switch (i)
    {
        case 0: menu(song,film,n,m,akun); break;
        case 1: music(song,film,n,m,akun); break;
        case 2: video(song,film,n,m,akun); break;
        case 3: search(song,film,n,m,akun);break;
        case 4: mycoll(song,film,n,m,akun); break;
        case 5: account(song,film,n,m,akun);break;
    }
    if(i>5)
        {
            for(i=11;i>8;)
            {
                printf("Pilih lagu 1-8: ");
                scanf("%d",&i);
            }

            if(song[i-1].status==1)
                musdet(song,i-1,film,akun,n,m);
            else if(song[i-1].status==2)
                muspur(song,i-1,n,film,akun,m);
                menu(song,film,n,m,akun);
        }
}

void music(struct song song[],struct film film[],int n,int m,struct account akun[])
{
    int i,j;
    system("cls");
    system("color F0");
    printf("\n================================================================================");
    printf("\n\t\t\t\tFeatures\n\n");
    printf("\t\t\t\t\t\t\t ----------------------\n");
    printf("\t\t\t\t\t\t\t| Hello %s",akun[0].name);
    printf("\n===============================================================================\n\n");
    printf("\tThere are recommended song for you, %s\n\n",akun[0].name);
    printf("\tRecent Played\t:\n");
    recent(song,n);
    for (i=0,j=0;i<5&&song[i].played!=0;i++,j++){}
     printf("\n==============================================================================\n");
    printf("\t\t| Home | Music | Video | Search | My Song | My Account |\n");
    printf("\t\t|  0   |   1   |   2   |    3   |    4    |      5     |\n");
    printf("==============================================================================\n");

    for(i=-1;i<0;)
        {
            printf("Input > 5 untuk membuka Menu Extra\n");
            printf("Input : ");
            scanf("%d",&i);
        }
    switch (i)
    {
        case 0: menu(song,film,n,m,akun); break;
        case 1: music(song,film,n,m,akun); break;
        case 2: video(song,film,n,m,akun); break;
        case 3: search(song,film,n,m,akun);break;
        case 4: mycoll(song,film,n,m,akun); break;
        case 5: account(song,film,n,m,akun);break;
    }

    if(i>5)
        {
            for(i=6;(i>5||i>j)&&i!=0;)
            {
                printf("Pilih lagu 1-%d:             0 to show all song\n",j);
                scanf("%d",&i);
            }
            if(i==0)
                allsong(song,film,n,m,akun);

            if(song[i-1].status==1)
                musdet(song,i-1,film,akun,n,m);
            else if(song[i-1].status==2)
                muspur(song,i-1,n,film,akun,m);
                menu(song,film,n,m,akun);
        }
}

void allsong(struct song song[],struct film film[],int n,int m,struct account akun[])
{
    int i,j;
    system("cls");
    system("color F0");
    printf("\n================================================================================");
    printf("\n\t\t\t\tFeatures\n");
    printf("\n================================================================================\n");
    printf("\tAll Song\t:\n");
    for(i=0,j=1;i<n;i++,j++)
    {
        printf("\t%d.%-30s %-30s\n",j,song[i].title,song[i].artist);
    }
     printf("\n===============================================================================\n");
    printf("\t\t| Home | Music | Video | Search | My Song | My Account |\n");
    printf("\t\t|  0   |   1   |   2   |    3   |    4    |      5     |\n");
    printf("===============================================================================\n");
     for(i=-1;i<0;)
        {
            printf("Input > 5 untuk membuka Menu Extra\n");
            printf("Input : ");
            scanf("%d",&i);
        }
    switch (i)
    {
        case 0: menu(song,film,n,m,akun); break;
        case 1: music(song,film,n,m,akun); break;
        case 2: video(song,film,n,m,akun); break;
        case 3: search(song,film,n,m,akun);break;
        case 4: mycoll(song,film,n,m,akun); break;
        case 5: account(song,film,n,m,akun);break;
    }

    if(i>5)
        {
            for(i=n+1;i>n;)
            {
                printf("Pilih lagu 1-%d:        0 to back home\n",n);
                scanf("%d",&i);
            }
            if(i==0)
                menu(song,film,n,m,akun);

            if(song[i-1].status==1)
                musdet(song,i-1,film,akun,n,m);
            else if(song[i-1].status==2)
                muspur(song,i-1,n,film,akun,m);
                menu(song,film,n,m,akun);
        }
}

void video(struct song song[],struct film film[],int n,int m,struct account akun[])
{
    int i;
    system("cls");
    system("color 0F");
    printf("\n================================================================================");
    printf("\n\t\t\t\tFeatures\n\n");
    printf("\t\t\t\t\t\t\t ----------------------\n");
    printf("\t\t\t\t\t\t\t| Hello %s",akun[0].name);
    printf("\n===============================================================================\n\n");
    printf("\tThere are some new movies for you, %s\n\n",akun[0].name);
    printf("\tHot Box Office\t:\n\n\n");
    hotbox(film,m);
     printf("\n===============================================================================\n");
    printf("\t\t| Home | Music | Video | Search | My Film | My Account |\n");
    printf("\t\t|  0   |   1   |   2   |    3   |    4    |      5     |\n");
    printf("===============================================================================\n");

    for(i=-1;i<0;)
        {
            printf("Input > 5 untuk membuka Menu Extra\n");
            printf("Input : ");
            scanf("%d",&i);
        }
    switch (i)
    {
        case 0: menu(song,film,n,m,akun); break;
        case 1: music(song,film,n,m,akun); break;
        case 2: video(song,film,n,m,akun); break;
        case 3: searchfilm(song,film,n,m,akun);break;
        case 4: mycoll2(song,film,n,m,akun); break;
        case 5: account(song,film,n,m,akun);break;
    }

    if(i>5)
        {
            for(i=4;i>3&&i!=0;)
            {
                printf("Pilih Film 1-5:     0 to show all collection\n");
                scanf("%d",&i);
            }
            if (i==0)
                allvid(song,film,n,m,akun);

            if(film[i-1].status==1)
                filmdet(song,i-1,film,akun,n,m);
            else if(film[i-1].status==2)
                filmpur(song,i-1,n,film,akun,m);
        }
}

void allvid(struct song song[],struct film film[],int n,int m,struct account akun[])
{
    int i,j;
    system("cls");
    system("color 0F");
    printf("\n================================================================================");
    printf("\n\t\t\t\tFeatures\n");
    printf("\n================================================================================\n");
    printf("\tAll Movie\t:\n");
    for(i=0,j=1;i<m;i++,j++)
    {
        printf("\t%d.%-30s %-30s\n",j,film[i].title,film[i].country);
    }
     printf("\n===============================================================================\n");
    printf("\t\t| Home | Music | Video | Search | My Song | My Account |\n");
    printf("\t\t|  0   |   1   |   2   |    3   |    4    |      5     |\n");
    printf("===============================================================================\n");
     for(i=-1;i<0;)
        {
            printf("Input > 5 untuk membuka Menu Extra\n");
            printf("Input : ");
            scanf("%d",&i);
        }
    switch (i)
    {
        case 0: menu(song,film,n,m,akun); break;
        case 1: music(song,film,n,m,akun); break;
        case 2: video(song,film,n,m,akun); break;
        case 3: search(song,film,n,m,akun);break;
        case 4: mycoll(song,film,n,m,akun); break;
        case 5: account(song,film,n,m,akun);break;
    }

    if(i>5)
        {
            for(i=m+1;i>m;)
            {
                printf("Pilih Film 1-%d:            0 to back home\n",m);
                scanf("%d",&i);
            }
            if(i==0)
                menu(song,film,n,m,akun);

            if(film[i-1].status==1)
                filmdet(song,i-1,film,akun,n,m);
            else if(film[i-1].status==2)
                filmpur(song,i-1,n,film,akun,m);
        }

}

void search(struct song song[],struct film film[],int n,int m,struct account akun[])
{
    int i;
    char a[100],b;
    system("cls");
    system("color F0");
    printf("\n===============================================================================");
    printf("\n\t\t\t\tFeatures Music\n");
    printf("\n===============================================================================");
    printf("\n\tSearch by : \n");
    printf("===============================================================================\n");
    printf("\t| Title | Artist | Country |  Movie | Home |\n");
    printf("\t|   0   |    1   |    2    |    3   |   4  |\n");
    printf("===============================================================================\n");
    for(;i>5;)
    {
        printf("Choice: ");
        scanf("%d",&i);
    }
    if(i==3)
        searchfilm(song,film,n,m,akun);
    else if(i==4)
        menu(song,film,n,m,akun);
    fflush(stdin);
    printf("Keyword : ");
    scanf("%[^\n]",&a);
    searching(song,n,i,a,akun,film,m);
    fflush(stdin);
    printf("Search again? Y/N\n");
    scanf("%c",&b);
    if(b=='Y'||b=='y')
        search(song,film,n,m,akun);
    else
        menu(song,film,n,m,akun);
}

void searchfilm(struct song song[],struct film film[],int n,int m,struct account akun[])
{
    int i,z,j;
    char a[100],b;
    system("cls");
    system("color 0F");
    printf("\n===============================================================================");
    printf("\n\t\t\t\tFeatures Movie\n");
    printf("\n===============================================================================");
    printf("\n\tSearch by : \n");
    printf("===============================================================================\n");
    printf("\t| Title | Year | Country |  Music | Home |\n");
    printf("\t|   0   |   1  |    2    |    3   |   4  |\n");
    printf("===============================================================================\n");
    for(;i>5;)
    {
        printf("Choice: ");
        scanf("%d",&i);
    }
    if(i==3)
        search(song,film,n,m,akun);
    else if(i==4)
        menu(song,film,n,m,akun);
    fflush(stdin);
    printf("Keyword : ");
    if(i==1)
        {
            scanf("%d",&z);
            for(j=0,i=0;i<m;i++)
            if(z==film[i].year)
            {
                printf("%-30s %-30s %.1f\n",film[i].title,film[i].country,film[i].rating);
                j++;
            }
            if(j==0)
                printf("There's no Item With Your Keyword\n");
        }
    else
        {
            scanf("%[^\n]",&a);
            searching2(song,n,i,a,akun,film,m);
        }
    fflush(stdin);
    printf("Search again? Y/N\n");
    scanf("%c",&b);
    if(b=='Y'||b=='y')
        searchfilm(song,film,n,m,akun);
    else
        menu(song,film,n,m,akun);
}

void mycoll(struct song song[],struct film film[],int n,int m,struct account akun[])
{
    int i=0,j=0,l=1,k[100];
    system("cls");
    system("color F0");
    printf("\n===============================================================================");
    printf("\n\n\t\t\t\tMy Music\n\n");
    while(j<n)
    {
        if(song[j].status==2)
            {
                printf("\t%d.%-30s\t%s\n",l,song[j].title,song[j].artist);
                l++;
                k[i]=j;
                i++;
            }
        j++;
    }
     printf("===============================================================================\n");
    printf("\t\t| Home | Music | Video | Search | My Film | My Account |\n");
    printf("\t\t|  0   |   1   |   2   |    3   |    4    |      5     |\n");
    printf("===============================================================================\n");

    for(i=-1;i<0;)
        {
            printf("Input > 5 untuk membuka Menu Extra\n");
            printf("Input : ");
            scanf("%d",&i);
        }
    switch (i)
    {
        case 0: menu(song,film,n,m,akun); break;
        case 1: music(song,film,n,m,akun); break;
        case 2: video(song,film,n,m,akun); break;
        case 3: search(song,film,n,m,akun);break;
        case 4: mycoll2(song,film,n,m,akun); break;
        case 5: account(song,film,n,m,akun);break;
    }
    if(i>5)
        {
            for(i=l+1;i>l;)
            {
                printf("Pilih Lagu: \t0 to play all song\n");
                scanf("%d",&i);
            }
            if(i==0)
            {
                for(i=1;i<l;i++)
                    muspur1(song,k[i-1],n,film,akun,m);
                mycoll(song,film,n,m,akun);
            }
            else
                {
                    muspur(song,k[i-1],n,film,akun,m);
                    mycoll(song,film,n,m,akun);
                }
        }
}

void mycoll2(struct song song[],struct film film[],int n,int m,struct account akun[])
{
    int i=0,j=0,l=1,k[100];
    system("cls");
    system("color 0F");
    printf("\n===============================================================================");
    printf("\n\n\t\t\t\tMy Movies\n\n");
    while(j<m)
    {
        if(film[j].status==2)
            {
                printf("\t%d.%-30s\t%s\n",l,film[j].title,film[j].country);
                l++;
                k[i]=j;
                i++;
            }
        j++;
    }
     printf("===============================================================================\n");
    printf("\t\t| Home | Music | Video | Search | My Song | My Account |\n");
    printf("\t\t|  0   |   1   |   2   |    3   |    4    |      5     |\n");
    printf("===============================================================================\n");

    for(i=-1;i<0;)
        {
            printf("Input > 5 untuk membuka Menu Extra\n");
            printf("Input : ");
            scanf("%d",&i);
        }
    switch (i)
    {
        case 0: menu(song,film,n,m,akun); break;
        case 1: music(song,film,n,m,akun); break;
        case 2: video(song,film,n,m,akun); break;
        case 3: search(song,film,n,m,akun);break;
        case 4: mycoll(song,film,n,m,akun); break;
        case 5: account(song,film,n,m,akun);break;
    }
    if(i>5)
        {
            for(i=l+1;i>l;)
            {
                printf("Pilih Film: \t0 to back to menu\n");
                scanf("%d",&i);
            }
            if(i==0)
            {
                menu(song,film,n,m,akun);
            }
            else
                {
                    filmpur(song,k[i-1],n,film,akun,m);
                    mycoll2(song,film,n,m,akun);
                }
        }
}

void account(struct song song[],struct film film[],int n,int m,struct account akun[])
{
    int a,b;
    system("cls");
    system("color F0");
    printf("\n===============================================================================\n");
    printf("\n\t\t\t\tMy Account\n");
    printf("\n===============================================================================\n\n");
    printf("\tName\t\t: %s\n\n",akun[0].name);
    printf("\tUsername\t: %s\n\n",akun[0].username);
    printf("\tMethod Payment\t: Credit\n\n");
    printf("===============================================================================\n");
    printf("\t\t\t\t| Home | Log Out |\n");
    printf("\t\t\t\t|  0   |    1    |\n");
    printf("===============================================================================\n");
    fflush(stdin);
    for(b=-1;b!=0&&b!=1;)
        {
            printf("Input : ");
            scanf("%d",&b);
        }
    fflush(stdin);

    if(b==1)
    {
        a=0;
        FILE *upp= fopen("Parameter.txt","w");
        fprintf(upp,"%d",a);
        fclose(upp);
        exit(0);
    }
    else if(b==0)
        menu(song,film,n,m,akun);


}






void searching(struct song song[],int n,int i,char a[],struct account akun[],struct film film[],int m)
{

    int j,k[100],l,z;
    if(i==0)
        for(l=1,j=0,i=0;i<n;i++)
    {
        if(strcmpi(a,song[i].title)==0)
        {
            printf("%d.%-30s %-30s %s\n",l,song[i].title,song[i].artist,song[i].country);
            k[j]=i;
            j++;
            l++;
        }
    }
    else if(i==1)
        for(l=1,j=0,i=0;i<n;i++)
    {
        if(strcmpi(a,song[i].artist)==0)
        {
            printf("%d.%-30s %-30s %s\n",l,song[i].title,song[i].artist,song[i].country);
            k[j]=i;
            j++;
            l++;
        }
    }
    else if(i==2)
        for(l=1,j=0,i=0;i<n;i++)
    {
        if(strcmpi(a,song[i].country)==0)
        {
            printf("%d.%-30s %-30s %s\n",l,song[i].title,song[i].artist,song[i].country);
            k[j]=i;
            j++;
            l++;
        }
    }

    if(j==0)
        printf("There's no Item With Your Keyword\n");
    else
    {
        for(;z>j;)
        {
            printf("Choose your song..\n");
            scanf("%d",&z);
        }
        if(z==0)
        {
            printf("Search Canceled\n");
        }
        else
        {
            if(song[k[z-1]].status==1)
                musdet(song,k[z-1],film,akun,n,m);
            else if(song[k[z-1]].status==2)
                muspur(song,k[z-1],n,film,akun,m);
                menu(song,film,n,m,akun);
        }
    }
}
void searching2(struct song song[],int n,int i,char a[],struct account akun[],struct film film[],int m)
{


    int j,k[100],l,z;
    if(i==0)
        for(l=1,j=0,i=0;i<n;i++)
    {
        if(strcmpi(a,film[i].title)==0)
        {
            printf("%-30s %-30s %.1f\n",film[i].title,film[i].country,film[i].rating);
            k[j]=i;
            l++;
            j++;
        }
    }

    else if(i==2)
        for(l=1,j=0,i=0;i<n;i++)
    {
        if(strcmpi(a,film[i].country)==0)
        {
            printf("%d.%-30s %-30s %.1f\n",l,film[i].title,film[i].country,film[i].rating);
            k[j]=i;
            l++;
            j++;
        }
    }

    if(j==0)
        printf("There's no Item With Your Keyword\n");
    else
     {
        for(;z>j;)
        {
            printf("Choose your Movie..\n");
            scanf("%d",&z);
        }
        if(z==0)
        {
            printf("Search Canceled\n");
        }
        else
        {
            if(film[k[z-1]].status==1)
                filmdet(song,k[z-1],film,akun,n,m);
            else if(film[k[z-1]].status==2)
                filmpur(song,k[z-1],n,film,akun,m);
        }
    }

}




void sortlagu (struct song sort[], int n){
    int i,j;
    struct song temp;
    for (i=1;i<n;i++){

        temp = sort[i];
        j= i-1;

        while (j>= 0 && strcmp(temp.title,sort[j].title)<0){
            sort [j+1] = sort[j];
            j = j-1;
        }
        sort [j+1] = temp;
    }
    for (i=0;i<n;i++){
        printf("%-30s %-30s %s\n",sort[i].title,sort[i].artist,sort[i].country);
    }
}


void hotbox(struct film sort[],int m)/* sort film by years*/
{
    int i,j;
    struct film temp;
    for (i=1;i<m;i++)
    {
        temp = sort[i];
        j= i-1;

        while (j>= 0 && temp.year>sort[j].year){
            sort [j+1] = sort[j];
            j = j-1;
        }
        sort [j+1] = temp;
    }
        for(j=0;j<3;j++,i++)
            {
                printf("  | %-20s |",sort[j].title);
            }
            printf("\n");

        for(j=0;j<3;j++,i++)
            {
                printf("  | %-20c |",32);
            }
            printf("\n");
         for(j=0;j<3;j++,i++)
            {
                printf("  | %-20s |",sort[j].country);
            }
            printf("\n");
        for(j=0;j<3;j++,i++)
            {
                printf("  | %-20c |",32);
            }
            printf("\n");
         for(i=1,j=0;j<3;j++,i++)
            {
                printf("  | %-20d |",i);
            }
            printf("\n\n");
}

void hottrack(struct song sort[],int n) /* sort film by years*/
{
    int i,j;
    struct song temp;
    for (i=1;i<n;i++)
    {
        temp = sort[i];
        j= i-1;

        while (j>= 0 && temp.year>sort[j].year){
            sort [j+1] = sort[j];
            j = j-1;
        }
        sort [j+1] = temp;
    }

    for (i=0,j=1;i<8;i++,j++){
        printf("\t%d.%-30s %-30s\n",j,sort[i].title,sort[i].artist);
    }
}

void recent(struct song sort[],int n)
{
    int i,j;
    struct song temp;
    for (i=1;i<n;i++)
    {
        temp = sort[i];
        j= i-1;

        while (j>= 0 && temp.played>sort[j].played){
            sort [j+1] = sort[j];
            j = j-1;
        }
        sort [j+1] = temp;
    }

    for (i=0,j=1;i<5&&sort[i].played!=0;i++,j++){
        printf("\t%d.%-30s %-30s\n",j,sort[i].title,sort[i].artist);
    }
}





void filmdet(struct song song[],int i,struct film film[],struct account akun[],int n,int m)
{
    char command[100];
    system("cls");
    system("color 0F");
    int a=20000;
    int b=0;
    int c;
    char j[10];
    printf("\n================================================================================");
    printf("\n\t\t\t\tStores\n");
    printf("\n================================================================================\n");
    printf("\tTitle   : %s\n\n",film[i].title);
    printf("\tYear    : %d\n\n",film[i].year);
    printf("\tCountry : %s\n\n",film[i].country);
    printf("\tRating  : %.1f\n\n",film[i].rating);
    printf("\tPrice   : Rp%d\n\n",a);
    printf("===============================================================================\n");
    printf("\t\t| Home | Purchase |\n");
    printf("\t\t|  0   |     1    |\n");
    printf("===============================================================================\n");
    for(;strcmpi(j,"1")==1&&strcmpi(j,"0")==1;)
    {
        printf("Choice: ");
        scanf("%s",j);
    }
    if(strcmpi(j,"0")==0)
        menu(song,film,n,m,akun);
    else
        {
            purchase(a,akun,song,n,film,m);
            printf("Purchase Complete\n");
            getch();
            film[i].status=2;
            FILE *update = fopen("Movie.txt","w+");
            while(b<m)
            {
                fprintf(update,"%s#%d#%s#%.1f#%d\n",film[b].title,film[b].year,film[b].country,film[b].rating,film[b].status);
                b++;
            }
            fclose(update);
            sprintf(command,"%s2.txt",akun[0].username);
            FILE *up =fopen(command,"w+");
            for(c=0;c<m;c++)
            {
                fprintf(up,"%d#",film[c].status);
            }
            fclose(up);
            menu(song,film,n,m,akun);
        }

}

void filmpur(struct song song[],int i,int n,struct film film[],struct account akun[],int m)
{
    char j[10],k;
    int b=0;
    system("cls");
    system("color 0F");
    printf("\n================================================================================");
    printf("\n\t\t\t\tMusic\n");
    printf("\n================================================================================\n");
    printf("\tTitle   : %s\n\n",film[i].title);
    printf("\tYear    : %d\n\n",film[i].year);
    printf("\tCountry : %s\n\n",film[i].country);
    printf("\tRating  : %.1f\n\n",film[i].rating);
    printf("===============================================================================\n");
    printf("\t\t| Home |   Play   |\n");
    printf("\t\t|  0   |     1    |\n");
    printf("===============================================================================\n");
    for(strcpy(j,"3");strcmpi(j,"1")==1&&strcmpi(j,"0")==1;)
    {
        printf("Choice: ");
        scanf("%s",j);
    }
    if(strcmpi(j,"0")==0)
        menu(song,film,n,m,akun);
    else
    {
        playfilm(film,i);
    }
    getch();
    menu(song,film,n,m,akun);
}

void musdet(struct song song[],int i,struct film film[],struct account akun[],int n,int m)
{
    char command[100];
    system("cls");
    system("color F0");
    int a=7000;
    int b=0;
    int c;
    char j[10];
    printf("\n================================================================================");
    printf("\n\t\t\t\tStores\n");
    printf("\n================================================================================\n");
    printf("\tTitle   : %s\n\n",song[i].title);
    printf("\tArtist  : %s\n\n",song[i].artist);
    printf("\tAlbum   : %s\n\n",song[i].album);
    printf("\tPrice   : Rp%d\n\n",a);
    printf("===============================================================================\n");
    printf("\t\t| Home | Purchase |\n");
    printf("\t\t|  0   |     1    |\n");
    printf("===============================================================================\n");
    for(;strcmpi(j,"1")==1&&strcmpi(j,"0")==1;)
    {
        printf("Choice: ");
        scanf("%s",j);
    }
    if(strcmpi(j,"0")==0)
        menu(song,film,n,m,akun);
    else
        {
            purchase(a,akun,song,n,film,m);
            printf("Purchase Complete\n");
            getch();
            song[i].status=2;
            FILE *update = fopen("Music.txt","w+");
            while(b<n)
            {
                fprintf(update,"%s#%s#%d#%s#%s#%s#%d#%d\n",song[b].title,song[b].artist,song[b].year,song[b].album,song[b].country,song[b].patch,song[b].played,song[b].status);
                b++;
            }
            fclose(update);

            sprintf(command,"%s1.txt",akun[0].username);

            FILE *up =fopen(command,"w+");
            for(c=0;c<n;c++)
            {
                fprintf(up,"%d#",song[c].status);
            }
            fclose(up);

            menu(song,film,n,m,akun);
        }

}
void muspur(struct song song[],int i,int n,struct film film[],struct account akun[],int m)
{
    char j[10],k;
    int b=0;
    system("cls");
    system("color F0");
    printf("\n================================================================================");
    printf("\n\t\t\t\tMusic\n");
    printf("\n================================================================================\n");
    printf("\tTitle   : %s\n",song[i].title);
    printf("\tArtist  : %s\n",song[i].artist);
    printf("\tAlbum   : %s\n",song[i].album);
    printf("===============================================================================\n");
    printf("\t\t| Home |   Play   |\n");
    printf("\t\t|  0   |     1    |\n");
    printf("===============================================================================\n");
    for(strcpy(j,"3");strcmpi(j,"1")==1&&strcmpi(j,"0")==1;)
    {
        printf("Choice: ");
        scanf("%s",j);
    }
    if(strcmpi(j,"0")==0)
        menu(song,film,n,m,akun);
    else
    {
        playsong(song,i);
        song[i].played++;
        FILE *update = fopen("Music.txt","w+");
            while(b<n)
            {
                fprintf(update,"%s#%s#%d#%s#%s#%s#%d#%d\n",song[b].title,song[b].artist,song[b].year,song[b].album,song[b].country,song[b].patch,song[b].played,song[b].status);
                b++;
            }
        fclose(update);
    }
    getch();
}

void muspur1(struct song song[],int i,int n,struct film film[],struct account akun[],int m)
{
    char j,k;
    int b=0;
    int timelimit=2,g;
    system("cls");
    system("color F0");
    printf("\n================================================================================");
    printf("\n\t\t\t\tMusic\n");
    printf("\n================================================================================\n");
    printf("\tTitle   : %s\n",song[i].title);
    printf("\tArtist  : %s\n",song[i].artist);
    printf("\tAlbum   : %s\n",song[i].album);
    printf("===============================================================================\n");
    printf("\t\t|     Playing....      |\n");
    printf("\t\t|    Input 1 to stop   |\n");
    printf("===============================================================================\n");
   fflush(stdin);
    for(g = 0; g < timelimit; g++)
	{
		Sleep(1000);
		if(_kbhit())
		{
			j=getch();
		}
	}

    if(j=='1')
        menu(song,film,n,m,akun);
    else
    {
        playsong(song,i);
        song[i].played++;
        FILE *update = fopen("Music.txt","w+");
            while(b<n)
            {
                fprintf(update,"%s#%s#%d#%s#%s#%s#%d#%d\n",song[b].title,song[b].artist,song[b].year,song[b].album,song[b].country,song[b].patch,song[b].played,song[b].status);
                b++;
            }
        fclose(update);
    }
}

void purchase(int price,struct account akun[],struct song song[],int n,struct film film[],int m)
{
    int a,b,c,pin[4],d,e;
    char buy[10];
    printf("Wanna Buy This Item for Rp%d?\n",price);
    printf("Y?\n");
    printf("Press anything except Y button\n");
    scanf("%s",buy);
    if(strcmpi(buy,"y")==0)
    {
        for(e=0;d!=akun[0].pins;e++)
        {
            printf("Input PIN: ");
        for(a=0,c=1000,d=0;a<4;a++,c/=10)
        {
            pin[a]=getch();
            b=42-pin[a];
            d+=((pin[a]-48)*c);
            printf("%c",pin[a]+b);
        }
        getch();
        if(d!=akun[0].pins)
            printf("\nPIN SALAH\n");
        printf("\n");

        if(e==2)
        {   a=0;
            FILE *upp= fopen("Parameter.txt","w");
            fprintf(upp,"%d",a);
            fclose(upp);
            exit(0);

        }
        }
    }
    else
    {
        printf("Purchase Canceled");
        getch();
        menu(song,film,n,m,akun);
    }

}

void playsong(struct song song[],int i)
{
    char command[100];
    sprintf(command,"\"D:/intones/Music/%s.mp3\"",song[i].patch);
    system(command);
}

void playfilm(struct film film[],int i)
{
    char command[100];
    sprintf(command,"\"D:/intones/Movie/%s.mp4\"",film[i].title);
    system(command);
}

void opening()
{
    int i,j;
    for(i=0,j=5;i<100;i+=j,j+=5)
    {
        system("cls");
        system("color F8");
        printf("\n\n\n\n\n");
        printf("\t\t\t        ************* \n");
        printf("\t\t\t      ***************** \n");
        printf("\t\t\t     ******        ***** \n");
        printf("\t\t\t    *****  ********  **** \n");
        printf("\t\t\t   ****  ***********  **** \n");
        printf("\t\t\t  ****  ***** *******  **** \n");
        printf("\t\t\t *****  *****  ******  ***** \n");
        printf("\t\t\t *****  *****   *****  ***** \n");
        printf("\t\t\t ****    ****    ***    **** \n");
        printf("\t\t\t  ***    ****   ****    *** \n");
        printf("\t\t\t   **    ****  *****    ** \n");
        printf("\t\t\t    ********* *********** \n");
        printf("\t\t\t     ******************* \n");
        printf("\t\t\t      ***************** \n");
        printf("\t\t\t       ************** \n\n\n");

        printf("\t\t\t     Loading Database %d%%",i);
        Sleep(1000);
    }
    Sleep(1000);
}

void signin(struct account akun[],struct list list[],int i,struct song song[],struct film film[],int n,int m)
{
    char name[100],command[100];
    system("color F0");
    int pin[4],d,a,c,b;
    while(1)
    {
        system("cls");
        printf("\n================================================================================");
        printf("\n\t\t\t\tSign In\n");
        printf("\n================================================================================\n");
        printf("\tUsername     : ");
        scanf("%[^\n]",name);
        printf("\tPin          : ");
        for(a=0,c=1000,d=0;a<4;a++,c/=10)
            {
                pin[a]=getch();
                b=42-pin[a];
                d+=((pin[a]-48)*c);
                printf("%c",pin[a]+b);
            }
        for(a=0;a<i;a++)
        {
            if(strcmp(name,list[a].username)==0)
                {
                        if(d==list[a].pins)
                    {
                       strcpy(akun[0].name,list[a].name);
                       strcpy(akun[0].username,list[a].username);
                       akun[0].pins=list[a].pins;
                        break;
                    }
                }
        }
        fflush(stdin);
        if(strcmp(name,list[a].username)==0)
            if(d==list[a].pins)
            break;
    }
        sprintf(command,"%s1.txt",akun[0].username);
            FILE *up =fopen(command,"r");
            c=0;
            while(!feof(up))
                {
                    fscanf(up,"%d#",&song[c].status);
                    c++;
                }
            fclose(up);

        sprintf(command,"%s2.txt",akun[0].username);
            FILE *ups =fopen(command,"r");
            c=0;
            while(!feof(ups))
                {
                    fscanf(ups,"%d#",&film[c].status);
                    c++;
                }
            fclose(ups);

            FILE *update = fopen("Movie.txt","w+");
            c=0;
            while(c<m)
            {
                fprintf(update,"%s#%d#%s#%.1f#%d\n",film[c].title,film[c].year,film[c].country,film[c].rating,film[c].status);
                c++;
            }
            fclose(update);

            FILE *updates = fopen("Music.txt","w+");
            c=0;
            while(c<n)
            {
                fprintf(updates,"%s#%s#%d#%s#%s#%s#%d#%d\n",song[c].title,song[c].artist,song[c].year,song[c].album,song[c].country,song[c].patch,song[c].played,song[c].status);
                c++;
            }
            fclose(updates);

            FILE *akuns =fopen("Account.txt","w");
            fprintf(akuns,"%s#%s#%d",akun[0].name,akun[0].username,akun[0].pins);
            fclose(akuns);
}

void signup(struct account akun[],struct list list[],int i,struct song song[],struct film film[],int n,int m)
{
    int pin[4],d,a,c,b;
    char command[100];
    system("color F0");
    system("cls");
    printf("\n================================================================================");
    printf("\n\t\t\t\tSign Up\n");
    printf("\n================================================================================\n");
    printf("\tName         : ");
    scanf("%[^\n]",akun[0].name);
    fflush(stdin);
    printf("\tUsername     : ");
    scanf("%[^\n]",akun[0].username);
    printf("\tPin          : ");
    for(a=0,c=1000,d=0;a<4;a++,c/=10)
            {
                pin[a]=getch();
                b=42-pin[a];
                d+=((pin[a]-48)*c);
                printf("%c",pin[a]+b);
            }
    akun[0].pins=d;

    FILE *akuns =fopen("Account.txt","w");
    fprintf(akuns,"%s#%s#%d",akun[0].name,akun[0].username,akun[0].pins);
    fclose(akuns);

     sprintf(command,"%s1.txt",akun[0].username);
            FILE *up =fopen(command,"w");
            for(i=0;i<n;i++)
            {
                song[i].status=1;
                fprintf(up,"%d#",song[i].status);
            }
            fclose(up);

        sprintf(command,"%s2.txt",akun[0].username);
            FILE *ups =fopen(command,"w");
            for(i=0;i<m;i++)
            {
                film[i].status=1;
                fprintf(ups,"%d#",film[i].status);
            }
            fclose(ups);

            FILE *update = fopen("Movie.txt","w+");
            c=0;
            while(c<m)
            {
                fprintf(update,"%s#%d#%s#%.1f#%d\n",film[c].title,film[c].year,film[c].country,film[c].rating,film[c].status);
                c++;
            }
            fclose(update);

            FILE *updates = fopen("Music.txt","w+");
            c=0;
            while(c<n)
            {
                fprintf(updates,"%s#%s#%d#%s#%s#%s#%d#%d\n",song[c].title,song[c].artist,song[c].year,song[c].album,song[c].country,song[c].patch,song[c].played,song[c].status);
                c++;
            }
            fclose(updates);


     FILE *listing =fopen("List.txt","a");
    fprintf(listing,"%s#%s#%d\n",akun[0].name,akun[0].username,akun[0].pins);
    fclose(listing);

}

void inup(struct account akun[],struct list lists[],int i,struct song song[],struct film film[],int n,int m)
{
    char a;
    system("cls");
    system("color F0");
    printf("\n\t\t\t Welcome To the InTones\n\n");
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    printf("\t\t\t| Sign In  |   Sign Up  |\n");
    printf("\t\t\t|    1     |      2     |\n");
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
    for(;a!='1'&&a!='2';)
    {
        printf("\tInput : ");
        scanf("%c",&a);
        fflush(stdin);
    }
    if(a=='1')
        signin(akun,lists,i,song,film,n,m);
    else if(a=='2')
        signup(akun,lists,i,song,film,n,m);
}


