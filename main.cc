#include <bits/stdc++.h>

//using namespace std;

int main(){
	freopen("DATA_SET.txt", "r", stdin);
	
	char ch; int n1, n2;
	std::vector<std::pair<char,std::pair<int,int>>> dataSet;
	
	while(std::cin >> ch >> n1 >> n2){
		if(ch=='-1' && n1==n2 && n1==-1){
			break;
		}
		
		dataSet.push_back({ch,{n1,n2}});
	}
	
	// Step-1: define cluster size
	int k = 2;
	// Step-2: define number of centroid
	int centroids = k, n = dataSet.size();
	
	// Step-3: choose randomly from dataset for centroid and store it
	std::vector<std::pair<char,std::pair<int,int>>> centroid;
	// for example i will choose  first k index for testing
	
	// if(k>n) give a error 
	for(int a=0; a<k; a++){
		centroid.push_back({dataSet[a].first,{dataSet[a].second.first, dataSet[a].second.second}});
	}
	
	for(int a=0; a<n; a++){
		// point a
	}
	
	return 0;
}
