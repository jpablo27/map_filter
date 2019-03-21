//FILTER

//NOTES

/*

The center of the 41x41 sqared window is 20,20 + offset

*/


#include <iostream>
#include <vector>
#include <algorithm>

const int w_s=41;
const int i_s=256;



struct XYPoint
{
	int r;//for rows
	int c;//for cols
};

struct subcheck
{
	bool clear;
	bool obstacle;
	bool uk;
	int count;
	XYPoint pix;
};

class map_filter
{
public:
	map_filter(){
	}
	~map_filter(){
	}

	void filter(int img[][i_s]);

private:


	bool Q1(int img[][i_s], XYPoint & w_o);
	bool Q2(int img[][i_s], XYPoint & w_o);
	bool Q3(int img[][i_s], XYPoint & w_o);
	bool Q4(int img[][i_s], XYPoint & w_o);

	subcheck obsQ1(int img[][i_s], XYPoint & w_o);
	subcheck obsQ2(int img[][i_s], XYPoint & w_o);
	subcheck obsQ3(int img[][i_s], XYPoint & w_o);
	subcheck obsQ4(int img[][i_s], XYPoint & w_o);
	
	void check6 (int img[][i_s], XYPoint origin);
	bool check1 (int img[][i_s], XYPoint origin);

	bool obs_check(int img[][i_s], XYPoint origin);
};


void map_filter::filter(int img[][i_s]){

	XYPoint origin;

	for (int i = 0; i < (int)i_s/w_s; i++)
	{
		origin.r = w_s*i;
		for (int j = 0; j < (int)i_s/w_s; j++)
		{
			origin.c = w_s*j;	
			check6(img, origin); 
		}
	}
}


void map_filter::check6 (int img[][i_s], XYPoint origin){

	if (img[origin.r+(int)(w_s/2)][origin.c+(int)(w_s/2)] == 255) //if center is pissible phantom obstacle
	{
		if (check1(img,origin))	img[origin.r+(int)(w_s/2)][origin.c+(int)(w_s/2)]=0;
	}else{//if not, search for possible phantom obstacles inside this square
		obs_check(img, origin);
	}
}

