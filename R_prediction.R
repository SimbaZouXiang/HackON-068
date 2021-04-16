data=read.csv("final.csv")    #read in data file

data$Hour=as.factor(data$Hour)  #factorize categorical variables
data$month=as.factor(data$month)
data$day=as.factor(data$day)
data$type=as.factor(data$type)
data$weekend=as.factor(data$weekend)
data$year=as.factor(data$year)

#In our example, we want to predict number of takeaway food that will be ordered at 1pm, 15 Jan
sample=subset(data,month==1&day==15&Hour==13&type==1) #Create a subset containing data (from last year/2016) fulfilling the above criteria

reg=lm(sandwiches~month+day+Hour+type,data=data)    #Set up Linear Regression models
reg2=lm(hamburger~month+day+Hour+type,data=data)    #Month, Day, Hour, Type as independent variables
reg3=lm(frenchfries~month+day+Hour+type,data=data)  #Food to be found (total amount of that food) as dependent variable

prediction=predict(reg,newdata=sample)    #Use the models and the sample data set to predict
prediction2=predict(reg2,newdata=sample)
prediction3=predict(reg3,newdata=sample)

table(prediction)   #Find out the predicted number of each order and the total number of order last year/2016
table(prediction2)
table(prediction3)

#Assume that numbers of orders of food in a certain time/month/type are similar over years
#To find out the predicted number of a certain kind of food under criteria, we can just multiply the numbers above (the predicted number of each order and the total number of order last year/2016)
