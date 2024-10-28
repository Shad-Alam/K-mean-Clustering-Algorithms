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
	int k = 4;
	// Step-2: define number of centroid
	int centroids = k, n = dataSet.size();
	
	// Step-3: choose randomly from dataset for centroid and store it
	std::vector<std::pair<char,std::pair<double,double>>> centroid;
	
	// if(k>n) give a error 
	for(int a=0; a<k; a++){
		int m1 = dataSet[a].first, m2 = dataSet[a].second.first, m3 = dataSet[a].second.second;
		centroid.push_back({dataSet[a].first,{dataSet[a].second.first, dataSet[a].second.second}});
	}

	int iteration = 1;
	// give a shot after calculation
	std::map<int, std::vector<std::pair<char,std::pair<double,double>>>> current, previous;
	bool port = false; 
	while(true){		
		current.clear();
		
		for(int a=0; a<n; a++){
			double x1 = dataSet[a].second.first, y1 = dataSet[a].second.second;

			std::vector<std::pair<double,int>> iv;
			for(int b=0; b<k; b++){
				double x2 = centroid[b].second.first, y2 = centroid[b].second.second;
			
				// Step-4:: Euclidean distance between two point
				std::pair<double,double> enx = mxmin(x1,x2);
				std::pair<double,double> eny = mxmin(y1,y2);
				double p1 = enx.first-enx.second, p2 = eny.first-eny.second;
				// squre
				p1*=p1, p2*=p2;
				// squre root
				double distance = sqrt(p1+p2);

				iv.push_back({distance,b});
			}
			
		
			sort(iv.begin(), iv.end(),[&](std::pair<double,int> x, std::pair<double,int> y){
					if(x.first==y.first){
						return x.second<y.second;
					}
					
					return x.first<y.first;
				});
			// Step-5:: assign to centroid (closer to point a)
			current[iv[0].second].push_back(dataSet[a]);
		}
		
		{
			centroid.clear();
			// Step-6:: Update centroid
			for(int a=0; a<k; a++){
				
				double sm = 0.0, ahq = 0.0;
				for(int b=0; b<current[a].size(); b++){
					char p1 = current[a][b].first;
					double px = current[a][b].second.first;
					double py = current[a][b].second.second;
					
					sm+=px, ahq+=py;
				}
				
				double sz = (double) current[a].size();
				sm/=sz, ahq/=sz;
					
				centroid.push_back({'~',{sm, ahq}});

			}
		}
		
		
		if(!port){
			previous = current;
			port = true;
		}else{
			// if only one dataset
			// handle the error
			if(previous==current){
				break;
			}else{
				previous = current;
			}
		}
				
		iteration++;
	}
	
	{
		std::cout << "\n Number of Iteration = " << iteration << std::endl << std::endl;
		for(int a=0; a<k; a++){
			printf(" Cluster %d:(%.2lf,%.2lf) {", a+1,centroid[a].second.first,centroid[a].second.second);
			for(int b=0; b<current[a].size(); b++){
				char p1 = current[a][b].first;
				if(b==current[a].size()-1){
					printf("%c",p1);
					break;
				}
				printf("%c, ",p1);
			}
				
			printf("}\n");
		}
	}
	
	
	return 0;
}
