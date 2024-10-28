#include <bits/stdc++.h>

std::pair<double,double> mxmin(double x1, double x2){
	return {x2>x1 ? x2 : x1, x2>x1 ? x1 : x2};
}

int main(){
	freopen("DATA_SET.txt", "r", stdin);
	
	char ch; double n1, n2;

	std::vector<std::pair<char,std::pair<double,double>>> dataSet;
	
	while(std::cin >> ch >> n1 >> n2){
		if(ch=='0' && n1==n2 && n1==0){
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
		int m1 = dataSet[a].first, m2 = dataSet[a].second.first, m3 = dataSet[a].second.second;
		std::cout << m1 << " " << m2 << " " << m3 << std::endl;
		centroid.push_back({dataSet[a].first,{dataSet[a].second.first, dataSet[a].second.second}});
	}
	
	

	int iteration = 1;
	// give shot after calculation
	std::map<int, std::vector<std::pair<char,std::pair<double,double>>>> current, previous;
	bool port = false, result = false;
	int trip = 10;
	while(trip--){
		// check privous centroid == current centroid, it's our ending point
		
		current.clear();
		
		for(int a=0; a<n; a++){
			// point a:(1,1)
			// cen-1:(1,1)
			// 		dis = 0
			// cen-2:(2,1)
			//		dis = sqrt((x2-x1)^2+(y2-y1)^2)
			double x1 = dataSet[a].second.first, y1 = dataSet[a].second.second;
			std::cout << x1 << " -------- " << y1 << std::endl;
			std::vector<std::pair<double,int>> iv;
			for(int b=0; b<k; b++){
				double x2 = centroid[b].second.first, y2 = centroid[b].second.second;
				//std::cout << "(x1,x2) == " << x1 << "," << x2 << " (y1,y2) == " << y1 << "," << y2 << std::endl;
				//continue;
				// Euclidean distance between two point
				std::pair<double,double> enx = mxmin(x1,x2);
				std::pair<double,double> eny = mxmin(y1,y2);
				double p1 = enx.first-enx.second, p2 = eny.first-eny.second;
				// squre
				p1*=p1, p2*=p2;
				// squre root
				double distance = sqrt(p1+p2);
				//std::cout << p1 << " " << p2 << " distance " << distance << std::endl;

				iv.push_back({distance,b});
			}
			
			//continue;
			
	
			for(auto a : iv){
				std::cout << a.first << " +++ " << a.second << std::endl;
			}
			
			std::cout << "-------------------------" << std::endl;
			
			//continue;
			sort(iv.begin(), iv.end(),[&](std::pair<double,int> x, std::pair<double,int> y){
					if(x.first==y.first){
						return x.second<y.second;
					}
					
					return x.first<y.first;
				});
			// assign to centroid (closer to point a)
			current[iv[0].second].push_back(dataSet[a]);
		}
		
		
		if(!port){
			previous = current;
			port = true;
			continue;
		}
		// if only one dataset
		// handle the error
		if(previous==current){
			result = true;
			break;
		}else{
			previous = current;
		}
			
		/**
		for(int a=0; a<k; a++){
			for(int b=0; b<current[a].size(); b++){
				char p1 = current[a][b].first;
				std::cout << a << " == " << p1 << " ";
			}
			
			std::cout << std::endl;
		}
		
		std::cout << std::endl << std::endl;
		*/
		
		std::cout << iteration << std::endl;
		iteration++;
		//break;
	}
	
	for(int a=0; a<k; a++){
		for(int b=0; b<current[a].size(); b++){
			char p1 = current[a][b].first;
			std::cout << a+1 << " == " << p1 << " ";
		}
			
		std::cout << std::endl;
	}
	
	std::cout << ">> " << iteration << std::endl;
	
	
	return 0;
}