bool map_filter::obs_check(int img[][i_s], XYPoint origin){
	subcheck q1,q2,q3,q4;

	XYPoint new_origin;

	//Case 1
	if( origin.r == 0 && origin.c == 0){
		q4=obsQ4(img,origin);
		if( q4.obstacle && q4.clear ){
			new_origin.r = q4.pix.r - (int)(w_s/2);
			new_origin.c = q4.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q4.pix.r][q4.pix.c]=0;
		}
	}else if (origin.r == 205 && origin.c == 205){ // Case 2
		q1=obsQ1(img,origin);
		q2=obsQ2(img,origin);
		q3=obsQ3(img,origin);
		q4=obsQ4(img,origin);
		
		if (q1.obstacle && q1.clear )
		{
			new_origin.r = q1.pix.r - (int)(w_s/2);
			new_origin.c = q1.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q1.pix.r][q1.pix.c]=0;	
		}
		

		if(q2.pix.r < 236 && q2.pix.c < 236){
			if (q2.obstacle && q2.clear )
			{
				new_origin.r = q2.pix.r - (int)(w_s/2);
				new_origin.c = q2.pix.c - (int)(w_s/2);	
				if(check1(img,new_origin)) img[q2.pix.r][q2.pix.c]=0;					
			}
		}
		if(q3.pix.r < 236 && q3.pix.c < 236){
			if (q3.obstacle && q3.clear )
			{
				new_origin.r = q3.pix.r - (int)(w_s/2);
				new_origin.c = q3.pix.c - (int)(w_s/2);	
				if(check1(img,new_origin)) img[q3.pix.r][q3.pix.c]=0;					
			}			
		}
		if(q4.pix.r < 236 && q4.pix.c < 236){
			if (q4.obstacle && q4.clear )
			{
				new_origin.r = q4.pix.r - (int)(w_s/2);
				new_origin.c = q4.pix.c - (int)(w_s/2);	
				if(check1(img,new_origin)) img[q4.pix.r][q4.pix.c]=0;					
			}			
		}		

	}else if(origin.r ==0 && origin.c == 205){ // Case 3
		q3=obsQ3(img,origin);
		q4=obsQ4(img,origin);


		if (q3.obstacle && q3.clear )
		{
			new_origin.r = q3.pix.r - (int)(w_s/2);
			new_origin.c = q3.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q3.pix.r][q3.pix.c]=0;	
		}
		
		if(q4.pix.c < 236){
			if (q1.obstacle && q1.clear )
			{
				new_origin.r = q4.pix.r - (int)(w_s/2);
				new_origin.c = q4.pix.c - (int)(w_s/2);	
				if(check1(img,new_origin)) img[q4.pix.r][q4.pix.c]=0;	
			}
		}

	}else if(origin.r == 205 && origin.c == 0){ // Case 4
		q2=obsQ2(img,origin);
		q4=obsQ4(img,origin);

		if (q2.obstacle && q2.clear )
		{
			new_origin.r = q2.pix.r - (int)(w_s/2);
			new_origin.c = q2.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q2.pix.r][q2.pix.c]=0;	
		}

		if(q4.pix.r < 236){
			if (q4.obstacle && q4.clear )
			{
				new_origin.r = q4.pix.r - (int)(w_s/2);
				new_origin.c = q4.pix.c - (int)(w_s/2);	
				if(check1(img,new_origin)) img[q4.pix.r][q4.pix.c]=0;	
			}
		}

	}else if((origin.r > 0 && origin.r < 205) && (origin.c > 0 && origin.c < 205) ){ //Case 9
		q1=obsQ1(img,origin);
		q2=obsQ2(img,origin);
		q3=obsQ3(img,origin);
		q4=obsQ4(img,origin);

		if (q1.obstacle && q1.clear )
		{
			new_origin.r = q1.pix.r - (int)(w_s/2);
			new_origin.c = q1.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q1.pix.r][q1.pix.c]=0;	
		}
		if (q2.obstacle && q2.clear )
		{
			new_origin.r = q2.pix.r - (int)(w_s/2);
			new_origin.c = q2.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q2.pix.r][q2.pix.c]=0;	
		}			

		if (q3.obstacle && q3.clear )
		{
			new_origin.r = q3.pix.r - (int)(w_s/2);
			new_origin.c = q3.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q3.pix.r][q3.pix.c]=0;	
		}
		if (q4.obstacle && q4.clear )
		{
			new_origin.r = q4.pix.r - (int)(w_s/2);
			new_origin.c = q4.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q4.pix.r][q4.pix.c]=0;	
		}

	}else if(origin.r == 0){//Case 5
		q3=obsQ3(img,origin);
		q4=obsQ4(img,origin);
		if (q3.obstacle && q3.clear )
		{
			new_origin.r = q3.pix.r - (int)(w_s/2);
			new_origin.c = q3.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q3.pix.r][q3.pix.c]=0;	
		}
		if (q4.obstacle && q4.clear )
		{
			new_origin.r = q4.pix.r - (int)(w_s/2);
			new_origin.c = q4.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q4.pix.r][q4.pix.c]=0;	
		}	
	}else if(origin.c == 0){//Case 6
		q2=obsQ2(img,origin);
		q4=obsQ4(img,origin);
		if (q2.obstacle && q2.clear )
		{
			new_origin.r = q2.pix.r - (int)(w_s/2);
			new_origin.c = q2.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q2.pix.r][q2.pix.c]=0;	
		}
		if (q4.obstacle && q4.clear )
		{
			new_origin.r = q4.pix.r - (int)(w_s/2);
			new_origin.c = q4.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q4.pix.r][q4.pix.c]=0;	
		}	
	}else if(origin.r == 205){//Case 7
		q1=obsQ1(img,origin);
		q2=obsQ2(img,origin);
		q3=obsQ3(img,origin);
		q4=obsQ4(img,origin);

		if (q1.obstacle && q1.clear )
		{
			new_origin.r = q1.pix.r - (int)(w_s/2);
			new_origin.c = q1.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q1.pix.r][q1.pix.c]=0;	
		}
		if (q2.obstacle && q2.clear )
		{
			new_origin.r = q2.pix.r - (int)(w_s/2);
			new_origin.c = q2.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q2.pix.r][q2.pix.c]=0;	
		}
		if(q3.pix.r<236){
			if (q3.obstacle && q3.clear )
			{
				new_origin.r = q3.pix.r - (int)(w_s/2);
				new_origin.c = q3.pix.c - (int)(w_s/2);	
				if(check1(img,new_origin)) img[q3.pix.r][q3.pix.c]=0;	
			}
		}
		if(q4.pix.r<236){
			if (q4.obstacle && q4.clear )
			{
				new_origin.r = q4.pix.r - (int)(w_s/2);
				new_origin.c = q4.pix.c - (int)(w_s/2);	
				if(check1(img,new_origin)) img[q4.pix.r][q4.pix.c]=0;	
			}
		}	

	}else if(origin.c == 205){//Case 8
		q1=obsQ1(img,origin);
		q2=obsQ2(img,origin);
		q3=obsQ3(img,origin);
		q4=obsQ4(img,origin);

		if (q1.obstacle && q1.clear )
		{
			new_origin.r = q1.pix.r - (int)(w_s/2);
			new_origin.c = q1.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q1.pix.r][q1.pix.c]=0;	
		}
		if(q2.pix.c<236){
			if (q2.obstacle && q2.clear )
			{
				new_origin.r = q2.pix.r - (int)(w_s/2);
				new_origin.c = q2.pix.c - (int)(w_s/2);	
				if(check1(img,new_origin)) img[q2.pix.r][q2.pix.c]=0;	
			}
		}
		if (q3.obstacle && q3.clear )
		{
			new_origin.r = q3.pix.r - (int)(w_s/2);
			new_origin.c = q3.pix.c - (int)(w_s/2);	
			if(check1(img,new_origin)) img[q3.pix.r][q3.pix.c]=0;	
		}
		
		if(q4.pix.c<236){
			if (q4.obstacle && q4.clear )
			{
				new_origin.r = q4.pix.r - (int)(w_s/2);
				new_origin.c = q4.pix.c - (int)(w_s/2);	
				if(check1(img,new_origin)) img[q4.pix.r][q4.pix.c]=0;	
			}
		}		
	}else{
		return false;
	}
}


