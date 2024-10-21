#include <bits/stdc++.h>

int main(){
	freopen("DATA_SET.txt", "r", stdin);
	
	char ch; int n1, n2;

	std::vector<std::pair<char,std::pair<double,double>>> dataSet;
	
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
	std::vector<std::pair<char,std::pair<double,double>>> centroid;
	// for example i will choose  first k index for testing
	
	// if(k>n) give a error 
	for(int a=0; a<k; a++){
		centroid.push_back({dataSet[a].first,{dataSet[a].second.first, dataSet[a].second.second}});
	}
	

	int iteration = 1;
	// give shot after calculation
	std::map<int, std::vector<std::pair<char,std::pair<int,int>>>> i;
	while(true){
		for(int a=0; a<n; a++){
			// point a:(1,1)
			// cen-1:(1,1)
			// 		dis = 0
			// cen-2:(2,1)
			//		dis = sqrt((x2-x1)^2+(y2-y1)^2)
			double x1 = dataSet[a].second.first, y1 = dataSet[a].second.second;
			std::vector<std::pair<double,int>> iv;
			for(int b=0; b<k; b++){
				double x2 = dataSet[a].second.first, y2 = dataSet[a].second.second;
				// Euclidean distance between two point
				double distance = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
				
				iv.push_back({distance,b});
			}
			
			sort(iv.begin(), iv.end());
			// assign to centroid (closer to point a)
			i[iv[0].second].push_back(dataSet[a]);
		}
		
		iteration++;
		break;
	}
	
	
	return 0;
}
