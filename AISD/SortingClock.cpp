#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <bits/stdc++.h>
#include <math.h> 
using namespace std;
void BUBBLE_SORT_RISING (int tab[],int n)
{
	 for(int i=0;i<n;i++)
        for(int j=0;j<n-i;j++) 
        if(tab[j]>tab[j+1])
        	swap(tab[j], tab[j+1]);
}
void BUBBLE_SORT_FALLING (int tab[],int n)
{
	 for(int i=0;i<n;i++)
        for(int j=0;j<n-i;j++) 
        if(tab[j]<tab[j+1])
        	swap(tab[j], tab[j+1]);
}
void QUICK_SORT_RISING (int tab[],int lewy,int prawy)
{
	if(prawy<lewy)
		return;
	int i=lewy-1,j=prawy+1,
	pivot=tab[(lewy+prawy)/2];
	while(1)
	{
		while (pivot>tab[++i]);
		while (pivot<tab[--j]);
		if(i<=j)
			swap(tab[i],tab[j]);
		else
			break;
	}
	if (j>lewy)
		QUICK_SORT_RISING(tab,lewy,j);
	if(i<prawy)
		QUICK_SORT_RISING(tab,i,prawy);
}
void QUICK_SORT_FALLING (int tab[],int lewy,int prawy)
{
	if(prawy<lewy)
		return;
	int i=lewy-1,j=prawy+1,
	pivot=tab[(lewy+prawy)/2];
	while(1)
	{
		while (pivot<tab[++i]);
		while (pivot>tab[--j]);
		if(i<=j)
			swap(tab[i],tab[j]);
		else
			break;
	}
	if (j>lewy)
		QUICK_SORT_FALLING(tab,lewy,j);
	if(i<prawy)
		QUICK_SORT_FALLING(tab,i,prawy);
}
void STOOGE_SORT_RISING (int tab[],int i,int j)
{
	if (tab[i]>tab[j])
		swap(tab[i],tab[j]);
	if ((i+1)>=j)
		return;
	long long k=floor((j-i+1)/3);
	STOOGE_SORT_RISING(tab,i,j-k);
	STOOGE_SORT_RISING(tab,i+k,j);
	STOOGE_SORT_RISING(tab,i,j-k);
}
void STOOGE_SORT_FALLING (int tab[],int i,int j)
{
	if (tab[i]<tab[j])
		swap(tab[i],tab[j]);
	if ((i+1)>=j)
		return;
	long long k=floor((j-i+1)/3);
	STOOGE_SORT_FALLING(tab,i,j-k);
	STOOGE_SORT_FALLING(tab,i+k,j);
	STOOGE_SORT_FALLING(tab,i,j-k);
}
int main ()
{
	time_t start,stop,start2,stop2,start3,stop3,start4,stop4,start5,stop5,start6,stop6,start7,stop7,start8,stop8,start9,stop9;
	srand(time(0));
	double czas1,czas2,czas3,czas4,czas5,czas6,czas7,czas8;
	int rozmiar=100000,tab[rozmiar],tab2[rozmiar],tab3[rozmiar];
    for( int i=0;i<rozmiar;i++)
        {
        	tab[i]=rand()%100+1;
		};
	for (int i=0;i<rozmiar;i++)
		{
			tab2[i]=tab[i];
		}
	for (int i=0;i<rozmiar;i++)
		{
			tab3[i]=tab[i];
		}
	start=clock();
	BUBBLE_SORT_RISING(tab,rozmiar);
	stop=clock();
	czas1=stop-start;
	czas1=(double)czas1/CLOCKS_PER_SEC;
	cout<<"BUBBLE_SORT_RISING_FROM_RANDOM TIME 100000 ARRAY:\t"<<fixed<<setprecision(20)<<czas1;
	cout<<"\n";
	start2=clock();
	QUICK_SORT_RISING(tab2,0,(rozmiar-1));
	stop2=clock();
	czas2=stop2-start2;
	czas2=(double)czas2/CLOCKS_PER_SEC;
	cout<<"QUICK_SORT_RISING_FROM_RANDOM TIME 100000 ARRAY:\t"<<fixed<<setprecision(20)<<czas2;
	cout<<"\n";
	start4=clock();
	BUBBLE_SORT_FALLING(tab,rozmiar);
	stop4=clock();
	czas4=stop4-start4;
	czas4=(double)czas4/CLOCKS_PER_SEC;
	cout<<"BUBBLE_SORT_RISING_TO_FALLING TIME 100000 ARRAY:\t"<<fixed<<setprecision(20)<<czas4;
	cout<<"\n";
	start5=clock();
	QUICK_SORT_FALLING(tab2,0,(rozmiar-1));
	stop5=clock();
	czas5=stop5-start5;
	czas5=(double)czas5/CLOCKS_PER_SEC;
	cout<<"QUICK_SORT_RISING_TO_FALLING TIME 100000 ARRAY:\t"<<fixed<<setprecision(20)<<czas5;
	cout<<"\n";
	start7=clock();
	BUBBLE_SORT_RISING(tab,rozmiar);
	stop7=clock();
	czas7=stop-start;
	czas7=(double)czas7/CLOCKS_PER_SEC;
	cout<<"BUBBLE_SORT_RISING_FROM_FALLING TIME 100000 ARRAY:\t"<<fixed<<setprecision(20)<<czas7;
	cout<<"\n";
	start8=clock();
	QUICK_SORT_RISING(tab2,0,(rozmiar-1));
	stop8=clock();
	czas8=stop8-start8;
	czas8=(double)czas2/CLOCKS_PER_SEC;
	cout<<"QUICK_SORT_RISING_FROM_FALLING TIME 100000 ARRAY:\t"<<fixed<<setprecision(20)<<czas8;
	return 0;
}