bool map_filter::Q1(int img[][i_s], XYPoint & w_o){
	for (int r = 0; r < (int)(w_s/2); r++)
	{
		for (int c = 0; c < (int)(w_s/2); c++)
		{
			if (img[w_o.r+r][w_o.c+c]!=0){
				return false;
			}
		}
	}
	return true;
}
bool map_filter::Q2(int img[][i_s], XYPoint & w_o){
	for (int r = 0; r < (int)(w_s/2); r++)
	{
		for (int c = (int)(w_s/2); c < w_s; c++)
		{
			if (img[w_o.r+r][w_o.c+c]!=0){
				return false;
			}
		}
	}
	return true;
}
bool map_filter::Q3(int img[][i_s], XYPoint & w_o){
	for (int r = (int)(w_s/2); r < w_s; r++)
	{
		for (int c = 0; c < (int)(w_s/2); c++)
		{
			if (img[w_o.r+r][w_o.c+c]!=0){
				return false;
			}
		}
	}
	return true;
}

bool map_filter::Q4(int img[][i_s], XYPoint & w_o){
	for (int r = (int)(w_s/2); r < w_s; r++)
	{
		for (int c = (int)(w_s/2); c < w_s; c++)
		{
			if( c== (int)w_s/2 & r==(int)w_s/2){
				continue;
			}else if (img[w_o.r+r][w_o.c+c]!=0){
				return false;
			}
		}
	}
	return true;
}

subcheck map_filter::obsQ1(int img[][i_s], XYPoint & w_o){
	int value;
	subcheck out;
	out.clear = false;
	out.obstacle = false;
	out.uk = false;
	out.count = 0;
	for (int r = 0; r < (int)(w_s/2); r++)
	{
		for (int c = 0; c < (int)(w_s/2); c++)
		{
			value = img[w_o.r+r][w_o.c+c];
			if (value==0){
				continue;
			}else if ((value!=0)&&(value!=255))
			{	
				out.uk = true;
				out.pix.r = w_o.r+r;
				out.pix.c = w_o.c+c;
				out.count ++;
			}else if (img[w_o.r+r][w_o.c+c]==255){
				out.obstacle = true;
				out.pix.r = w_o.r+r;
				out.pix.c = w_o.c+c;
				out.count ++;
			}
			if (out.count >1 ){
				return out;
			}
		}
	}
	out.clear = true;
	return out; // If no obstacles were found.
}

