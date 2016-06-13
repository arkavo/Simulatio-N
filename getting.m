data = dlmread("Graph.csv",",");
x1=data(:,1);
y1=data(:,2);
x2=data(:,4);
y2=data(:,5);
plot(x1,y1,";particle1;");
