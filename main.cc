#include <bits/stdc++.h>

std::pair<double,double> mxmin(double x1, double x2){
	return {x2>x1 ? x2 : x1, x2>x1 ? x1 : x2};
}

int main(){
	freopen("DATA_SET.txt", "r", stdin);
	
	char ch; double n1, n2;

	std::vector<std::pair<char,std::vector<double>>> dataSet;
	
	while(std::cin >> ch){
		if(ch=='0'){
			break;
		}
		
		std::vector<double> vip;
		while(std::cin >> n1){
			if(n1==0){
				break;
			}
			vip.push_back(n1);
		}
		
		dataSet.push_back({ch,vip});
	}
	

	// Step-1: define cluster size
	int k = 5;
	// Step-2: define number of centroid
	int centroids = k, n = dataSet.size(), iteration = 1;
	
	// Step-3: choose randomly from dataset for centroid and store it
	std::vector<std::pair<char,std::vector<double>>> centroid;
	
	// if(k>n) give a error 
	for(int a=0; a<k; a++){
		centroid.push_back({dataSet[a].first, dataSet[a].second});
	}	
	
	// give a shot after calculation
	std::map<int, std::vector<std::pair<char,std::vector<double>>>> current, previous;
	bool port = false; 
	while(true){		
		current.clear();
		
		for(int a=0; a<n; a++){ // vector on dataSet[a].second
			std::vector<double> pointA = dataSet[a].second;
			std::vector<std::pair<double,int>> iv;
			for(int b=0; b<k; b++){
				std::vector<double> pointB = dataSet[b].second;
				// Step-4:: Euclidean distance method
				double distance = 0.0, pointSum = 0;
				for(int x=0, y=0; x<pointA.size(); x++){	
					std::pair<double,double> enx = mxmin(pointA[x], pointB[y]);
					double p1 = enx.first-enx.second;
					// squre
					p1*=p1; 
					pointSum+=p1;
				}
				// squre root
				distance = sqrt(pointSum);
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
				int cz = current[a].size();
				double sz = (double) cz;
				std::vector<double> pointSum;
				//double sm = 0.0, ahq = 0.0;
				for(int b=0; b<cz; b++){
					pointSum.assign(current[a][b].second.size(),0.0);
					for(int c=0; c<current[a][b].second.size(); c++){
						double px = current[a][b].second[c];
						pointSum[c]+=px;
					}

					for(int c=0; c<current[a][b].second.size(); c++){
						pointSum[c]/=sz;
					}
				}
				
				centroid.push_back({'~',pointSum});

			}
		}
		
		if(!port){
			previous = current;
			port = true;
		}else{
	
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
			printf(" Cluster %d: Centroid(", a+1);//,centroid[a].second.first,centroid[a].second.second);
			for(int b=0; b<centroid[a].second.size(); b++){
				if(b==centroid[a].second.size()-1){
					printf("%.2lf",centroid[a].second[b]);
				}else{	
					printf("%.2lf, ",centroid[a].second[b]);
				}
			}
			printf(") {");
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