subcheck map_filter::obsQ2(int img[][i_s], XYPoint & w_o){
	int value;
	subcheck out;
	out.clear = false;
	out.obstacle = false;
	out.uk = false;
	out.count = 0;
	for (int r = 0; r < (int)(w_s/2); r++)
	{
		for (int c = (int)(w_s/2); c < w_s; c++)
		{
			value = img[w_o.r+r][w_o.c+c];
			if (value==0){
				continue;
			}else if ((value!=0)&&(value!=255))
			{	
				out.uk = true;
				out.pix.r = w_o.r+r;
				out.pix.c = w_o.c+c;
				out.count ++;
			}else if (img[w_o.r+r][w_o.c+c]==255){
				out.obstacle = true;
				out.pix.r = w_o.r+r;
				out.pix.c = w_o.c+c;
				out.count ++;
			}
			if (out.count >1 ){
				return out;
			}
		}
	}
	out.clear = true;
	return out; // If no obstacles were found.
}
subcheck map_filter::obsQ3(int img[][i_s], XYPoint & w_o){
	int value;
	subcheck out;
	out.clear = false;
	out.obstacle = false;
	out.uk = false;
	out.count = 0;
	for (int r = (int)(w_s/2); r < w_s; r++)
	{
		for (int c = 0; c < (int)(w_s/2); c++)
		{
			value = img[w_o.r+r][w_o.c+c];
			if (value==0){
				continue;
			}else if ((value!=0)&&(value!=255))
			{	
				out.uk = true;
				out.pix.r = w_o.r+r;
				out.pix.c = w_o.c+c;
				out.count ++;
			}else if (img[w_o.r+r][w_o.c+c]==255){
				out.obstacle = true;
				out.pix.r = w_o.r+r;
				out.pix.c = w_o.c+c;
				out.count ++;
			}
			if (out.count >1 ){
				return out;
			}
		}
	}
	out.clear = true;
	return out; // If no obstacles were found.
}

subcheck map_filter::obsQ4(int img[][i_s], XYPoint & w_o){
	int value;
	subcheck out;
	out.clear = false;
	out.obstacle = false;
	out.uk = false;
	out.count = 0;
	for (int r = (int)(w_s/2); r < w_s; r++)
	{
		for (int c = (int)(w_s/2); c < w_s; c++)
		{
			if( c== (int)w_s/2 & r==(int)w_s/2){
				continue;
			}

			value = img[w_o.r+r][w_o.c+c];
			if (value==0){
				continue;
			}else if ((value!=0)&&(value!=255))
			{	
				out.uk = true;
				out.pix.r = w_o.r+r;
				out.pix.c = w_o.c+c;
				out.count ++;
			}else if (img[w_o.r+r][w_o.c+c]==255){
				out.obstacle = true;
				out.pix.r = w_o.r+r;
				out.pix.c = w_o.c+c;
				out.count ++;
			}
			if (out.count >1 ){
				return out;
			}

		}
	}
	out.clear = true;
	return out; // If no obstacles were found.
}

bool map_filter::check1(int img[][i_s], XYPoint origin){

	if (Q1(img,origin))
	{
		if (Q2(img,origin))
		{
			if (Q3(img,origin))
			{
				if (Q4(img,origin))
					{
						return true;
					}
			}	
		}
	}

	return false;
}
/*
XYPoint distance(vector<XYPoint> a, vector<XYPoint> b){
	XYPoint dist;

	vector<XYPoint> out;
	int mdist;

	if (a.size()>b.size())
	{
		for (int i = 0; i < a.size(); i++)
		{
			dist.r = a[i].r - b[0].r;
			dist.c = a[i].c - b[0].c;
			mdist = dist.r + dist.c;
			
		}
	}else if(a.size()<b.size()){

	}else{

	}

	dist.r = a.r - b.r;
	dist.c = a.c - b.c;

	if(dist.r<0) dist.r = dist.r*-1;
	if(dist.c<0) dist.c = dist.c*-1;

	return dist;
}*/